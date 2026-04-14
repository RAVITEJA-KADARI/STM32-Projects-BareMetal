/**
 ******************************************************************************
 * @file           : main.c
 * @author         : RAVITEJA KADARI
 * @github         : https://github.com/RAVITEJA-KADARI
 * @brief          : STM32 ADC + LCD + USART1 Example
 ******************************************************************************
 * @attention
 *
 * This project demonstrates:
 * 1. Bare-metal GPIO initialization on STM32.
 * 2. ADC1 initialization and analog value reading (PA0).
 * 3. LCD 16x2 display interface using GPIO (PE for control, PD for data).
 * 4. USART1 initialization for serial communication (PC4 TX, PC5 RX).
 * 5. Displaying ADC values on both LCD and UART.
 *
 * Hardware  : STM32 Discovery Board, 16x2 LCD, Gas Sensor or potentiometer
 * Created   : 2026
 *
 * License   : MIT License
 *
 ******************************************************************************
 */

#include <stdint.h>

#define RCC_Base	0x40021000
//-----CLOCk GPIO------//
#define RCC_AHBENR	(*(volatile uint32_t*)(RCC_Base + 0x14))
//------For USART1------//
#define RCC_APB2ENR (*(volatile uint32_t*)(RCC_Base + 0x18))
//-------For ADC Prescaler--------//
//#define RCC_CFGR2	(*(volatile uint32_t*)(RCC_Base + 0x2C))

//--------For LCD RS,RW,EN--------//
#define GPIOE_BASE      0x48001000
#define GPIOE_MODER     (*(volatile uint32_t*)(GPIOE_BASE + 0x00))
#define GPIOE_ODR       (*(volatile uint32_t*)(GPIOE_BASE + 0x14))

//--------For LCD DATA PINS--------//
#define GPIOD_BASE      0x48000C00
#define GPIOD_MODER     (*(volatile uint32_t*)(GPIOD_BASE + 0x00))
#define GPIOD_ODR       (*(volatile uint32_t*)(GPIOD_BASE + 0x14))

//-------For ADC-------//
#define GPIOA_Base	0x48000000
#define GPIOA_MODER	(*(volatile uint32_t*)(GPIOA_Base + 0x00))
#define GPIOA_IDR	(*(volatile uint32_t*)(GPIOA_Base + 0x10))
#define GPIOA_ODR	(*(volatile uint32_t*)(GPIOA_Base + 0x14))
#define GPIOA_AFRL	(*(volatile uint32_t*)(GPIOA_Base + 0x20))
#define GPIOA_PUPDR	(*(volatile uint32_t*)(GPIOA_Base + 0x0C))


//----------For USART1---------//
#define GPIOC_BASE      0x48000800
#define GPIOC_MODER     (*(volatile uint32_t*)(GPIOC_BASE + 0x00))
#define GPIOC_AFRL      (*(volatile uint32_t*)(GPIOC_BASE + 0x20))

///----------ADC------------//

#define ADC1_Base 		0x50000000
#define ADC_COMMON_BASE 0x50000300

#define ADC1_ISR		(*(volatile uint32_t*)(ADC1_Base + 0x00))
#define ADC1_IER		(*(volatile uint32_t*)(ADC1_Base + 0x04))
#define ADC1_CR 		(*(volatile uint32_t*)(ADC1_Base + 0x08))
#define ADC1_CFGR 		(*(volatile uint32_t*)(ADC1_Base + 0x0C))
#define ADC1_SMPR1 		(*(volatile uint32_t*)(ADC1_Base + 0x14))
#define ADC1_SQR1		(*(volatile uint32_t*)(ADC1_Base + 0x30))
#define ADC1_DR 		(*(volatile uint32_t*)(ADC1_Base + 0x40))

#define ADC1_CCR (*(volatile uint32_t*)(ADC_COMMON_BASE + 0x08))

#define PORTA_EN	17

void delay(uint32_t t)
{
	while(t--)
		for(volatile uint32_t i = 0; i < 5000; i++);
}

void adc1_init(void)
{
	RCC_AHBENR |=   (1 << PORTA_EN) | ( 1 << 28);
	GPIOA_MODER &= ~(3 << 0*2);
	GPIOA_MODER |=  (3 << 0*2);
	GPIOA_PUPDR  &= ~(1 << 0*2 );

	if(ADC1_CR & 1)
	{
		ADC1_CR |= (1 << 1);
		while(ADC1_CR & 1);
	}

	ADC1_CCR &= ~(3 << 16);
	ADC1_CCR |=  (1 << 16);

	ADC1_CR  &= ~(3 << 29);
	ADC1_CR  |=  (1 << 28);

	delay(100);

	ADC1_CR |= (1 << 31);
	while(	ADC1_CR & (1 << 31));

	ADC1_CFGR = 0x00000000;
	ADC1_SMPR1 |= (4 << 3);
	ADC1_SQR1 = (1 << 6);

	ADC1_CR |= 1;
	while(!(ADC1_CR & 1));
	ADC1_ISR = 1;

}

