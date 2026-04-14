/*
 * twoledsalternateblink.c
 *
 *  Created on: Nov 11, 2025
 *      Author: Vishwa teja
 */



#include <stdint.h>
#include "globalfile.h"
#define LED0 0
#define LED1 1
int main(void)
{
    init_gpio_pin(PORTE, LED0);
    init_gpio_pin(PORTE, LED1);

    while(1)
    {
        GPIOE->ODR ^= (1 << LED0);  // Toggle PE0
        GPIOE->ODR ^= (1 << LED1);  // Toggle PE1
        delay(500);
    }
    return 0;
}
