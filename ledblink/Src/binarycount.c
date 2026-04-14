/*
 * binarycount.c
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

	RCC ->AHBENR |=(1<<PORTB);

	//GPIOC clock

	for(int i=8;i<16;i++)
	{
		GPIOB -> MODER &= ~(3<<(i*2));
		GPIOB -> MODER |= (1<<(i*2));
	}

	//init_gpio_pin(PORTC);

	while(1)
	{
		for(uint16_t i=1;i<=255;i++)
		{
			GPIOE -> ODR &= ~(8<<i);
			delay();
			GPIOE -> ODR |= (8<<i);
			delay();
		}

	}
	return 0;

}
