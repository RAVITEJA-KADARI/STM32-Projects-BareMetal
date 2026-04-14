/*
 * sevensegmentdisplay.c
 *
 *  Created on: Nov 11, 2025
 *      Author: Vishwa teja
 */


#include<stdint.h>
#include <globalfile.h>

int main()
{

	int Look_Up_Table[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
	uint64_t Counter = 0;
	int Temp_Container[16];
	uint64_t Temp_Counter;

	RCC   -> AHBENR |=  (1 << PORTB);				//GPIOA clock enabled
	RCC   -> AHBENR |=  (1 << PORTC);				//GPIOA clock enabled
	GPIOB -> MODER  &=   0x0000; 					//MODER is loaded with 00
	GPIOB -> MODER  |=   ((1 <<   0 * 2) | (1 <<   1 * 2) | (1 <<  2 * 2) | (1 <<  3 * 2)\
						 |(1 <<   4 * 2) | (1 <<   5 * 2) | (1 <<  6 * 2) | (1 <<  7 * 2)\
						 |(1 <<   8 * 2) | (1 <<   9 * 2) | (1 << 10 * 2) | (1 << 11 * 2)
						 |(1 <<  12 * 2) | (1 <<  13 * 2) | (1 << 14 * 2) | (1 << 15 * 2)
						 );
	GPIOC -> MODER  &=   0x0000; 					//MODER is loaded with 00
	GPIOC -> MODER  |=   ((1 <<  0 * 2) |(1 <<  1 * 2)  | (1 <<  2 * 2) | (1 <<  3 * 2)\
						 |(1 <<  4 * 2) | (1 <<  5 * 2) | (1 <<  6 * 2) | (1 <<  7 * 2)\
						 |(1 <<  8 * 2) | (1 <<  9 * 2) | (1 << 10 * 2) | (1 << 11 * 2)\
						 |(1 << 12 * 2) | (1 << 13 * 2) | (1 << 14 * 2) | (1 << 15 * 2)\
						 );




	while(1)
	{
		Temp_Counter = Counter;
		for(uint8_t digit = 0; digit < 16; digit++)
		{
			Temp_Container[digit]  = Temp_Counter % 10;//gets the last digit
			Temp_Counter /= 10;//Removes the last digit
		}


				for(uint8_t channel = 0; channel < 16; channel++)
				{

					GPIOC -> ODR = channel;
					GPIOB -> ODR = Look_Up_Table[Temp_Container[15 - channel]];
					delay(1);

				}

			Counter++;
	}
	return 0;
}
