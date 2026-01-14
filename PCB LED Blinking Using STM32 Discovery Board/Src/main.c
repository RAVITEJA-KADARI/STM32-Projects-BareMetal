/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Raviteja Kadari
 * @github         : https://github.com/RAVITEJA-KADARI
 * @brief          : PCB LED blinking patterns using STM32 GPIOD (bare metal)
 ******************************************************************************
 * @attention
 *
 * This project demonstrates direct register-level GPIO programming
 * on an STM32 microcontroller to generate various LED blinking
 * patterns using GPIOD pins (PD0–PD10).
 *
 * Patterns implemented:
 *  - Incrementing LED sequence
 *  - Decrementing LED sequence
 *  - 2-by-2 LED blinking
 *  - 3-by-3 LED blinking
 *  - Increment + decrement sequence
 *
 * Hardware  : STM32 (Fxx Series)
 * Created   : 2026
 *
 * License   : MIT License
 *
 ******************************************************************************
 */


#include <stdint.h>


#define RCC_Base   0x40021000
#define RCC_AHBENR    (*(volatile uint32_t*)(RCC_Base + 0x14))

#define GPIOD_Base    0x48000c00
#define GPIOD_MODER   (*(volatile uint32_t*)(GPIOD_Base + 0x00))
#define GPIOD_ODR     (*(volatile uint32_t*)(GPIOD_Base + 0x14))

#define PORTD  20

void delay()
{

		for(uint32_t loop=0;loop<100000;loop++);


}


int main(void)
{

	RCC_AHBENR |=(1<<PORTD);

	//GPIOE clock

	for(int i=0;i<=10;i++)
	{
		GPIOD_MODER &= ~(3<<(i*2));
		GPIOD_MODER |= (1<<(i*2));
	}

	GPIOD_ODR = 0;


	//init_gpio_pin(PORTE);

	while(1)
	{

		//-------- blinking one by one increment--------//
		for(int i=0;i<2;i++)
		{
			for(int i=0;i<=10;i++)
			{
				GPIOD_ODR |= (1<<i);
				delay();

				}
			for(int i=0;i<=10;i++)
			{

				GPIOD_ODR &= ~(1<<i);
				delay();
				}

			}

		//-------- blinking one by one decrement --------//
		for(int i=0;i<2;i++)
		{
			for(int i=10;i>=0;i--)
			{
				GPIOD_ODR |= (1<<i);
				delay();

				}
			for(int i=10;i>=0;i--)
			{

				GPIOD_ODR &= ~(1<<i);
				delay();
				}

			}
		GPIOD_ODR = 0;
		//-------- blinking 2-2 increment --------//
		for(int i=0;i<2;i+=2)
		{
			for(int i=0;i<=10;i+=2)
			{
				GPIOD_ODR |= (1<<i);
				delay();

				}
			for(int i=0;i<=10;i+=2)
			{

				GPIOD_ODR &= ~(1<<i);
				delay();
				}

			}
		GPIOD_ODR = 0;
		//-------- blinking 3-3 increment --------//
		for(int i=0;i<2;i+=3)
		{
			for(int i=0;i<=10;i+=3)
			{
				GPIOD_ODR |= (1<<i);
				delay();

				}
			for(int i=0;i<=10;i+=3)
			{

				GPIOD_ODR &= ~(1<<i);
				delay();
				}

			}
		//-------- blinking increment + decrement --------//
		for(int i=0;i<2;i++)
		{
			for(int i=0;i<=10;i++)
			{
				GPIOD_ODR |= (1<<i);
				delay();

			}
				for(int i=10;i>=0;i--)
					{
						GPIOD_ODR &= ~(1<<i);
						delay();
					}

		}



}
	return 0;

}