uint32_t adc1_read(void)
{
	ADC1_CR |= (1 << 2);               // start conversion
	while(!(ADC1_ISR & (1 << 2)));     // wait EOC
	uint32_t val = ADC1_DR;
	ADC1_ISR |= (1 << 2);              // clear EOC
	return val;
}

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


void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}


//------------------------USART1-------------------------//

#define USART1_BASE     0x40013800
#define USART1_CR1      (*(volatile uint32_t*)(USART1_BASE + 0x00))
#define USART1_BRR      (*(volatile uint32_t*)(USART1_BASE + 0x0C))
#define USART1_ISR      (*(volatile uint32_t*)(USART1_BASE + 0x1C))
#define USART1_RDR      (*(volatile uint32_t*)(USART1_BASE + 0x24))
#define USART1_TDR      (*(volatile uint32_t*)(USART1_BASE + 0x28))


#define USART_CR1_UE    		(1 << 0)
#define USART_CR1_RE    		(1 << 2)
#define USART_CR1_TE    		(1 << 3)
#define USART_ISR_RXNE  		(1 << 5)
#define USART_ISR_TXE   		(1 << 7)

#define USART1_BAUD_9600   		833	 	// 	= 8M / 9600 ≈ 833

#define TxPC4					4
#define RxPC5					5
#define USART1EN				14
#define PORTC_EN				19

static void uart1_init(void)
{

    RCC_AHBENR  |=  (1 << PORTC_EN);

    GPIOC_MODER &= ~((3    << (TxPC4*2)) | (3    << (RxPC5*2)));
    GPIOC_MODER |=  ((2    << (TxPC4*2)) | (2    << (RxPC5*2)));

    GPIOC_AFRL &= ~((0xF << (TxPC4*4)) | (0xF << (RxPC5*4)));
    GPIOC_AFRL |=  ((0x7 << (TxPC4*4)) | (0x7 << (RxPC5*4)));  // AF7 for USART1


    RCC_APB2ENR |= (1 << USART1EN);

    USART1_BRR = USART1_BAUD_9600;		// CPU f / Baud Rate = BRR Value = // 8000000 / 9600

    USART1_CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

static void uart1_write_char(char c)
{
    while(!(USART1_ISR & USART_ISR_TXE)); // wait until TXE
    USART1_TDR = c;
}

void uart1_tx_char(char c)
{
    while (!(USART1_ISR & USART_ISR_TXE));
    USART1_TDR = c;
}

char uart1_rx_char(void)
{
    while (!(USART1_ISR & USART_ISR_RXNE));
    return USART1_RDR;
}


static void uart1_print(const char* s)
{
    while (*s)
    {
        uart1_tx_char(*s++);
    }
}


int main(void)
{

    gpio_init();
    lcd_init();
    uart1_init();
    adc1_init();

    lcd_command(0x84);
	lcd_string("LCD USART!");
	lcd_command(0xC4);
	lcd_string("Success!");
	_delay_ms(2000);
	 lcd_command(0x84);
	 lcd_string("GAS SENSOR..!");
		lcd_command(0xC4);
		lcd_string("USING ADC...!");

    uart1_print("USART1 READY!");

 //   char c = uart1_rx_char();
	lcd_command(0x01);
	uint32_t val;



    	while(1)
    	{
    	    val = adc1_read();

    	    // LCD display
    	    lcd_command(0x80);      // first row
    	    lcd_string("ADC: ");
    	    lcd_data((val / 1000) + '0');
    	    lcd_data((val / 100) % 10 + '0');
    	    lcd_data((val / 10) % 10 + '0');
    	    lcd_data(val % 10 + '0');

    	    // UART display
    	    uart1_print("ADC: ");
    	    uart1_write_char((val / 1000) + '0');
    	    uart1_write_char((val / 100) % 10 + '0');
    	    uart1_write_char((val / 10)  % 10 + '0');
    	    uart1_write_char(val % 10 + '0');
    	    uart1_print("\r\n");

    	    _delay_ms(500);

    	    lcd_command(0x01); // clear LCD for next reading
    	}


    }

