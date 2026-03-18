/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Raviteja Kadari
 * @github         : https://github.com/RAVITEJA-KADARI
 * @brief          : Relay control using STM32 GPIO (bare metal)
 ******************************************************************************
 * @attention
 *
 * This project demonstrates direct register-level GPIO programming
 * on an STM32 microcontroller to control a relay module.
 *
 * The relay is toggled ON and OFF with a fixed software delay,
 * illustrating basic digital output control without HAL/CMSIS.
 *
 * GPIO Port : GPIOA
 * Pin       : PA1 (Relay control)
 * Hardware  : STM32 (Fxx Series)
 * Created   : 2026
 *
 * License   : MIT License
 *
 ******************************************************************************
 */



#include<stdint.h>

#define RCC_BASE	0x40021000
#define RCC_AHBENR	(*(volatile uint32_t*)(RCC_BASE + 0x14))

#define GPIOA_BASE	0x48000000
#define GPIOA_MODER	(*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR	(*(volatile uint32_t*)(GPIOA_BASE + 0x14))

#define GPIOA	17

//#define LED  	8
#define RELAY	1

void delay(uint32_t time)
{
	volatile uint32_t i;
	for(i = 0; i < time; i++);
}


int main()
{
	//init_gpio(PORTE, LED);
	//init_gpio(PORTA, RELAY);
	RCC_AHBENR |= (1 << GPIOA);

	GPIOA_MODER &= ~(3 << (RELAY*2));
	GPIOA_MODER |=	(1 << (RELAY*2));

	while(1)
	{
		//GPIOE -> ODR ^= (1 << LED);
		GPIOA_ODR |= (1 << RELAY);
		delay(5000000);
		GPIOA_ODR &= ~(1 << RELAY);
		delay(5000000);
	}
	return 0;
}
