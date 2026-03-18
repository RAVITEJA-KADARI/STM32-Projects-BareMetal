/**
 ******************************************************************************
 * @file           : main.c
 * @author         : RAVITEJA KADARI
 * @github         : https://github.com/RAVITEJA-KADARI
 * @brief          : STM32 Bare-Metal DHT11 Temperature & Humidity Display
 ******************************************************************************
 * @attention
 *
 * This project demonstrates:
 * 1. Configuring GPIOA pin as input/output for DHT11 sensor communication.
 * 2. Initializing GPIOC and GPIOD pins for interfacing with a 16x2 LCD
 *    (RS, RW, EN, D0–D7).
 * 3. Implementing DHT11 protocol to read temperature and humidity data:
 *    - Start signal
 *    - Response check
 *    - Reading 5 bytes (RH integer, RH decimal, TEMP integer, TEMP decimal, checksum)
 * 4. Validating checksum to ensure data integrity.
 * 5. Displaying real-time temperature (°C) and humidity (%) on LCD.
 * 6. Handling error conditions (sensor not connected or checksum mismatch).
 *
 * Hardware  : STM32 Discovery/Nucleo Board, DHT11 sensor, 16x2 LCD
 * Created   : 2026
 *
 * License   : MIT License
 *
 ******************************************************************************
 */

#include<stdint.h>

#define RCC_Base		0x40021000
#define RCC_AHBENR		(*(volatile uint32_t*)(RCC_Base + 0x14))


//------for DHT11-------//
#define DHT11_IN	4

#define GPIOA_Base		0x48000000
#define GPIOA_MODER		(*(volatile uint32_t*)(GPIOA_Base + 0x00))
#define GPIOA_IDR		(*(volatile uint32_t*)(GPIOA_Base + 0x10))
#define GPIOA_ODR		(*(volatile uint32_t*)(GPIOA_Base + 0x14))
//#define GPIOA_PUPDR     (*(volatile uint32_t*)(GPIOA_Base + 0x0C))


//-------for LCD RS,RW,EN--------//
#define GPIOC_Base		0x48000800
#define GPIOC_MODER		(*(volatile uint32_t*)(GPIOC_Base + 0x00))
#define GPIOC_ODR		(*(volatile uint32_t*)(GPIOC_Base + 0x14))

//--------For LCD D0-D8)--------//
#define GPIOD_Base		0x48000C00
#define GPIOD_MODER		(*(volatile uint32_t*)(GPIOD_Base + 0x00))
#define GPIOD_ODR		(*(volatile uint32_t*)(GPIOD_Base + 0x14))



#define PORTA_EN	17
#define PORTC_EN	19
#define PORTD_EN	20

#define LCD_RS		0
#define LCD_RW		1
#define LCD_EN		2

#define LCD_D0		8
#define LCD_D1		9
#define LCD_D2		10
#define LCD_D3		11
#define LCD_D4		12
#define LCD_D5		13
#define LCD_D6		14
#define LCD_D7		15

void delay(uint32_t t)
{
	while(t--)
		for(volatile uint32_t i = 0; i < 8000; i++);
}

void delay1(uint32_t t)
{
	while(t--)
		for(volatile uint32_t i = 0; i < 8; i++);
}


void gpio_init(void)
{
	RCC_AHBENR |=  ((1 << PORTA_EN) | (1 << PORTC_EN) | (1 << PORTD_EN));

    GPIOA_MODER &= ~(3 << (DHT11_IN * 2));
    //GPIOA_PUPDR &= ~(3 << (DHT11_IN * 2));
    //GPIOA_PUPDR |=  (1 << (DHT11_IN * 2));

	GPIOC_MODER &= ~((3 << LCD_RS*2) | (3 << LCD_RW*2) | (3 << LCD_EN*2));
	GPIOC_MODER |=  ((1 << LCD_RS*2) | (1 << LCD_RW*2) | (1 << LCD_EN*2));

	for(int i=8;i<=15;i++) {
	    GPIOD_MODER &= ~(3 << (i*2)); // clear
	    GPIOD_MODER |=  (1 << (i*2)); // set as output
	}


	GPIOD_ODR |= ((1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN));

}
void LCD_pulse(void)
{
	GPIOC_ODR |= (1 << LCD_EN);
	delay(2);

	GPIOC_ODR &= ~(1 << LCD_EN);
	delay(2);
}

