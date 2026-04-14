/**
 ******************************************************************************
 * @file           : main.c
 * @author         : RAVITEJA KADARI
 * @github         : https://github.com/RAVITEJA-KADARI
 * @brief          : Buzzer Control with Switch Using STM32 Discovery Board
 ******************************************************************************
 * @attention
 *
 * This project demonstrates bare-metal GPIO programming on STM32 microcontrollers
 * to control a buzzer using a push-button switch without using HAL or CMSIS libraries.
 *
 * Hardware  : STM32 Discovery Board, Buzzer, Push-button Switch
 * Created   : 2026
 *
 * License   : MIT License
 *
 ******************************************************************************
 */
#include <stdint.h>

#define RCC_Base		0x40021000
#define RCC_AHBENR		(*(volatile uint32_t*)(RCC_Base + 0x14))

#define GPIOC_Base		0x48000800
#define GPIOC_MODER		(*(volatile uint32_t*)(GPIOC_Base + 0x00))
#define GPIOC_IDR		(*(volatile uint32_t*)(GPIOC_Base + 0x10))
#define GPIOC_ODR		(*(volatile uint32_t*)(GPIOC_Base + 0x14))

#define PORTC_EN	19
#define BUZZER		0
#define switch_pin	7

void delay(void)
{
    for(uint32_t loop = 0; loop < 1000000; loop++);
}

int main(void)
{
	RCC_AHBENR |= (1 << PORTC_EN);

    GPIOC_MODER &= ~(3 << (switch_pin * 2));

    GPIOC_MODER &= ~(3 << (BUZZER * 2));
    GPIOC_MODER |=  (1 << (BUZZER * 2));
while(1)
{

	if(GPIOC_IDR & (1 << switch_pin))
	{
		GPIOC_ODR |= (1 << BUZZER);
		delay();
	}
	else {
		GPIOC_ODR &= ~(1 << BUZZER);
	}
}

}
