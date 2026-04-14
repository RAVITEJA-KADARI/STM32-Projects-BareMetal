/*
 * ledwithtimer.c
 *
 *  Created on: Nov 22, 2025
 *      Author: Vishwa teja
 */

//Generate a delay of 1000ms using  Timer0  for blinking LEDs mentioned in assignment1

#include<stdint.h>

#define RCC_Base		0x4002100
#define RCC_AHBENR		((volatile uint32_t)(RCC_Base + 0x14))
#define RCC_APB1ENR		((volatile uint32_t)(RCC_Base + 0x1C))

#define GPIO_Base		0x48001000
#define GPIO_MODER		((volatile uint32_t)(GPIO_Base + 0x00))
#define GPIO_ODR		((volatile uint32_t)(GPIO_Base + 0x14))

#define TIM6_Base		0x40001000
#define TIM6_CR1		((volatile uint32_t)(TIM6_Base + 0x00))
#define TIM6_CR2		((volatile uint32_t)(TIM6_Base + 0x04))
#define TIM6_DIER		((volatile uint32_t)(TIM6_Base + 0x1C))
#define TIM6_SR 		((volatile uint32_t)(TIM6_Base + 0x10))
#define TIM6_EGR 		((volatile uint32_t)(TIM6_Base + 0x14))
#define TIM6_CNT 		((volatile uint32_t)(TIM6_Base + 0x24))
#define TIM6_PSC 		((volatile uint32_t)(TIM6_Base + 0x28))
#define TIM6_ARR 		((volatile uint32_t)(TIM6_Base + 0x2C))

#define TIM6EN 4
#define IOPEEN 21

#define TIM6CEN 0
#define LED 11

void TIM6Delay()
{
	TIM6_PSC = 7999;
	TIM6_ARR = 999;
	TIM6_EGR = 1;
	TIM6_SR = 0;
	TIM6_CR1 |= (1<<TIM6CEN);

	while(!(TIM6_SR & 1));

	TIM6_SR = 0;
	TIM6_CR1 &= ~(1<<TIM6CEN);

}

int main()
{
	RCC->AHBENR  |=   (1<<IOPEEN);
	GPIOE->MODER &= ~(3<<LED*2);
	GPIOE->MODER |=  (3<<LED*2);

	RCC->APB1ENR |= (1<<TIM6EN);

	while(1)
	{
		GPIOE ^= (1<<LED);
		TIM6Delay();
	}

	return 0;
}
