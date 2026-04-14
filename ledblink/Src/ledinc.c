/*
 * ledinc.c
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

	//GPIOB clock

	for(int i=0;i<8;i++)
	{
		GPIOB -> MODER &= ~(3<<(i*2));
		GPIOB -> MODER |= (1<<(i*2));
	}

	//init_gpio_pin(PORTB);

	while(1)
	{
		for(int i=0;i<=3;i++)
		{
			//GPIOE -> ODR &= (1<<i);
			//delay();
			GPIOE -> ODR |= (1<<i);
			delay();

		}

		for(int i=3;i>=0;i--)
				{
					//GPIOE -> ODR &= ~(1<<i);
					//delay();
					GPIOE -> ODR |= (1<<i);
					delay();

				}
	}
	return 0;

}
