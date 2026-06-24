/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : 16x2 LCD using STM32F303 + I2C (PCF8574 module)
 *
 * This is bare-metal code (no HAL, no CMSIS).
 * We directly control registers of STM32F303.
 *
 * Connections:
 * PB6 -> I2C1 SCL
 * PB7 -> I2C1 SDA
 ******************************************************************************
 */

#include <stdint.h>

/* ================= RCC (Clock control registers) ================= */
// Base address for RCC (controls peripheral clocks)
#define RCC_Base        0x40021000

// Enable GPIOB clock
#define RCC_AHBENR      (*(volatile uint32_t*)(RCC_Base + 0x14))

// Enable I2C1 clock
#define RCC_APB1ENR     (*(volatile uint32_t*)(RCC_Base + 0x1C))


/* ================= GPIOB registers ================= */
// Base address for GPIOB
#define GPIOB_Base      0x48000400

#define GPIOB_MODER     (*(volatile uint32_t*)(GPIOB_Base + 0x00)) // mode select
#define GPIOB_OTYPER    (*(volatile uint32_t*)(GPIOB_Base + 0x04)) // output type
#define GPIOB_PUPDR     (*(volatile uint32_t*)(GPIOB_Base + 0x0C)) // pull-up/down
#define GPIOB_AFRL      (*(volatile uint32_t*)(GPIOB_Base + 0x20)) // alternate function


/* ================= I2C1 registers ================= */
#define I2C1_Base       0x40005400

#define I2C1_CR1        (*(volatile uint32_t*)(I2C1_Base + 0x00)) // control register
#define I2C1_CR2        (*(volatile uint32_t*)(I2C1_Base + 0x04)) // config register
#define I2C1_TIMINGR    (*(volatile uint32_t*)(I2C1_Base + 0x10)) // timing setup
#define I2C1_ISR        (*(volatile uint32_t*)(I2C1_Base + 0x18)) // status register
#define I2C1_ICR        (*(volatile uint32_t*)(I2C1_Base + 0x1C)) // interrupt clear
#define I2C1_TXDR       (*(volatile uint32_t*)(I2C1_Base + 0x28)) // transmit data


/* ================= Clock enable bits ================= */
#define GPIOBEN         18   // GPIOB enable bit in RCC
#define I2C1EN          21   // I2C1 enable bit in RCC


/* ================= LCD I2C address ================= */
#define LCD_ADDR 0x27   // change to 0x3F if your module uses it


/* ================= PCF8574 pin mapping =================
This is how I2C expander connects to LCD pins:

P0 = RS (Register Select)
P1 = RW (Read/Write)
P2 = EN (Enable)
P3 = Backlight
P4–P7 = Data lines (D4–D7)
*/
#define RS 0x01
#define RW 0x02
#define EN 0x04
#define BL 0x08


/* ================= Simple delay function ================= */
// Not accurate, just a rough delay for LCD timing
void delay_ms(uint32_t t)
{
    while(t--)
    {
        for(volatile uint32_t i = 0; i < 8000; i++);
    }
}


/* ================= I2C initialization ================= */
void I2C_Init(void)
{
    // 1. Enable clocks for GPIOB and I2C1
    RCC_AHBENR |= (1 << GPIOBEN);
    RCC_APB1ENR |= (1 << I2C1EN);

    // 2. Configure PB6 and PB7 as Alternate Function mode (I2C)
    GPIOB_MODER &= ~(0xF << 12);
    GPIOB_MODER |=  (0xA << 12);

    // 3. Open-drain output (required for I2C)
    GPIOB_OTYPER |= (1 << 6) | (1 << 7);

    // 4. Enable pull-up resistors (I2C needs pull-ups)
    GPIOB_PUPDR  |= (1 << 12) | (1 << 14);

    // 5. Select I2C function on PB6 and PB7
    GPIOB_AFRL &= ~(0xFF << 24);
    GPIOB_AFRL |=  (0x44 << 24);

    // 6. Disable I2C before configuration
    I2C1_CR1 &= ~(1);

    // 7. Set timing for ~100kHz I2C speed (based on 8MHz clock)
    I2C1_TIMINGR = 0x10420F13;

    // 8. Enable I2C
    I2C1_CR1 |= 1;
}


