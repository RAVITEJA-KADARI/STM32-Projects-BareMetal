/*
 * stm32f303_reg.h
 *
 *  Created on: May 19, 2026
 *      Author: Vishwa teja
 */

#ifndef INC_STM32F303_REG_H_
#define INC_STM32F303_REG_H_

#ifndef STM32F303_REG_H
#define STM32F303_REG_H

#include <stdint.h>

/*=====================================================
                        RCC
=====================================================*/

#define RCC_Base               0x40021000

#define RCC_CR                 (*(volatile uint32_t*)(RCC_Base + 0x00))
#define RCC_CFGR               (*(volatile uint32_t*)(RCC_Base + 0x04))
#define RCC_CIR                (*(volatile uint32_t*)(RCC_Base + 0x08))
#define RCC_APB2RSTR           (*(volatile uint32_t*)(RCC_Base + 0x0C))
#define RCC_APB1RSTR           (*(volatile uint32_t*)(RCC_Base + 0x10))
#define RCC_AHBENR             (*(volatile uint32_t*)(RCC_Base + 0x14))
#define RCC_APB2ENR            (*(volatile uint32_t*)(RCC_Base + 0x18))
#define RCC_APB1ENR            (*(volatile uint32_t*)(RCC_Base + 0x1C))
#define RCC_BDCR               (*(volatile uint32_t*)(RCC_Base + 0x20))
#define RCC_CSR                (*(volatile uint32_t*)(RCC_Base + 0x24))
#define RCC_AHBRSTR            (*(volatile uint32_t*)(RCC_Base + 0x28))
#define RCC_CFGR2              (*(volatile uint32_t*)(RCC_Base + 0x2C))
#define RCC_CFGR3              (*(volatile uint32_t*)(RCC_Base + 0x30))

/*=====================================================
                        GPIOA
=====================================================*/

#define GPIOA_Base             0x48000000

#define GPIOA_MODER            (*(volatile uint32_t*)(GPIOA_Base + 0x00))
#define GPIOA_OTYPER           (*(volatile uint32_t*)(GPIOA_Base + 0x04))
#define GPIOA_OSPEEDR          (*(volatile uint32_t*)(GPIOA_Base + 0x08))
#define GPIOA_PUPDR            (*(volatile uint32_t*)(GPIOA_Base + 0x0C))
#define GPIOA_IDR              (*(volatile uint32_t*)(GPIOA_Base + 0x10))
#define GPIOA_ODR              (*(volatile uint32_t*)(GPIOA_Base + 0x14))
#define GPIOA_BSRR             (*(volatile uint32_t*)(GPIOA_Base + 0x18))
#define GPIOA_LCKR             (*(volatile uint32_t*)(GPIOA_Base + 0x1C))
#define GPIOA_AFRL             (*(volatile uint32_t*)(GPIOA_Base + 0x20))
#define GPIOA_AFRH             (*(volatile uint32_t*)(GPIOA_Base + 0x24))
#define GPIOA_BRR              (*(volatile uint32_t*)(GPIOA_Base + 0x28))

/*=====================================================
                        GPIOB
=====================================================*/

#define GPIOB_Base             0x48000400

#define GPIOB_MODER            (*(volatile uint32_t*)(GPIOB_Base + 0x00))
#define GPIOB_OTYPER           (*(volatile uint32_t*)(GPIOB_Base + 0x04))
#define GPIOB_OSPEEDR          (*(volatile uint32_t*)(GPIOB_Base + 0x08))
#define GPIOB_PUPDR            (*(volatile uint32_t*)(GPIOB_Base + 0x0C))
#define GPIOB_IDR              (*(volatile uint32_t*)(GPIOB_Base + 0x10))
#define GPIOB_ODR              (*(volatile uint32_t*)(GPIOB_Base + 0x14))
#define GPIOB_BSRR             (*(volatile uint32_t*)(GPIOB_Base + 0x18))
#define GPIOB_LCKR             (*(volatile uint32_t*)(GPIOB_Base + 0x1C))
#define GPIOB_AFRL             (*(volatile uint32_t*)(GPIOB_Base + 0x20))
#define GPIOB_AFRH             (*(volatile uint32_t*)(GPIOB_Base + 0x24))
#define GPIOB_BRR              (*(volatile uint32_t*)(GPIOB_Base + 0x28))

