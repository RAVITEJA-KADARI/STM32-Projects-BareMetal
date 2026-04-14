/*
 * switchcode.c
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

	RCC ->AHBENR |=(1<<PORTA);
	RCC ->AHBENR |=(1<<PORTB);
	//GPIOC clock

	for(int i=8;i<15;i++)
	{

		GPIOB -> MODER &= ~(3<<(i*2));
		GPIOB -> MODER |= (1<<(i*2));
	}
	GPIOA -> MODER &= ~(3<<0*2);
	GPIOA -> IDR = (1<<1);

	while(1)
	{
		for(int i=0;i<8;i++)
		{

			GPIOB -> ODR &= ~(1<<i);
			delay();
			GPIOB -> ODR |= (1<<i);
			delay();
		}

	}
	return 0;

}
