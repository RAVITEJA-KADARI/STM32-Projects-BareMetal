/*
 * sevensegmentdisplay.c
 *
 *  Created on: Nov 21, 2025
 *      Author: Vishwa teja
 */

//Seven segment displays segments a,b,c,d,e,f,g,h are connected to port pins PC0 to PC7, write embedded firmware for displaying  numbers 1 to 9 on the seven segment display


#include <stdint.h>
#include "ravi.h"

// Lookup table for digits 0–9
int Look_Up_Table[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

// Simple software delay
void delay(uint32_t time)
{
    for(uint32_t i=0; i<time*1000; i++);
}

int main(void)
{
    uint8_t Counter = 0;

    // Enable GPIOC clock
    RCC->AHBENR |= (1 << PORTC);

    // Configure PC0–PC7 as output (assuming 7 segments are connected to PC0–PC7)
    for(int i=0; i<8; i++) {
        GPIOC->MODER &= ~(3 << (i*2)); // Clear mode
        GPIOC->MODER |=  (1 << (i*2)); // Set as output
    }

    while(1)
    {
        GPIOB->ODR = Look_Up_Table[Counter]; // Display digit
        delay(500); // ~500 ms delay

        Counter++;
        if(Counter > 9)
            Counter = 0; // Reset after 9
    }
}
