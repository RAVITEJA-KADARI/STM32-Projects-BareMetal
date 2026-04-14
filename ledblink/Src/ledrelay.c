/*
 * ledrelay.c
 *
 *  Created on: Nov 11, 2025
 *      Author: Vishwa teja
 */


#include<stdint.h>
#include "globalfile.h"

#define LED  	8
#define RELAY	9

int main()
{
	init_gpio(PORTE, LED);
	init_gpio(PORTA, RELAY);

	while(1)
	{
		GPIOE -> ODR ^= (1 << LED);
		GPIOA -> ODR ^= (1 << RELAY);
		delay(500);
	}
	return 0;
}
