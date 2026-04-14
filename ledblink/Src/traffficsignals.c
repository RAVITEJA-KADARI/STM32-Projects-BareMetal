/*
 * traffficsignals.c
 *
 *  Created on: Nov 11, 2025
 *      Author: Vishwa teja
 */


//Traffic Lights Controller



#include<stdint.h>
#define RCC_Base        0x40021000
#define RCC_AHBENR      ((volatile uint32_t)(RCC_Base + 0x14))
#define GPIOA_Base      0x48000800
#define GPIOA_MODER     ((volatile uint32_t)(GPIOA_Base + 0x00))
#define GPIOA_ODR      ((volatile uint32_t)(GPIOA_Base + 0x14))
void delay(uint32_t counter)
{
	while(counter)
	{
		for(uint32_t loop = 0; loop < 1000; loop++);
		counter --;
	}
}


#define S_RED 0
#define S_ORG 1
#define S_GRN 2

#define N_RED 3
#define N_ORG 4
#define N_GRN 5

#define E_RED 6
#define E_ORG 7
#define E_GRN 8

#define W_RED 9
#define W_ORG 10
#define W_GRN 11

int main()
{
	RCC_AHBENR  |=  (1 << 17);

	GPIOA_MODER &= ~((3 << S_RED*2) | (3 << S_ORG*2) | (3 << S_GRN*2) |\
					 (3 << N_RED*2) | (3 << N_ORG*2) | (3 << N_GRN*2) |\
					 (3 << E_RED*2) | (3 << E_ORG*2) | (3 << E_GRN*2) |\
					 (3 << W_RED*2) | (3 << W_ORG*2) | (3 << W_GRN*2) );

	GPIOA_MODER |=  ((1 << S_RED*2) | (1 << S_ORG*2) | (1 << S_GRN*2) |\
					 (1 << N_RED*2) | (1 << N_ORG*2) | (1 << N_GRN*2) |\
					 (1 << E_RED*2) | (1 << E_ORG*2) | (1 << E_GRN*2) |\
					 (1 << W_RED*2) | (1 << W_ORG*2) | (1 << W_GRN*2) );


	GPIOA_ODR   &= ~((1 << S_RED) | (1 << S_ORG) | (1 << S_GRN) |\
					 (1 << N_RED) | (1 << N_ORG) | (1 << N_GRN) |\
					 (1 << E_RED) | (1 << E_ORG) | (1 << E_GRN) |\
					 (1 << W_RED) | (1 << W_ORG) | (1 << W_GRN) );
	while(1)
	{
//--------EAST Side Green --> ON, RED --> OFF, ORG --> OFF---------
    GPIOA_ODR &= ~(1 << E_RED); // RED LIGHT OFF
    GPIOA_ODR &= ~(1 << E_ORG); // ORG LIGHT OFF
    GPIOA_ODR |=  (1 << E_GRN); // GRN LIGHT ON

    GPIOA_ODR |=  (1 << W_RED); // RED LIGHT ON
    GPIOA_ODR &= ~(1 << W_ORG); // ORG LIGHT OFF
    GPIOA_ODR &= ~(1 << W_GRN); // GRN LIGHT OFF

    GPIOA_ODR |=  (1 << N_RED); // RED LIGHT ON
    GPIOA_ODR &= ~(1 << N_ORG); // ORG LIGHT OFF
    GPIOA_ODR &= ~(1 << N_GRN); // GRN LIGHT OFF

    GPIOA_ODR |=  (1 << S_RED); // RED LIGHT ON
    GPIOA_ODR &= ~(1 << S_ORG); // ORG LIGHT OFF
    GPIOA_ODR &= ~(1 << S_GRN); // GRN LIGHT OFF
	delay(28000);

//--------WEST Side Green --> ON, RED --> OFF, ORG --> OFF---------
	GPIOA_ODR |=  (1 << E_RED); // RED LIGHT ON
    GPIOA_ODR &= ~(1 << E_ORG); // ORG LIGHT OFF
    GPIOA_ODR &= ~(1 << E_GRN); // GRN LIGHT OFF

	GPIOA_ODR &= ~(1 << W_RED); // RED LIGHT OFF
    GPIOA_ODR |=  (1 << W_ORG); // ORG LIGHT ON
    GPIOA_ODR &= ~(1 << W_GRN); // GRN LIGHT OFF
    delay(1000);
    GPIOA_ODR &= ~(1 << W_RED); // RED LIGHT OFF
    GPIOA_ODR &= ~(1 << W_ORG); // ORG LIGHT OFF
    GPIOA_ODR |=  (1 << W_GRN); // GRN LIGHT ON

    GPIOA_ODR |=  (1 << N_RED); // RED LIGHT ON
    GPIOA_ODR &= ~(1 << N_ORG); // ORG LIGHT OFF
    GPIOA_ODR &= ~(1 << N_GRN); // GRN LIGHT OFF

    GPIOA_ODR |=  (1 << S_RED); // RED LIGHT ON
    GPIOA_ODR &= ~(1 << S_ORG); // ORG LIGHT OFF
    GPIOA_ODR &= ~(1 << S_GRN); // GRN LIGHT OFF
	delay(28000);

//--------NORTH Side Green --> ON, RED --> OFF, ORG --> OFF---------
	GPIOA_ODR |=  (1 << E_RED); // RED LIGHT ON
    GPIOA_ODR &= ~(1 << E_ORG); // ORG LIGHT OFF
    GPIOA_ODR &= ~(1 << E_GRN); // GRN LIGHT OFF


    GPIOA_ODR |=  (1 << W_RED); // RED LIGHT On
    GPIOA_ODR &= ~(1 << W_ORG); // ORG LIGHT OFF
    GPIOA_ODR &= ~(1 << W_GRN); // GRN LIGHT Off

    GPIOA_ODR &= ~(1 << N_RED); // RED LIGHT OFF
    GPIOA_ODR |=  (1 << N_ORG); // ORG LIGHT ON
    GPIOA_ODR &= ~(1 << N_GRN); // GRN LIGHT OFF
    delay(1000);
    GPIOA_ODR &= ~(1 << N_RED); // RED LIGHT OFF
    GPIOA_ODR &= ~(1 << N_ORG); // ORG LIGHT OFF
    GPIOA_ODR |=  (1 << N_GRN); // GRN LIGHT ON

    GPIOA_ODR |=  (1 << S_RED); // RED LIGHT ON
    GPIOA_ODR &= ~(1 << S_ORG); // ORG LIGHT OFF
    GPIOA_ODR &= ~(1 << S_GRN); // GRN LIGHT OFF
	delay(28000);


//--------SOUTH Side Green --> ON, RED --> OFF, ORG --> OFF---------
	GPIOA_ODR |=  (1 << E_RED); // RED LIGHT ON
    GPIOA_ODR &= ~(1 << E_ORG); // ORG LIGHT OFF
    GPIOA_ODR &= ~(1 << E_GRN); // GRN LIGHT OFF


    GPIOA_ODR |=  (1 << W_RED); // RED LIGHT ON
    GPIOA_ODR &= ~(1 << W_ORG); // ORG LIGHT OFF
    GPIOA_ODR &= ~(1 << W_GRN); // GRN LIGHT Off

    GPIOA_ODR |=  (1 << N_RED); // RED LIGHT ON
    GPIOA_ODR &= ~(1 << N_ORG); // ORG LIGHT OFF
    GPIOA_ODR &= ~(1 << N_GRN); // GRN LIGHT OFF

    GPIOA_ODR &= ~(1 << S_RED); // RED LIGHT OFF
    GPIOA_ODR |=  (1 << S_ORG); // ORG LIGHT ON
    GPIOA_ODR &= ~(1 << S_GRN); // GRN LIGHT OFF
	delay(1000);
	GPIOA_ODR &= ~(1 << S_RED); // RED LIGHT OFF
    GPIOA_ODR &= ~(1 << S_ORG); // ORG LIGHT OFF
    GPIOA_ODR |=  (1 << S_GRN); // GRN LIGHT ON
	delay(28000);
	}

}
