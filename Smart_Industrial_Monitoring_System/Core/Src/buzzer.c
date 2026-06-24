/*
 * buzzer.c
 *
 *  Created on: May 19, 2026
 *      Author: Vishwa teja
 */


#include "stdio.h"
#include "stm32f303_reg.h"
#include "buzzer.h"



void gpio_buzzer_init(void)
{
	RCC_AHBENR |= (1 << 18);

	GPIOB_MODER &= ~(3 << (5*2)); // clearing Buzzer bits
	GPIOB_MODER |=  (1 << (5*2)); //output mode

	GPIOB_OTYPER &= ~(1 << 5);   // push-pull
	GPIOB_OSPEEDR |= (3 << (5 * 2)); // high speed
	GPIOB_PUPDR &= ~(3 << (5 * 2));  // no pull
}
