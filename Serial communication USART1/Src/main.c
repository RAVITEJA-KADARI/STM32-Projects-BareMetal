
#include <stdint.h>

#define RCC_Base	0x40021000
#define RCC_AHBENR	(*(volatile uint32_t*)(RCC_Base + 0x14))
#define RCC_APB2ENR	(*(volatile uint32_t*)(RCC_Base + 0x18))

#define GPIOC_Base	0x48000800
#define GPIOC_MODER	(*(volatile uint32_t*)(GPIOC_Base + 0x00))
#define GPIOC_AFRL	(*(volatile uint32_t*)(GPIOC_Base + 0x20))

//--------For LCD RS,RW,EN--------//
#define GPIOE_BASE      0x48001000
#define GPIOE_MODER     (*(volatile uint32_t*)(GPIOE_BASE + 0x00))
#define GPIOE_ODR       (*(volatile uint32_t*)(GPIOE_BASE + 0x14))

//--------For LCD DATA PINS--------//
#define GPIOD_BASE      0x48000C00
#define GPIOD_MODER     (*(volatile uint32_t*)(GPIOD_BASE + 0x00))
#define GPIOD_ODR       (*(volatile uint32_t*)(GPIOD_BASE + 0x14))


//--------LCD--------//

#define PORTE_EN        		21			// 	PORTE  LCD Control Lines
#define PORTD_EN        		20			// 	PORTD  LCD Data line

#define LCD_RS          		8   		// 	PE8
#define LCD_RW          		9   		// 	PE9
#define LCD_EN          		10   		// 	PE10

#define LCD_D0          		8			//	PD8
#define LCD_D1          		9			//	PD9
#define LCD_D2          		10			//	PD10
#define LCD_D3          		11			//	PD11
#define LCD_D4          		12			//	PD12
#define LCD_D5          		13			//	PD13
#define LCD_D6          		14			//	PD14
#define LCD_D7          		15			//	PD15


#define BUFFER_SIZE 32
char usart1_buffer[BUFFER_SIZE];

/* ================= DELAY ================= */
void _delay_ms(uint16_t i)
{
	while(i)
	{
		for(uint16_t k = 0; k < 1000; k++);
		i--;
	}
}

void gpio_init(void)
{
    RCC_AHBENR  |=  (1 << PORTE_EN) | (1 << PORTD_EN);

    GPIOE_MODER &= ~(0xFF);
    GPIOE_MODER |=  ((1 << LCD_RS * 2) | (1 << LCD_RW * 2) | (1 << LCD_EN * 2));

    GPIOD_MODER &= ~(0xFFFF << 16);
    GPIOD_MODER |=  (0x5555 << 16);		// 0101 0101 0101 0101

    GPIOE_ODR   &= ~((1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN));
}


void lcd_pulse(void)
{
    GPIOE_ODR |=  (1 << LCD_EN);
    _delay_ms(1);

    GPIOE_ODR &= ~(1 << LCD_EN);
    _delay_ms(2);
}


void lcd_command(char cmd)
{
    GPIOE_ODR &= ~(1 << LCD_RS);
    GPIOE_ODR &= ~(1 << LCD_RW);
    GPIOD_ODR  =  (GPIOD_ODR & 0x00FF) | (cmd << 8);
    lcd_pulse();
}

void lcd_data(char data)
{
    GPIOE_ODR |=  (1 << LCD_RS);
    GPIOE_ODR &= ~(1 << LCD_RW);
    GPIOD_ODR  =  (GPIOD_ODR & 0x00FF) | (data << 8);
    lcd_pulse();
}


void lcd_init(void)
{
    _delay_ms(20);
    lcd_command(0x38);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_command(0x01);
    _delay_ms(2);
}


void lcd_print(char *str)
{
	lcd_command(0x80);

    int i = 0;

    while(str[i] && i < 16)
        lcd_data(str[i++]);

    if(str[i])
    {
    	lcd_command(0xC0);
        while(str[i] && i < 32)
            lcd_data(str[i++]);
    }
}


#define PORTC_EN	19
#define TxPC4		4
#define RxPC5		5
#define USART1EN	14

//--------USART Registers------//
#define USART1_Base	0x40013800
#define USART1_CR1	(*(volatile uint32_t*)(USART1_Base + 0x00))
#define USART1_BRR	(*(volatile uint32_t*)(USART1_Base + 0x0C))
#define USART1_ISR	(*(volatile uint32_t*)(USART1_Base + 0x1C))
#define USART1_TDR	(*(volatile uint32_t*)(USART1_Base + 0x28))
#define USART1_RDR  (*(volatile uint32_t*)(USART1_Base + 0x24))

#define USART1_CR1_UE	(1 << 0)
#define USART1_CR1_RE   (1 << 2)
#define USART1_CR1_TE	(1 << 3)
#define USART1_ISR_TXE	(1 << 7)
#define USART1_ISR_RXNE (1 << 5)

#define USART1_Baud_9600  833

static void usart1_init(void)
{
	RCC_AHBENR |= (1 << PORTC_EN);

	GPIOC_MODER &= ~((3 << (TxPC4 * 2)) | (3 << (RxPC5*2)));
	GPIOC_MODER |=  ((2 << (TxPC4 * 2)) | (2 << (RxPC5*2)));

	GPIOC_AFRL &= ~((0xF << (TxPC4 * 4)) | (0xF << (RxPC5*4)));
	GPIOC_AFRL |=  ((0x7 << (TxPC4 * 4)) | (0x7 << (RxPC5*4)));

	RCC_APB2ENR |= (1 << USART1EN);

	USART1_BRR = USART1_Baud_9600;


	USART1_CR1 = USART1_CR1_UE |  USART1_CR1_TE	|	USART1_CR1_RE;

}

/* 🔹 Receive one char */
char usart1_read(void)
{
    while(!(USART1_ISR & USART1_ISR_RXNE)); // RXNE
    return USART1_RDR;
}

/* 🔹 Transmit one char */
void usart1_write_char(char c)
{
    while(!(USART1_ISR & USART1_ISR_TXE)); // TXE
    USART1_TDR = c;
}

/* 🔹 Transmit string */
void usart1_write_string(char *str)
{
    int i = 0;
    while(str[i])
        usart1_write_char(str[i++]);
}

/* 🔹 Read string + Echo */
void usart1_read_string(void)
{
    int i = 0;
    char c;

    while(i < BUFFER_SIZE - 1)
    {
        c = usart1_read();

        if(c == '\r' || c == '\n')
        {
            usart1_write_string("\r\n"); // new line in terminal
            break;
        }

        usart1_write_char(c); // 🔥 Echo back
        usart1_buffer[i++] = c;
    }

    usart1_buffer[i] = '\0';
}

/* ================= MAIN ================= */
int main(void)
{
    gpio_init();
    lcd_init();
    usart1_init();

    usart1_write_string("System Ready\r\n");

    lcd_print("HELLO!");
    _delay_ms(2000);

    lcd_print("USART READY");
    _delay_ms(2000);

    while(1)
    {
        usart1_write_string("Enter Text: ");

        usart1_read_string();

        lcd_command(0x01);   // 🔥 CLEAR FIRST
         _delay_ms(2);

        lcd_print(usart1_buffer);

    }
}
