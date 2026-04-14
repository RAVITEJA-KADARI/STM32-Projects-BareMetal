/*
 * switchbuzz.c
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

	GPIOC -> MODER &= ~(3<<(0*2));
	GPIOC -> MODER |= (1<<(0*2));

	//init_gpio_pin(PORTC);

	while(1)
	{

	 uint16_t switch1 =	GPIOC -> IDR = (1<<7);
			if (switch1)
			{
				GPIOC -> ODR &= ~(1<<0);
				delay();
				GPIOC -> ODR |= (1<<0);
				delay();
			}




	}
	return 0;

}
