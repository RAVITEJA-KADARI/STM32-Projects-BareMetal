/**
 ******************************************************************************
 * @file           : main.c
 * @author         : RAVITEJA KADARI
 * @github         : https://github.com/RAVITEJA-KADARI
 * @brief          : 2-digit 7-segment display counter using STM32 (bare metal)
 ******************************************************************************
 * @attention
 *
 * This project demonstrates register-level GPIO programming
 * on an STM32 microcontroller to drive a multiplexed
 * 2-digit 7-segment display without using HAL or CMSIS.
 *
 * Hardware  : STM32 (Fxx Series)
 * Created   : 2026
 *
 * License   : MIT License
 *
 ******************************************************************************
 */

#include <stdint.h>

#define RCC_BASE       0x40021000
#define RCC_AHBENR     (*(volatile uint32_t*)(RCC_BASE + 0x14))

#define GPIOA_BASE     0x48000000
#define GPIOA_MODER    (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR      (*(volatile uint32_t*)(GPIOA_BASE + 0x14))

#define GPIOB_BASE     0x48000400
#define GPIOB_MODER    (*(volatile uint32_t*)(GPIOB_BASE + 0x00))
#define GPIOB_ODR      (*(volatile uint32_t*)(GPIOB_BASE + 0x14))

#define PORTA_EN       17
#define PORTB_EN       18

void delay(void)
{
    for(uint32_t i = 0; i < 1000; i++);
}

int main(void)
{
    uint8_t Look_up_Table[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
    uint16_t counter = 0;
    uint8_t digits[2];
    uint16_t display_cycles = 0;

    // Enable GPIO clocks
    RCC_AHBENR |= (1 << PORTA_EN);
    RCC_AHBENR |= (1 << PORTB_EN);

    // PA0–PA6 as output
    for(uint8_t i=0;i<7;i++)
    {
        GPIOA_MODER &= ~(3 << (i*2));
        GPIOA_MODER |= (1 << (i*2));
    }

    // PB0–PB1 as output
    for(uint8_t i=0;i<2;i++)
    {
        GPIOB_MODER &= ~(3 << (i*2));
        GPIOB_MODER |= (1 << (i*2));
    }

    while(1)
    {
        digits[0] = counter % 10;
        digits[1] = (counter / 10) % 10;

        // Multiplex displays
        for(uint8_t display = 0; display < 2; display++)
        {
            GPIOB_ODR = (1 << display);
            GPIOA_ODR = Look_up_Table[digits[1 - display]];
            delay();
        }

        display_cycles++;
        if(display_cycles >= 500) // adjust this for slower/faster counting
        {
            counter++;
            if(counter > 99) counter = 0;
            display_cycles = 0;
        }
    }

    return 0;
}