/* ================= I2C write function ================= */
// Sends 1 byte to a device on I2C bus
void I2C_Write(uint8_t addr, uint8_t data)
{
    // Wait until bus is free
    while(I2C1_ISR & (1 << 15));

    // Configure slave address + write mode
    I2C1_CR2 =
        (addr << 1) |   // device address
        (1 << 16) |     // number of bytes = 1
        (1 << 25);      // start condition

    I2C1_CR2 |= (1 << 13); // start transfer

    // Wait until TX register is ready
    while(!(I2C1_ISR & (1 << 1)));

    // Send data
    I2C1_TXDR = data;

    // Wait until transfer is complete
    while(!(I2C1_ISR & (1 << 5)));

    // Clear transfer complete flag
    I2C1_ICR |= (1 << 5);
}


/* ================= LCD low-level functions ================= */

// Send enable pulse to LCD (required for data read/write)
void LCD_pulse(uint8_t data)
{
    I2C_Write(LCD_ADDR, data | EN); // EN = 1
    delay_ms(2);

    I2C_Write(LCD_ADDR, data & ~EN); // EN = 0
    delay_ms(2);
}


/* Convert 4-bit data and send it to LCD */
void LCD_write4(uint8_t nibble, uint8_t rs)
{
    uint8_t data = 0;

    // Convert 4-bit nibble into LCD data pins (D4-D7)
    if(nibble & 0x01) data |= (1 << 4);
    if(nibble & 0x02) data |= (1 << 5);
    if(nibble & 0x04) data |= (1 << 6);
    if(nibble & 0x08) data |= (1 << 7);

    // Set RS = 1 for data, 0 for command
    if(rs) data |= RS;

    // Keep backlight ON
    data |= BL;

    LCD_pulse(data);
}


/* Send full byte (split into 2 nibbles) */
void LCD_send(uint8_t value, uint8_t rs)
{
    LCD_write4(value >> 4, rs);   // send upper 4 bits
    LCD_write4(value & 0x0F, rs); // send lower 4 bits
}


/* Send command to LCD */
void LCD_cmd(uint8_t cmd)
{
    LCD_send(cmd, 0);
}


/* Send character/data to LCD */
void LCD_data(char data)
{
    LCD_send(data, 1);
}


/* ================= LCD initialization ================= */
void LCD_init(void)
{
    delay_ms(50); // wait for LCD power-up

    // Initialization sequence for 4-bit mode
    LCD_write4(0x03,0); delay_ms(5);
    LCD_write4(0x03,0); delay_ms(5);
    LCD_write4(0x03,0); delay_ms(5);
    LCD_write4(0x02,0); delay_ms(5);

    // Configure LCD
    LCD_cmd(0x28);  // 4-bit mode, 2 lines
    LCD_cmd(0x0C);  // display ON, cursor OFF
    LCD_cmd(0x06);  // auto increment cursor
    LCD_cmd(0x01);  // clear display

    delay_ms(5);
}


/* Print string on LCD */
void LCD_string(char *str)
{
    while(*str)
    {
        LCD_data(*str++);
    }
}


/* ================= MAIN FUNCTION ================= */
int main(void)
{
    // Initialize I2C and LCD
    I2C_Init();
    LCD_init();

    // Print first line
    LCD_cmd(0x80); // move cursor to line 1
    LCD_string("HELLO");

    // Print second line
    LCD_cmd(0xC0); // move cursor to line 2
    LCD_string("WORKING NOW...");

    // Infinite loop
    while(1)
    {
    }
}
