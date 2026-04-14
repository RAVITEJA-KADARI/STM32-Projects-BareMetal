/*
 * binarycounterleds.c
 *
 *  Created on: Nov 11, 2025
 *      Author: Vishwa teja
 */



#include <stdint.h>
#include "globalfile.h"

int main(void)
{
    for(int i=0;i<4;i++)
        init_gpio_pin(PORTE, i);

    uint8_t counter = 0;

    while(1)
    {
        GPIOE->ODR = counter;  // Output counter to LEDs
        counter = (counter + 1) & 0xF;
        delay(500);
    }
    return 0;
}
