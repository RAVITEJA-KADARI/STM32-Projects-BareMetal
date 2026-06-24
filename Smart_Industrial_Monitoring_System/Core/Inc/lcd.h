/*
 * lcd.h
 *
 *  Created on: May 19, 2026
 *      Author: Vishwa teja
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stdio.h"
#include "stm32f303_reg.h"

#define I2C1_Base		0x40005400
#define I2C1_CR1		(*(volatile uint32_t*)(I2C1_Base + 0x00))
#define I2C1_CR2		(*(volatile uint32_t*)(I2C1_Base + 0x04))
#define I2C1_TIMINGR	(*(volatile uint32_t*)(I2C1_Base + 0x10))
#define I2C1_ISR		(*(volatile uint32_t*)(I2C1_Base + 0x18))
#define I2C1_ICR		(*(volatile uint32_t*)(I2C1_Base + 0x1C))
#define I2C1_TXDR		(*(volatile uint32_t*)(I2C1_Base + 0x28))

#define GPIOB_EN		18
#define I2C1_EN			21

#define LCD_ADDR		0x27
#define RS				0x01
#define RW				0x02
#define EN				0x04
#define BL				0x08

#define SCL				6	//PB6
#define SDA				7	//PB7

void delay_ms(uint32_t t);
void I2C1_init(void);
void I2C1_Write(uint8_t addr, uint8_t data);
void LCD_pulse(uint8_t data);
void LCD_write4(uint8_t nibble, uint8_t rs);
void LCD_send(uint8_t value, uint8_t rs);
void LCD_cmd(uint8_t cmd);
void LCD_data(char data);
void LCD_init(void);
void LCD_string(char *str);


#endif /* INC_LCD_H_ */