/*=====================================================
                        GPIOC
=====================================================*/

#define GPIOC_Base             0x48000800

#define GPIOC_MODER            (*(volatile uint32_t*)(GPIOC_Base + 0x00))
#define GPIOC_OTYPER           (*(volatile uint32_t*)(GPIOC_Base + 0x04))
#define GPIOC_OSPEEDR          (*(volatile uint32_t*)(GPIOC_Base + 0x08))
#define GPIOC_PUPDR            (*(volatile uint32_t*)(GPIOC_Base + 0x0C))
#define GPIOC_IDR              (*(volatile uint32_t*)(GPIOC_Base + 0x10))
#define GPIOC_ODR              (*(volatile uint32_t*)(GPIOC_Base + 0x14))
#define GPIOC_BSRR             (*(volatile uint32_t*)(GPIOC_Base + 0x18))
#define GPIOC_LCKR             (*(volatile uint32_t*)(GPIOC_Base + 0x1C))
#define GPIOC_AFRL             (*(volatile uint32_t*)(GPIOC_Base + 0x20))
#define GPIOC_AFRH             (*(volatile uint32_t*)(GPIOC_Base + 0x24))
#define GPIOC_BRR              (*(volatile uint32_t*)(GPIOC_Base + 0x28))

/*=====================================================
                        GPIOD
=====================================================*/

#define GPIOD_Base             0x48000C00

#define GPIOD_MODER            (*(volatile uint32_t*)(GPIOD_Base + 0x00))
#define GPIOD_OTYPER           (*(volatile uint32_t*)(GPIOD_Base + 0x04))
#define GPIOD_OSPEEDR          (*(volatile uint32_t*)(GPIOD_Base + 0x08))
#define GPIOD_PUPDR            (*(volatile uint32_t*)(GPIOD_Base + 0x0C))
#define GPIOD_IDR              (*(volatile uint32_t*)(GPIOD_Base + 0x10))
#define GPIOD_ODR              (*(volatile uint32_t*)(GPIOD_Base + 0x14))
#define GPIOD_BSRR             (*(volatile uint32_t*)(GPIOD_Base + 0x18))
#define GPIOD_LCKR             (*(volatile uint32_t*)(GPIOD_Base + 0x1C))
#define GPIOD_AFRL             (*(volatile uint32_t*)(GPIOD_Base + 0x20))
#define GPIOD_AFRH             (*(volatile uint32_t*)(GPIOD_Base + 0x24))
#define GPIOD_BRR              (*(volatile uint32_t*)(GPIOD_Base + 0x28))

/*=====================================================
                        GPIOE
=====================================================*/

#define GPIOE_Base             0x48001000

#define GPIOE_MODER            (*(volatile uint32_t*)(GPIOE_Base + 0x00))
#define GPIOE_OTYPER           (*(volatile uint32_t*)(GPIOE_Base + 0x04))
#define GPIOE_OSPEEDR          (*(volatile uint32_t*)(GPIOE_Base + 0x08))
#define GPIOE_PUPDR            (*(volatile uint32_t*)(GPIOE_Base + 0x0C))
#define GPIOE_IDR              (*(volatile uint32_t*)(GPIOE_Base + 0x10))
#define GPIOE_ODR              (*(volatile uint32_t*)(GPIOE_Base + 0x14))
#define GPIOE_BSRR             (*(volatile uint32_t*)(GPIOE_Base + 0x18))
#define GPIOE_LCKR             (*(volatile uint32_t*)(GPIOE_Base + 0x1C))
#define GPIOE_AFRL             (*(volatile uint32_t*)(GPIOE_Base + 0x20))
#define GPIOE_AFRH             (*(volatile uint32_t*)(GPIOE_Base + 0x24))
#define GPIOE_BRR              (*(volatile uint32_t*)(GPIOE_Base + 0x28))

/*=====================================================
                        GPIOF
=====================================================*/

