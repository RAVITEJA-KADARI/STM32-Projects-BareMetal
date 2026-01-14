/*
 * STM32headerfile.h
 *
 *  Created on: Dec 30, 2025
 *      Author: Vishwa teja
 */


#ifndef GLOBALFILE_H_
#define GLOBALFILE_H_

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBRSTR;
	volatile uint32_t CFGR2;
	volatile uint32_t CFGR3;
}RCC_Base;

//defining the ports avalible in GPIO register.
typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
	volatile uint32_t BRR;
}GPIO_Base;

#define RCC   ((RCC_Base*) 0x40021000) //defining the starting address of RCC register
#define GPIOA ((GPIO_Base*)0x48000000) //defining the  address of GPIOA input and output register
#define GPIOB ((GPIO_Base*)0x48000400)//defining the  address of GPIOB input and output register
#define GPIOC ((GPIO_Base*)0x48000800)//defining the  address of GPIOC input and output register
#define GPIOD ((GPIO_Base*)0x48000c00)//defining the  address of GPIOD input and output register
#define GPIOE ((GPIO_Base*)0x48001000)//defining the  address of GPIOE input and output register
#define GPIOF ((GPIO_Base*)0x48001400)//defining the  address of GPIOF input and output register
#define GPIOG ((GPIO_Base*)0x48001800)//defining the  address of GPIOG input and output register
#define GPIOH ((GPIO_Base*)0x48001c00)//defining the  address of GPIOH input and output register

//defining the ports number for input and output connection
#define PORTA 17
#define PORTB 18
#define PORTC 19
#define PORTD 20
#define PORTE 21
#define PORTF 22
#define PORTG 23
#define PORTH 16

#endif /* GLOBALFILE_H_ */
