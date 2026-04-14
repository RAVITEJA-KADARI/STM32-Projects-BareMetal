/*
 * withrelay.c
 *
 *  Created on: Nov 21, 2025
 *      Author: Vishwa teja
 */


//A bulb is controlled through a relay connected to PD0, Write application to on and off relay based on need to turn on and turn off electric bulb.

#include<stdint.h>
#include "ravi.h"

int main(){

	RCC -> AHBENR |= (1<<PORTD);
	RCC -> AHBENR |= (1<<PORTA);

	GPIOD -> MODER &= ~(3<<(0*2));
	GPIOD -> MODER |=  (1<<(0*2));

	GPIOA -> MODER &= ~(3<<(0*2));
	GPIOA -> MODER |=  (1<<(0*2));

	if(GPIOA -> IDR & (1<<0))
	{
		GPIOD -> ODR |= (1<<0);
	}
	else
	{
		GPIOD -> ODR &= ~(1<<0);
	}
	return 0;
}
