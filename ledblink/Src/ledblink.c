/*
 * ledblink.c
 *
 *  Created on: Nov 6, 2025
 *      Author: Vishwa teja
 */


#include <stdint.h>
#include "globalfile.h"


void delay()
{

		for(uint32_t loop=0;loop<1000;loop++);


}


int main(void){

	RCC ->AHBENR |=(1<<PORTC);

	//GPIOC clock

	for(int i=0;i<8;i++)
	{
		GPIOC -> MODER &= ~(3<<(i*2));
		GPIOC -> MODER |= (1<<(i*2));
	}

	//init_gpio_pin(PORTC);

	while(1)
	{
		for(int i=0;i<9;i++)
		{
			GPIOE -> ODR &= ~(1<<i);
			delay();
			GPIOE -> ODR |= (1<<i);
			delay();
		}

	}
	return 0;

}
