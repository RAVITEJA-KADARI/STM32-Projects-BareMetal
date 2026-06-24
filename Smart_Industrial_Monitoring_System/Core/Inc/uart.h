/*
 * uart.h
 *
 *  Created on: May 19, 2026
 *      Author: Vishwa teja
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdio.h>
#include <stm32f303_reg.h>

#define TxPC4		4
#define USART1EN	14

//--------USART Registers------//
#define USART1_Base	0x40013800
#define USART1_CR1	(*(volatile uint32_t*)(USART1_Base + 0x00))
#define USART1_BRR	(*(volatile uint32_t*)(USART1_Base + 0x0C))
#define USART1_ISR	(*(volatile uint32_t*)(USART1_Base + 0x1C))
#define USART1_TDR	(*(volatile uint32_t*)(USART1_Base + 0x28))
//#define USART1_RDR  (*(volatile uint32_t*)(USART1_BASE + 0x24))

#define USART1_CR1_UE	(1 << 0)
//#define USART1_CR1_RE   (1 << 2)
#define USART1_CR1_TE	(1 << 3)
#define USART1_ISR_TXE	(1 << 7)
//#define USART1_ISR_RXNE (1 << 5)

#define USART1_Baud_9600  833

void usart1_init(void);
void usart1_tx_char(char c);
void usart1_print(const char* str);

#endif /* INC_UART_H_ */