#define GPIOF_Base             0x48001400

#define GPIOF_MODER            (*(volatile uint32_t*)(GPIOF_Base + 0x00))
#define GPIOF_OTYPER           (*(volatile uint32_t*)(GPIOF_Base + 0x04))
#define GPIOF_OSPEEDR          (*(volatile uint32_t*)(GPIOF_Base + 0x08))
#define GPIOF_PUPDR            (*(volatile uint32_t*)(GPIOF_Base + 0x0C))
#define GPIOF_IDR              (*(volatile uint32_t*)(GPIOF_Base + 0x10))
#define GPIOF_ODR              (*(volatile uint32_t*)(GPIOF_Base + 0x14))
#define GPIOF_BSRR             (*(volatile uint32_t*)(GPIOF_Base + 0x18))
#define GPIOF_LCKR             (*(volatile uint32_t*)(GPIOF_Base + 0x1C))
#define GPIOF_AFRL             (*(volatile uint32_t*)(GPIOF_Base + 0x20))
#define GPIOF_AFRH             (*(volatile uint32_t*)(GPIOF_Base + 0x24))
#define GPIOF_BRR              (*(volatile uint32_t*)(GPIOF_Base + 0x28))

/*=====================================================
                        GPIOG
=====================================================*/

#define GPIOG_Base             0x48001800

#define GPIOG_MODER            (*(volatile uint32_t*)(GPIOG_Base + 0x00))
#define GPIOG_OTYPER           (*(volatile uint32_t*)(GPIOG_Base + 0x04))
#define GPIOG_OSPEEDR          (*(volatile uint32_t*)(GPIOG_Base + 0x08))
#define GPIOG_PUPDR            (*(volatile uint32_t*)(GPIOG_Base + 0x0C))
#define GPIOG_IDR              (*(volatile uint32_t*)(GPIOG_Base + 0x10))
#define GPIOG_ODR              (*(volatile uint32_t*)(GPIOG_Base + 0x14))
#define GPIOG_BSRR             (*(volatile uint32_t*)(GPIOG_Base + 0x18))
#define GPIOG_LCKR             (*(volatile uint32_t*)(GPIOG_Base + 0x1C))
#define GPIOG_AFRL             (*(volatile uint32_t*)(GPIOG_Base + 0x20))
#define GPIOG_AFRH             (*(volatile uint32_t*)(GPIOG_Base + 0x24))
#define GPIOG_BRR              (*(volatile uint32_t*)(GPIOG_Base + 0x28))

/*=====================================================
                        GPIOH
=====================================================*/

#define GPIOH_Base             0x48001C00

#define GPIOH_MODER            (*(volatile uint32_t*)(GPIOH_Base + 0x00))
#define GPIOH_OTYPER           (*(volatile uint32_t*)(GPIOH_Base + 0x04))
#define GPIOH_OSPEEDR          (*(volatile uint32_t*)(GPIOH_Base + 0x08))
#define GPIOH_PUPDR            (*(volatile uint32_t*)(GPIOH_Base + 0x0C))
#define GPIOH_IDR              (*(volatile uint32_t*)(GPIOH_Base + 0x10))
#define GPIOH_ODR              (*(volatile uint32_t*)(GPIOH_Base + 0x14))
#define GPIOH_BSRR             (*(volatile uint32_t*)(GPIOH_Base + 0x18))
#define GPIOH_LCKR             (*(volatile uint32_t*)(GPIOH_Base + 0x1C))
#define GPIOH_AFRL             (*(volatile uint32_t*)(GPIOH_Base + 0x20))
#define GPIOH_AFRH             (*(volatile uint32_t*)(GPIOH_Base + 0x24))
#define GPIOH_BRR              (*(volatile uint32_t*)(GPIOH_Base + 0x28))


//defining the ports number for input and output connection
#define PORTA_EN 17
#define PORTB_EN 18
#define PORTC_EN 19
#define PORTD_EN 20
#define PORTE_EN 21
#define PORTF_EN 22
#define PORTG_EN 23
#define PORTH_EN 16

#endif


#endif /* INC_STM32F303_REG_H_ */
