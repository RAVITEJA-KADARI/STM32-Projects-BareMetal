/**
 ******************************************************************************
 * @file           : main.c
 * @author         : RAVITEJA KADARI
 * @github         : https://github.com/RAVITEJA-KADARI
 * @brief          : STM32 Bare-Metal USART Transmit Example
 ******************************************************************************
 * @attention
 *
 * This project demonstrates:
 * 1. Configuring GPIOC pin (PC4) for USART1 TX in alternate function mode.
 * 2. Initializing USART1 peripheral for transmit-only communication at 9600 baud.
 * 3. Sending a test string over USART1 using polling method.
 *
 * Hardware  : STM32 Discovery/Nucleo Board, USART1 interface
 * Created   : 2026
 *
 * License   : MIT License
 *
 ******************************************************************************
 */

#include <stdint.h>

#define RCC_Base	0x40021000
#define RCC_AHBENR	(*(volatile uint32_t*)(RCC_Base + 0x14))
#define RCC_APB2ENR	(*(volatile uint32_t*)(RCC_Base + 0x18))

#define GPIOC_Base	0x48000800
#define GPIOC_MODER	(*(volatile uint32_t*)(GPIOC_Base + 0x00))
#define GPIOC_AFRL	(*(volatile uint32_t*)(GPIOC_Base + 0x20))

#define PORTC_EN	19
#define TxPC4		4
//#define RxPC5		5
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

static void usart1_init(void)
{
	RCC_AHBENR |= (1 << PORTC_EN);

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

static void usart1_print(const char* str)
{

	while(*str)
	{
		usart1_tx_char(*str++);
	}
}


int main(void)
{
  usart1_init();

  usart1_print("HAI, I'M TESTING USART TRANSMIT DATA!\r\n");


}
