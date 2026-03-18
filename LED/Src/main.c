/**
 ******************************************************************************
 * @file           : main.c
 * @author         : RAVITEJA KADARI
 * @github         : https://github.com/RAVITEJA-KADARI
 * @brief          : STM32 Bare-Metal GPIO Blink Example
 ******************************************************************************
 * @attention
 *
 * This project demonstrates:
 * 1. Enabling GPIOA clock on STM32.
 * 2. Configuring PA1–PA10 as output pins.
 * 3. Blinking LEDs connected to PA1–PA10 using simple delay loops.
 * 4. Optional methods to toggle GPIO pins using XOR operator.
 *
 * Hardware  : STM32 Discovery Board or STM32 Nucleo, LEDs connected to PA1–PA10
 * Created   : 2026
 *
 * License   : MIT License
 *
 ******************************************************************************
 */

#include <stdint.h>

#define RCC_Base 	0x40021000
#define RCC_AHBENR	(*(volatile uint32_t*)(RCC_Base + 0x14))


#define GPIOA_Base 	0x48000000
#define GPIOA_MODER (*(volatile uint32_t*)(GPIOA_Base + 0x00))
#define GPIOA_ODR   (*(volatile uint32_t*)(GPIOA_Base + 0x14))


#define PORTA_EN 17   // GPIOA enable bit

void delay(void)
{
    for(uint32_t loop = 0; loop < 100000; loop++);
}

int main(void)
{

    /* Enable GPIOA clock */
    RCC_AHBENR |= (1 << PORTA_EN);

    /* PA1 to PA10 as OUTPUT */
    for(int i =1 ; i <= 10; i++)
    {
        GPIOA_MODER &= ~(3 << (i * 2));
        GPIOA_MODER |=  (1 << (i * 2));
    }



    while(1)
    {


            /* Blink All */
            GPIOA_ODR |= 0xFFFF; //0xFFFF = 1111 1111 1111 1111
            delay();
            GPIOA_ODR &= ~0xFFFF;//~0xFFFF = 0000 0000 0000 0000
            delay();


            //------Or we can write in this way-----//

			//(0x03FF << 1); 			  0x3FF = 0000 0011 1111 1111
							//	Shift left by 1 → 0000 0111 1111 1110

            //(0x03FF << 1); 			  0x3FF = 1111 1100 0000 0000
                        									//	Shift left by 1 → 1111 1000 0000 0001

            //------Or we can write using ^ to toggle P1-P10-----//

             // GPIOA_ODR ^= (0x3FF << 1); (Toggling) 1 -> 0
        }

}