void LCD_Command(char cmd)
{
	GPIOC_ODR &= ~(1 << LCD_RS);
	GPIOC_ODR &= ~(1 << LCD_RW);
	GPIOD_ODR = (GPIOD_ODR & 0x00FF)| (cmd << 8);
	LCD_pulse();
}

void LCD_data(char data)
{
	GPIOC_ODR |=  (1 << LCD_RS);
	GPIOC_ODR &= ~(1 << LCD_RW);
	GPIOD_ODR  =  (GPIOD_ODR & 0x00FF) | (data << 8);
	LCD_pulse();
}

void LCD_string(char *str)
{
	while(*str){
		LCD_data(*str++);
	}
}

void LCD_init(void)
{
	delay(50);
	LCD_Command(0x01);
	delay(50);
	LCD_Command(0x38);
	delay(50);
	LCD_Command(0x0C);
	delay(50);
	LCD_Command(0x06);
	delay(50);
	LCD_Command(0x01);
	delay(10);
}

void dht_output(void)
{

	GPIOA_MODER &= ~(3 << DHT11_IN*2);
	GPIOA_MODER |=  (1 << DHT11_IN*2);


}

void dht_input(void)
{

	GPIOA_MODER &= ~(3 << DHT11_IN*2);
//    GPIOA_PUPDR &= ~(3 << (DHT11_IN*2));
  //  GPIOA_PUPDR |=  (1 << (DHT11_IN*2));


}

void dht_start(void)
{

	dht_output();

	GPIOA_ODR &= ~(1 << DHT11_IN);
	delay(200);
	GPIOA_ODR |=  (1 << DHT11_IN);
	delay1(300);
	dht_input();

}

uint8_t dht_readbit(void)
{
	while(GPIOA_IDR & (1 << DHT11_IN));
	while(!(GPIOA_IDR & (1 << DHT11_IN)));
	volatile uint32_t count=0;
	while(GPIOA_IDR & (1 << DHT11_IN)) count++;
	return (count>300)?1:0;
}


uint8_t dht_readbyte(void)
{
	uint8_t data = 0;
	for(int i=0;i<8;i++){
		data <<= 1;
		data |= dht_readbit();

	}

	return data;
}

uint8_t dht_check_response(void)
{
    uint32_t count = 0;

    // Wait for DHT11 to pull line LOW (response ~80us)
    while((GPIOA_IDR & (1 << DHT11_IN)) && count++ < 10000);
    if(count >= 10000) return 0;

    count = 0;
    // Wait for DHT11 to pull line HIGH (~80us)
    while(!(GPIOA_IDR & (1 << DHT11_IN)) && count++ < 10000);
    if(count >= 10000) return 0;

    return 1; // OK, response received
}


int main(void)
{

	uint8_t RH_int, RH_dec, TEMP_int, TEMP_dec, checksum;

	gpio_init();
	LCD_init();



	delay(100);
	LCD_Command(0x01);
	LCD_Command(0x80);
	LCD_string("WELCOME");
	delay(200);
	LCD_Command(0xC0);
	LCD_string("DHT11 TESTING");
	delay(200);
	LCD_Command(0x01);
	LCD_Command(0x80);
	LCD_string("DATA INIT...!");
	delay(200);

	while(1)
	{
		dht_start();
		if (!dht_check_response()) {
		    LCD_Command(0x01);
		    LCD_Command(0x80);
		    LCD_string("No DHT11...");
		}
		else
		{
		RH_int = dht_readbyte();
		RH_dec = dht_readbyte();
		TEMP_int = dht_readbyte();
		TEMP_dec = dht_readbyte();
		checksum = dht_readbyte();

		if(checksum != (RH_int + RH_dec + TEMP_int + TEMP_dec))
		{
			LCD_Command(0x01);
			LCD_Command(0x80);
			LCD_string("Error DHT11...!");
			}

		else

		{
			LCD_Command(0x01);
			LCD_Command(0x80);
			LCD_string("TEMP: ");
			LCD_data(TEMP_int/10+'0');
			LCD_data(TEMP_int%10+'0');
			LCD_string("C ");

			LCD_Command(0xC0);
			LCD_string("HUMIDITY: ");
			LCD_data(RH_int/10+'0');
			LCD_data(RH_int%10+'0');
			LCD_string("% ");
			        }


		delay(2000);

	}

	}
}


