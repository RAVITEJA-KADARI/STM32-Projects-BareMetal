/*
 * uart.c
 *
 *  Created on: May 19, 2026
 *      Author: Vishwa teja
 */


#include "stdio.h"
#include "stm32f303_reg.h"
#include "uart.h"


void usart1_init(void)
{
	RCC_AHBENR |= (1 << 19);

	GPIOC_MODER &= ~((3 << (TxPC4 * 2)));// | (3 << (RxPC5*2)));
	GPIOC_MODER |=  ((2 << (TxPC4 * 2)));// | (2 << (RxPC5*2)));

	GPIOC_AFRL &= ~((0xF << (TxPC4 * 4)));// | (0xF << (RxPC5*4)));
	GPIOC_AFRL |=  ((0x7 << (TxPC4 * 4)));// | (0x7 << (RxPC5*4)));

	RCC_APB2ENR |= (1 << USART1EN);

	USART1_BRR = USART1_Baud_9600;


	USART1_CR1 = USART1_CR1_UE |  USART1_CR1_TE;//	|	USART1_CR1_RE;

}

void usart1_tx_char(char c)
{
	while(!(USART1_ISR & USART1_ISR_TXE));
	USART1_TDR = c;
}

void usart1_print(const char* str)
{

	while(*str)
	{
		usart1_tx_char(*str++);
	}
}
