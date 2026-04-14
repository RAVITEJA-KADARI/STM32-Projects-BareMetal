/*
 * ledpatternwithswitch.c
 *
 *  Created on: Nov 21, 2025
 *      Author: Vishwa teja
 */

// Blink the LEDs on the Discovery board as the connections in the schematic with switch connected to PA0

#include<stdint.h>
#include "ravi.h"

int i;
void delay(){

	for(volatile uint32_t loop=0;loop<1000;loop++);

}

int main(void){

	RCC -> AHBENR |= (1<<PORTA);
	RCC -> AHBENR |= (1<<PORTE);

	GPIOA -> MODER &= ~(1<<(0*2));
	//GPIOA -> MODER |=  (1<<(0*2));

	for(i=8;i<=15;i++){

	GPIOE -> MODER &= ~(1<<(i*2));
	GPIOE -> MODER |=  (1<<(i*2));
	}

	while(1){

		if(GPIOA -> IDR & (1<<0)){

				for(i=0;i<8;i++){

					GPIOE -> ODR |=  (1<<(i*2));
					delay();
				}

				for(i=8;i>0;i--){

					GPIOE -> ODR |=  (1<<(i*2));
					delay();
				}

				for(i=0;i<8;i+=2){

					GPIOE -> ODR |=  (1<<(i*2));
					delay();
				}

				for(i=0;i<8;i+=3){

					GPIOE -> ODR |=  (1<<(i*2));
					delay();
					}
				}
			else
			{
				GPIOE -> ODR &= ~(3<<(i*2));
			}

			}
			return 0;
		}

