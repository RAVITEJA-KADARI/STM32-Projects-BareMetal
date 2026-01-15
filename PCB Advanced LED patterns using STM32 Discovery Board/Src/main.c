/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Raviteja Kadari
 * @github         : https://github.com/RAVITEJA-KADARI
 * @brief          : Advanced LED patterns using STM32 GPIO (bare metal)
 ******************************************************************************
 * @attention
 *
 * This project demonstrates register-level GPIO programming
 * on an STM32 microcontroller to implement multiple LED
 * blinking and pattern-generation techniques.
 *
 * LED Patterns Implemented:
 *  1. Blink All LEDs ON / OFF
 *  2. Running Light (Left to Right)
 *  3. Reverse Running Light (Right to Left)
 *  4. Ping-Pong / Knight Rider Effect
 *  5. Alternate LED Blinking
 *  6. LED Accumulation (Fill & Clear)
 *  7. Binary Counter
 *  8. Pair Blinking (2 LEDs at a Time)
 *
 * GPIO Port : GPIOA (PA0–PA9)
 * Hardware  : STM32 (specify exact model, e.g., STM32F0 / STM32F3)
 * Created   : 2026
 *
 * License   : MIT License
 *
 ******************************************************************************
 */

/*
 1. Blink  All LEDs ON / OFF (Blink All) on board LEDs connected port pins PE8 to PE15 with some delay
"2. Blink the on board LEDs connected port pins PE8 to PE15 in the following:
a) Running Light (Left to Right)  : 00000001 → 00000010 → 00000100 → ... → 10000000
b) Reverse Running Light (Right to Left):  10000000 → 01000000 → ... → 00000001
c) Ping-Pong / Knight Rider:  00000001 → 00000010 → ... → 10000000 → 01000000 → ... → 00000010
d) Alternate LEDs Blinking:  10101010 ↔ 01010101
e) LED Accumulation (Fill & Clear):  00000001 → 00000011 → 00000111 → ... → 11111111 → clear
f) Binary Counter: 00000000 → 00000001 → 00000010 → ... → 11111111
g) Pair Blinking (2 LEDs at a Time):   11000000 → 00110000 → 00001100 → 00000011

}*/

#include <stdint.h>

#define RCC_Base        0x40021000
#define RCC_AHBENR      (*(volatile uint32_t*)(RCC_Base + 0x14))

#define GPIOA_Base      0x48000000
#define GPIOA_MODER     (*(volatile uint32_t*)(GPIOA_Base + 0x00))
#define GPIOA_ODR       (*(volatile uint32_t*)(GPIOA_Base + 0x14))

#define PORTA           17   // GPIOA enable bit

void delay(void)   // normal delay
{
    for(uint32_t loop = 0; loop < 100000; loop++);
}

void long_delay(void)   // longer delay for Blink All
{
    for(uint32_t loop = 0; loop < 1500000; loop++);
}

int main(void)
{
    /* Enable GPIOA clock */
    RCC_AHBENR |= (1 << PORTA);

    /* Configure PA0 to PA9 as output */


    for(int i = 0; i <= 9; i++)
    {
        GPIOA_MODER &= ~(3 << (i * 2));
        GPIOA_MODER |=  (1 << (i * 2));
    }

    GPIOA_ODR = 0;

    while(1)
    {

        /* 1. Blink All LEDs ON / OFF */
    	 for(int i = 0; i <= 2; i++)
    	        {
        GPIOA_ODR |= 0x3FF;     // 10 LEDs ON
        long_delay();
        GPIOA_ODR &= ~0x3FF;    // 10 LEDs OFF
        long_delay();
    	        }

        /* 2a. Running Light (Left to Right) */
    	 for(int i = 0; i <= 2; i++)
    	        {
        for(int i = 0; i <= 9; i++)
        {
            GPIOA_ODR = (1 << i);
            delay();
        }
    	        }
        /* 2b. Reverse Running Light (Right to Left) */
    	 for(int i = 0; i <= 2; i++)
    	        {
        for(int i = 9; i >= 0; i--)
        {
            GPIOA_ODR = (1 << i);
            delay();
        }
    	        }

        /* 2c. Ping-Pong / Knight Rider */
    	 for(int i = 0; i <= 2; i++)
    	        {
        for(int i = 0; i <= 9; i++)
        {
            GPIOA_ODR = (1 << i);
            delay();
        }
        for(int i = 8; i >= 1; i--)
        {
            GPIOA_ODR = (1 << i);
            delay();
        }
    	        }

        /* 2d. Alternate LEDs Blinking */
    	 for(int i = 0; i <= 2; i++)
    	 {
        for(int i = 0; i <= 10; i++)
               {
        GPIOA_ODR = 0x2AA;   // 1010101010
        delay();
        GPIOA_ODR = 0x155;   // 0101010101
        delay();
               }
    	 }
        /* 2e. LED Accumulation (Fill & Clear) */
        uint16_t value = 0;
        for(int i = 0; i < 10; i++)
        {
            value = (value << 1) | 1;
            GPIOA_ODR = value;
            delay();
        }
        GPIOA_ODR = 0;
        delay();

        /* 2f. Binary Counter (0–1023) */
        for(int i = 0; i < 1024; i++)
        {
            GPIOA_ODR = i;
            delay();
        }

        /* 2g. Pair Blinking (2 LEDs at a Time) */
        GPIOA_ODR = 0x300;   // 1100000000
        delay();
        GPIOA_ODR = 0x0C0;   // 0011000000
        delay();
        GPIOA_ODR = 0x030;   // 0000110000
        delay();
        GPIOA_ODR = 0x00C;   // 0000001100
        delay();
        GPIOA_ODR = 0x003;   // 0000000011
        delay();
    }
}
