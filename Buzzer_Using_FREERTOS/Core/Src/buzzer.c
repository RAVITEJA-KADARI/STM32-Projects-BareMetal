/*
 * buzzer.c
 *
 *  Created on: May 19, 2026
 *      Author: Vishwa teja
 */


#include <stdio.h>
#include <stm32f303_reg.h>

void gpio_init(void)
{
	RCC_AHBENR |= (1 << PORTB_EN);

	GPIOB_MODER &= ~(3 << (5*2));
	GPIOB_MODER |=  (1 << (5*2));

}
