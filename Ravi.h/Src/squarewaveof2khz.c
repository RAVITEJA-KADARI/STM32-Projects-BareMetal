/*
 * squarewaveof2khz.c
 *
 *  Created on: Nov 23, 2025
 *      Author: Vishwa teja
 */


//Generate a square wave of 2khz on port pin PH0

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

#define TIM6_CCR1		((volatile uint32_t)(TIM6_Base + 0x34))
#define TIM6_CCR2		((volatile uint32_t)(TIM6_Base + 0x38))
#define TIM6_CCR3		((volatile uint32_t)(TIM6_Base + 0x3C))
#define TIM6_CCR4		((volatile uint32_t)(TIM6_Base + 0x40))
#define TIM6_CCMR1		((volatile uint32_t)(TIM6_Base + 0x18))
#define TIM6_CCER		((volatile uint32_t)(TIM6_Base + 0x20))

#define TIM6EN 4
#define IOPEEN 7
#define PORTH 3
#define TIM6CEN 0


void TIM6Delay(uint32_t delay)
{
	TIM6_PSC = 71;
	TIM6_ARR = 999*2;
	TIM6_EGR = 1;
	TIM6_SR = 0;
	TIM6_CR1 |= (1<<TIM6CEN);

	while(!(TIM6_SR & 1));

	TIM6_SR = 0;
	TIM6_CR1 &= ~(1<<TIM6CEN);

}

int main()
{
	RCC->ABHENR |= (1<<PORTH);
	GPIOH->MODER &= ~(3<<0*2);
	GPIOH->MODER |=  (3<<0*2);

}

while(1)
{
	GPIOH->ODR |= (1<<0);
	TIM6Delay(2000);
}
