/*
 * adc.h
 *
 *  Created on: May 19, 2026
 *      Author: Vishwa teja
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stdio.h"
#include "stm32f303_reg.h"

#define ADC1_Base 		0x50000000
#define ADC_COMMON_BASE 0x50000300

#define ADC1_ISR		(*(volatile uint32_t*)(ADC1_Base + 0x00))
#define ADC1_IER		(*(volatile uint32_t*)(ADC1_Base + 0x04))
#define ADC1_CR 		(*(volatile uint32_t*)(ADC1_Base + 0x08))
#define ADC1_CFGR 		(*(volatile uint32_t*)(ADC1_Base + 0x0C))
#define ADC1_SMPR1 		(*(volatile uint32_t*)(ADC1_Base + 0x14))
#define ADC1_SQR1		(*(volatile uint32_t*)(ADC1_Base + 0x30))
#define ADC1_DR 		(*(volatile uint32_t*)(ADC1_Base + 0x40))

#define ADC1_CCR 		(*(volatile uint32_t*)(ADC_COMMON_BASE + 0x08))

void delay(uint32_t t);
void adc1_init(void);
uint32_t adc1_read(void);

#endif /* INC_ADC_H_ */
