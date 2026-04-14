/*
 * ledfadesimulation.c
 *
 *  Created on: Nov 11, 2025
 *      Author: Vishwa teja
 */


#include <stdint.h>
#include "globalfile.h"

int main(void)
{
    init_gpio_pin(PORTE, 0);

    while(1)
    {
        for(int i=0;i<100;i++)
        {
            GPIOE->ODR |= (1<<0);
            delay(i*10);
            GPIOE->ODR &= ~(1<<0);
            delay((100-i)*10);
        }

        for(int i=100;i>0;i--)
        {
            GPIOE->ODR |= (1<<0);
            delay(i*10);
            GPIOE->ODR &= ~(1<<0);
            delay((100-i)*10);
        }
    }
    return 0;
}
