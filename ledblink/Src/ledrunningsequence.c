/*
 * ledrunningsequence.c
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

    while(1)
    {
        for(int i=0;i<4;i++)
        {
            GPIOE->ODR = (1 << i);
            delay(200);
        }
    }
    return 0;
}
