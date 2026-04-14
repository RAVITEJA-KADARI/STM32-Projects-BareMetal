/**
 ******************************************************************************
 * @file           : main.c
 * @author         : RAVITEJA KADARI
 * @github         : https://github.com/RAVITEJA-KADARI
 * @brief          : DC Motor Control Using STM32 Discovery Board
 ******************************************************************************
 * @attention
 *
 * This project demonstrates bare-metal GPIO programming on STM32 microcontrollers
 * to control a DC motor's direction (forward, backward, stop) using two GPIO pins
 * without using HAL or CMSIS libraries.
 *
 * Hardware  : STM32 Discovery Board, DC Motor, Driver Circuit
 * Created   : 2026
 *
 * License   : MIT License
 *
 ******************************************************************************
 */
#include<stdint.h>

#define RCC_Base		0x40021000
#define RCC_AHBENR		(*(volatile uint32_t*)(RCC_Base + 0x14))

#define GPIOA_Base		0x48000000
#define GPIOA_MODER		(*(volatile uint32_t*)(GPIOA_Base + 0x00))
#define GPIOA_ODR		(*(volatile uint32_t*)(GPIOA_Base + 0x14))

#define PORTA_EN	17
#define MOTORF	     4    ///int 1
#define MOTORB   	 3   ///int 2

/*
   int 1		   int 2			o/p
	0   			0           	stop
	0	    		1				backward
	1		    	0				forward


*/

void delay(void)
{
	for(volatile uint32_t i=0;i<500000;i++);

}


void gpio_init(void)
{
	RCC_AHBENR	|= (1 << PORTA_EN);

        GPIOA_MODER &= ~((3 << (MOTORF * 2)) | (3 << (MOTORB * 2)));
        GPIOA_MODER |=  ((1 << (MOTORF * 2)) | (1 << (MOTORB * 2)));

}

void Forward(void)
{
	GPIOA_ODR  |=  (1 << MOTORF);
	GPIOA_ODR  &= ~(1 << MOTORB);
}

void Backward(void)
{
	GPIOA_ODR  &= ~(1 << MOTORF);
	GPIOA_ODR  |=  (1 << MOTORB);
}

void Stop(void)
{
	GPIOA_ODR  &= ~(1 << MOTORB);
	GPIOA_ODR  &= ~(1 << MOTORF);
}



int main(void)
{
	gpio_init();
	while(1)
	{

		Forward();
		delay();

		Stop();
		delay();

		Backward();
		delay();

		Stop();
		delay();

	}

}

