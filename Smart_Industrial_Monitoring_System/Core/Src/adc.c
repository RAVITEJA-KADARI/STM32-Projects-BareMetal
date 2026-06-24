/*
 * adc.c
 *
 *  Created on: May 19, 2026
 *      Author: Vishwa teja
 */

#include "stdio.h"
#include "stm32f303_reg.h"
#include "adc.h"

void delay(uint32_t t)
{
	while(t--)
		for(volatile uint32_t i = 0; i < 5000; i++);
}

void adc1_init(void)
{
    // 1️. Enable clocks
    RCC_AHBENR |= (1 << 17) | (1 << 28);
    // PORTA_EN: Enable GPIOA clock
    // (1 << 28): Enable ADC1 & ADC2 clock

    // 2️. Configure PA0 as analog input
    GPIOA_MODER &= ~(3 << (0*2));  // Clear mode bits for PA0
    GPIOA_MODER |=  (3 << (0*2));  // Set PA0 to analog mode (11)
    GPIOA_PUPDR &= ~(1 << (0*2));  // Disable pull-up/pull-down for PA0

    // 3️. Ensure ADC is disabled before configuration
    if(ADC1_CR & 1)              // If ADC enabled
    {
        ADC1_CR |= (1 << 1);     // Disable ADC (ADSTP or ADDIS)
        while(ADC1_CR & 1);      // Wait until ADC fully disabled
    }

    // 4️. Set ADC clock mode
    ADC1_CCR &= ~(3 << 16);      // Clear previous clock mode
    ADC1_CCR |=  (1 << 16);      // Set clock mode (e.g., HCLK / 1)

    // 5️. Enable ADC voltage regulator
    ADC1_CR &= ~(3 << 29);       // Clear bits for voltage regulator
    ADC1_CR |=  (1 << 28);       // Enable ADC internal voltage regulator

    delay(100);                  // Wait ~t ADCVreg for regulator to stabilize

    // 6️. Calibrate ADC
    ADC1_CR |= (1 << 31);        // Start calibration
    while(ADC1_CR & (1 << 31));  // Wait until calibration finishes

    // 7️. Configure ADC behavior
    ADC1_CFGR = 0x00000000;      // Reset CFGR register (default config)
    ADC1_SMPR1 |= (4 << 3);      // Sample time: 100 → 19.5 ADC clock cycles
    ADC1_SQR1 = (1 << 6);        // Set first conversion in sequence to channel 1 (PA0)

    // 8️. Enable ADC
    ADC1_CR |= 1;                // Set ADEN to enable ADC
    while(!(ADC1_CR & 1));       // Wait until ADC is ready

    // 9️. Clear any pending status flags
    ADC1_ISR = 1;                // Clear end-of-conversion (EOC) flag
}
uint32_t adc1_read(void)
{
    // 1️. Start conversion
    ADC1_CR |= (1 << 2);               // Set ADSTART bit

    // 2️. Wait for conversion to complete
    while(!(ADC1_ISR & (1 << 2)));     // Wait for EOC (End of Conversion) flag

    // 3️. Read ADC result
    uint32_t val = ADC1_DR;            // Read converted value

    // 4️. Clear EOC flag
    ADC1_ISR |= (1 << 2);              // Clear EOC to be ready for next conversion

    return val;                        // Return digital value
}

