/*
 * timers6,3.c
 *
 *  Created on: Nov 22, 2025
 *      Author: Vishwa teja
 */


#include<stdint.h>

#define RCC_Base		0x40021000
#define RCC_AHBENR 		((volatile uint32_t)(RCC_Base + 0x14))
#define RCC_APB1ENR 	((volatile uint32_t)(RCC_Base + 0x1C))

#define GPIOE_Base		0x48001000
#define GPIOE_MODER		((volatile uint32_t)(GPIOE_Base + 0x00))
#define GPIOE_ODR		((volatile uint32_t)(GPIOE_Base + 0x14))

#define TIM6_Base		0x40001000
#define TIM6_CR1    	((volatile uint32_t)(TIM6_Base + 0x00))
#define TIM6_CR2    	((volatile uint32_t)(TIM6_Base + 0x04))
#define TIM6_DIER    	((volatile uint32_t)(TIM6_Base + 0x0C))
#define TIM6_SR    		((volatile uint32_t)(TIM6_Base + 0x10))
#define TIM6_EGR    	((volatile uint32_t)(TIM6_Base + 0x14))
#define TIM6_CNT    	((volatile uint32_t)(TIM6_Base + 0x24))
#define TIM6_PSC    	((volatile uint32_t)(TIM6_Base + 0x28))
#define TIM6_ARR    	((volatile uint32_t)(TIM6_Base + 0x2C))


//Register definition
#define TIM6EN 	4
#define IOPEEN 	21


//Bit definition
#define TIM6CEN 0
#define LED 	11



void Time6Delay()
{

	TIM6_PSC = 7999;     				// Setup the Pre Scaler to 1 milliSec
	TIM6_ARR = 999*3;     				// Load the ARR with required multiplier to get 1 sec
	TIM6_EGR = 1;        				// Generate update event (load PSC and ARR)
	TIM6_SR = 0;         				// Clear update flag
	TIM6_CR1 |= (1 << TIM6CEN);       	// Enable counter

	while (!(TIM6_SR & 1));				// Wait for overflow

	TIM6_SR = 0;         				// Clear flag
	TIM6_CR1 &= ~(1 << TIM6CEN); ;      // Stop timer

}


int main()
{
	RCC_AHBENR  |= (1 << IOPEEN);
	GPIOE_MODER &= (3 << LED*2);
	GPIOE_MODER |= (1 << LED*2);

	RCC_APB1ENR |= (1 << TIM6EN);

	while(1)
	{
		GPIOE_ODR ^= (1 << LED);
		Time6Delay();
	}
	return 0;
}
