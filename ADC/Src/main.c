/**
 ******************************************************************************
 * @file           : main.c
 * @author         : RAVITEJA KADARI
 * @github         : https://github.com/RAVITEJA-KADARI
 * @brief          : 16x2 LCD Display ADC Reader using STM32 Discovery Board
 ******************************************************************************
 * @attention
 *
 * This project demonstrates bare-metal GPIO and ADC programming on STM32 
 * microcontrollers to read analog input from a sensor (PA0) and display 
 * the value on a 16x2 LCD without using HAL or CMSIS libraries.
 *
 * Hardware  : STM32 Discovery Board, 16x2 LCD
 * Created   : 2026
 *
 * License   : MIT License
 *
 ******************************************************************************
 */

#include<stdint.h>

#define RCC_Base		0x40021000
#define RCC_AHBENR		(*(volatile uint32_t*)(RCC_Base + 0x14))
#define RCC_CFGR2		(*(volatile uint32_t*)(RCC_Base + 0x2C))

//------for ADC-------//
#define GPIOA_Base		0x48000000
#define GPIOA_MODER		(*(volatile uint32_t*)(GPIOA_Base + 0x00))
#define GPIOA_IDR		(*(volatile uint32_t*)(GPIOA_Base + 0x10))
#define GPIOA_ODR		(*(volatile uint32_t*)(GPIOA_Base + 0x14))
#define GPIOA_PUPDR		(*(volatile uint32_t*)(GPIOA_Base + 0x0C))

//-------for LCD RS,RW,EN--------//
#define GPIOC_Base		0x48000800
#define GPIOC_MODER		(*(volatile uint32_t*)(GPIOC_Base + 0x00))
#define GPIOC_ODR		(*(volatile uint32_t*)(GPIOC_Base + 0x14))

//--------For LCD D0-D8)--------//
#define GPIOD_Base		0x48000C00
#define GPIOD_MODER		(*(volatile uint32_t*)(GPIOD_Base + 0x00))
#define GPIOD_ODR		(*(volatile uint32_t*)(GPIOD_Base + 0x14))


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
#define PORTC_EN	19
#define PORTD_EN	20

#define LCD_RS		0
#define LCD_RW		1
#define LCD_EN		2

#define LCD_D0		8
#define LCD_D1		9
#define LCD_D2		10
#define LCD_D3		11
#define LCD_D4		12
#define LCD_D5		13
#define LCD_D6		14
#define LCD_D7		15

void delay(uint32_t t)
{
	while(t--)
		for(volatile uint32_t i = 0; i < 5000; i++);
}
void gpio_init(void)
{
	RCC_AHBENR |=  ((1 << PORTC_EN) | (1 << PORTD_EN));
	GPIOC_MODER &= ~((3 << LCD_RS*2) | (3 << LCD_RW*2) | (3 << LCD_EN*2));
	GPIOC_MODER |=  ((1 << LCD_RS*2) | (1 << LCD_RW*2) | (1 << LCD_EN*2));

	for(int i=8;i<=15;i++) {
	    GPIOD_MODER &= ~(3 << (i*2)); // clear
	    GPIOD_MODER |=  (1 << (i*2)); // set as output
	}


	GPIOD_ODR |= ((1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN));

}
void LCD_pulse(void)
{
	GPIOC_ODR |= (1 << LCD_EN);
	delay(2);

	GPIOC_ODR &= ~(1 << LCD_EN);
	delay(2);
}

void LCD_Command(char cmd)
{
	GPIOC_ODR &= ~(1 << LCD_RS);
	GPIOC_ODR &= ~(1 << LCD_RW);
	GPIOD_ODR = (GPIOD_ODR & 0x00FF)| (cmd << 8);
	LCD_pulse();
}

void LCD_data(char data)
{
	GPIOC_ODR |=  (1 << LCD_RS);
	GPIOC_ODR &= ~(1 << LCD_RW);
	GPIOD_ODR  =  (GPIOD_ODR & 0x00FF) | (data << 8);
	LCD_pulse();
}

void LCD_string(char *str)
{
	while(*str){
		LCD_data(*str++);
	}
}

void LCD_init(void)
{
	delay(50);
	LCD_Command(0x01);
	delay(50);
	LCD_Command(0x38);
	delay(50);
	LCD_Command(0x0C);
	delay(50);
	LCD_Command(0x06);
	delay(50);
	LCD_Command(0x01);
	delay(10);
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

int main(void)
{
	gpio_init();
	LCD_init();
	adc1_init();

	delay(10);
	LCD_Command(0x80);
	LCD_string("WELCOME");
	delay(500);
	LCD_Command(0x80);
	LCD_string("DATA INITI..");
	delay(500);
	LCD_Command(0xC0);
	LCD_string("ADC TESTING..");
	delay(500);
	LCD_Command(0x01);
	delay(10);
	uint32_t val;



	while(1)
	{
		while(1)
		{
			val = adc1_read();

			LCD_Command(0x80);  // Move cursor to beginning of 1st line
			delay(5);           // Small delay after command

			// Display "ADC: "
			LCD_string("ADC: ");

			// Display ADC value as digits
			LCD_data((val / 1000) + '0');
			LCD_data((val / 100) % 10 + '0');
			LCD_data((val / 10)  % 10 + '0');
			LCD_data(val % 10 + '0');

			delay(500);  // Slow down update
			LCD_Command(0x01);  // Clear screen for next reading
			delay(5);           // Small delay after clear
		}

	}
}

