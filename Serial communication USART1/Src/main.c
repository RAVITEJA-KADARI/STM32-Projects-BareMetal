/*#include <stdint.h>

#define RCC_BASE        0x40021000
#define RCC_AHBENR      (*(volatile uint32_t*)(RCC_BASE + 0x14))
#define RCC_APB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x18))

#define GPIOE_BASE      0x48001000
#define GPIOE_MODER     (*(volatile uint32_t*)(GPIOE_BASE + 0x00))
#define GPIOE_ODR       (*(volatile uint32_t*)(GPIOE_BASE + 0x14))

#define GPIOD_BASE      0x48000C00
#define GPIOD_MODER     (*(volatile uint32_t*)(GPIOD_BASE + 0x00))
#define GPIOD_ODR       (*(volatile uint32_t*)(GPIOD_BASE + 0x14))

#define GPIOC_BASE      0x48000800
#define GPIOC_MODER     (*(volatile uint32_t*)(GPIOC_BASE + 0x00))
#define GPIOC_AFRL      (*(volatile uint32_t*)(GPIOC_BASE + 0x20))


#define USART1_BASE     0x40013800
#define USART1_CR1      (*(volatile uint32_t*)(USART1_BASE + 0x00))  // Turning Usart on/off
#define USART1_BRR      (*(volatile uint32_t*)(USART1_BASE + 0x0C))  // Set speed of sending and receiving  data
#define USART1_ISR      (*(volatile uint32_t*)(USART1_BASE + 0x1C))  //shows status incoming and outgoing
#define USART1_RDR      (*(volatile uint32_t*)(USART1_BASE + 0x24))  //receive data
#define USART1_TDR      (*(volatile uint32_t*)(USART1_BASE + 0x28))  //send data



#define PORTE_EN        		21			// 	PORTE  LCD Control Lines
#define PORTD_EN        		20			// 	PORTD  LCD Data line

#define LCD_RS          		8   		// 	PE8
#define LCD_RW          		9   		// 	PC9
#define LCD_EN          		10   		// 	PC10

#define LCD_D0          		8			//	PD8
#define LCD_D1          		9			//	PD9
#define LCD_D2          		10			//	PD10
#define LCD_D3          		11			//	PD11
#define LCD_D4          		12			//	PD12
#define LCD_D5          		13			//	PD13
#define LCD_D6          		14			//	PD14
#define LCD_D7          		15			//	PD15


void _delay_ms(uint16_t i)
{
	while(i)
	{
		for(uint16_t k = 0; k < 1000; k++);
		i--;
	}
}


void gpio_init(void)
{
    RCC_AHBENR  |=  (1 << PORTE_EN) | (1 << PORTD_EN);

    GPIOE_MODER &= ~(0xFF);             // 1111 1111
    GPIOE_MODER |=  ((1 << LCD_RS * 2) | (1 << LCD_RW * 2) | (1 << LCD_EN * 2));

    GPIOD_MODER &= ~(0xFFFF << 16);		// 1111 1111 1111 1111
    GPIOD_MODER |=  (0x5555 << 16);		// 0101 0101 0101 0101

    GPIOE_ODR   &= ~((1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN));
}


void lcd_pulse(void)
{
    GPIOE_ODR |=  (1 << LCD_EN);
    _delay_ms(1);

    GPIOE_ODR &= ~(1 << LCD_EN);
    _delay_ms(2);
}


void lcd_command(char cmd)
{
    GPIOE_ODR &= ~(1 << LCD_RS);  // 0 = it is in command mode sending command
    GPIOE_ODR &= ~(1 << LCD_RW);  // writing data to lcd
    GPIOD_ODR  =  (GPIOD_ODR & 0x00FF) | (cmd << 8);
    lcd_pulse();
}

void lcd_data(char data)
{
    GPIOE_ODR |=  (1 << LCD_RS);   // 1 = sending data
    GPIOE_ODR &= ~(1 << LCD_RW);  // writing data to lcd
    GPIOD_ODR  =  (GPIOD_ODR & 0x00FF) | (data << 8);
    lcd_pulse();
}


void lcd_init(void)
{
    _delay_ms(20);
    lcd_command(0x38);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_command(0x01);
    _delay_ms(2);
}


void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}


#define USART_CR1_UE    		(1 << 0)  // 1 = Usart enable | 0 = Usart disable
#define USART_CR1_RE    		(1 << 2)  // receive data
#define USART_CR1_TE    		(1 << 3)  //transmit data
#define USART_ISR_RXNE  		(1 << 5)  //Receive not empty  - received data sucessfully
#define USART_ISR_TXE   		(1 << 7)  //Transmit empty - ready to receive from rx

#define USART1_BAUD_9600   		833		//0x33E   	// 	= 8M / 115200 ≈ 69.44

#define TxPC4					4
#define RxPC5					5
#define USART1EN				14
#define PORTC_EN				19

static void uart1_init(void)
{

    RCC_AHBENR  |=  (1 << PORTC_EN);

    GPIOC_MODER &= ~((3    << (TxPC4*2)) | (3    << (RxPC5*2)));
    GPIOC_MODER |=  ((2    << (TxPC4*2)) | (2    << (RxPC5*2)));

    GPIOC_AFRL  &= ~((0xF  << (TxPC4*4)) | (0xF  << (RxPC5*4)));
    GPIOC_AFRL  |=  ((0x07 << (TxPC4*4)) | (0x07 << (RxPC5*4)));


    RCC_APB2ENR |= (1 << USART1EN);

    USART1_BRR = USART1_BAUD_9600;		// CPU f / Baud Rate = BRR Value = // 8000000 / 9600

    USART1_CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}



void uart1_tx_char(char c)
{
    while (!(USART1_ISR & USART_ISR_TXE));
    USART1_TDR = c;
}

char uart1_rx_char(void)
{
    while (!(USART1_ISR & USART_ISR_RXNE));
    return USART1_RDR;
}




static void uart1_print(const char* s)
{
    while (*s)
    {
        uart1_tx_char(*s++);
    }
    uart1_tx_char('\n');
}

int main(void)
{
    gpio_init();
    lcd_init();
    uart1_init();

    lcd_command(0x80);
	lcd_string("Testing USART!");
	lcd_command(0xC0);
	lcd_string("Communication!");
	_delay_ms(2000);

    uart1_print("USART1 READY!     ");
    uart1_print("TYPE ANY CHARACTER..");

    char c = uart1_rx_char();
	lcd_command(0x01);


    while(1)
    {
    	 lcd_command(0x80);
    	 for(int i = 0; i < 16; i++)
    	 {
    		 lcd_data(c);
    		 c = uart1_rx_char();
    	 }


    	 lcd_command(0xC0);
    	 for(int i = 0; i < 16; i++)
    	 {
    		 lcd_data(c);
    		 c = uart1_rx_char();
    	 }
    	 lcd_command(0x01);
    	 _delay_ms(500);
    }
}*/


#include <stdint.h>

#define RCC_BASE        0x40021000
#define RCC_AHBENR      (*(volatile uint32_t*)(RCC_BASE + 0x14))
#define RCC_APB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x18))

#define GPIOE_BASE      0x48001000
#define GPIOE_MODER     (*(volatile uint32_t*)(GPIOE_BASE + 0x00))
#define GPIOE_ODR       (*(volatile uint32_t*)(GPIOE_BASE + 0x14))

#define GPIOD_BASE      0x48000C00
#define GPIOD_MODER     (*(volatile uint32_t*)(GPIOD_BASE + 0x00))
#define GPIOD_ODR       (*(volatile uint32_t*)(GPIOD_BASE + 0x14))

#define GPIOC_BASE      0x48000800
#define GPIOC_MODER     (*(volatile uint32_t*)(GPIOC_BASE + 0x00))
#define GPIOC_AFRL      (*(volatile uint32_t*)(GPIOC_BASE + 0x20))

#define USART1_BASE     0x40013800
#define USART1_CR1      (*(volatile uint32_t*)(USART1_BASE + 0x00))  // Turning Usart on/off
#define USART1_BRR      (*(volatile uint32_t*)(USART1_BASE + 0x0C))  // Set speed of sending and receiving  data
#define USART1_ISR      (*(volatile uint32_t*)(USART1_BASE + 0x1C))  //shows status incoming and outgoing
#define USART1_RDR      (*(volatile uint32_t*)(USART1_BASE + 0x24))  //receive data
#define USART1_TDR      (*(volatile uint32_t*)(USART1_BASE + 0x28))  //send data


#define PORTE_EN        		21			// 	PORTE  LCD Control Lines
#define PORTD_EN        		20			// 	PORTD  LCD Data line

#define LCD_RS          		8   		// 	PE8
#define LCD_RW          		9   		// 	PC9
#define LCD_EN          		10   		// 	PC10

#define LCD_D0          		8			//	PD8
#define LCD_D1          		9			//	PD9
#define LCD_D2          		10			//	PD10
#define LCD_D3          		11			//	PD11
#define LCD_D4          		12			//	PD12
#define LCD_D5          		13			//	PD13
#define LCD_D6          		14			//	PD14
#define LCD_D7          		15			//	PD15


void _delay_ms(uint16_t i)
{
	while(i)
	{
		for(uint16_t k = 0; k < 1000; k++);
		i--;
	}
}


void gpio_init(void)
{
    RCC_AHBENR  |=  (1 << PORTE_EN) | (1 << PORTD_EN);

    GPIOE_MODER &= ~(0xFF);             // 1111 1111
    GPIOE_MODER |=  ((1 << LCD_RS * 2) | (1 << LCD_RW * 2) | (1 << LCD_EN * 2));

    GPIOD_MODER &= ~(0xFFFF << 16);		// 1111 1111 1111 1111
    GPIOD_MODER |=  (0x5555 << 16);		// 0101 0101 0101 0101

    GPIOE_ODR   &= ~((1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN));
}


void lcd_pulse(void)
{
    GPIOE_ODR |=  (1 << LCD_EN);
    _delay_ms(1);

    GPIOE_ODR &= ~(1 << LCD_EN);
    _delay_ms(2);
}


void lcd_command(char cmd)
{
    GPIOE_ODR &= ~(1 << LCD_RS);  // 0 = it is in command mode sending command
    GPIOE_ODR &= ~(1 << LCD_RW);  // writing data to lcd
    GPIOD_ODR  =  (GPIOD_ODR & 0x00FF) | (cmd << 8);
    lcd_pulse();
}

void lcd_data(char data)
{
    GPIOE_ODR |=  (1 << LCD_RS);   // 1 = sending data
    GPIOE_ODR &= ~(1 << LCD_RW);  // writing data to lcd
    GPIOD_ODR  =  (GPIOD_ODR & 0x00FF) | (data << 8);
    lcd_pulse();
}


void lcd_init(void)
{
    _delay_ms(20);
    lcd_command(0x38);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_command(0x01);
    _delay_ms(2);
}


void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}


#define USART_CR1_UE    		(1 << 0)  // 1 = Usart enable | 0 = Usart disable
#define USART_CR1_RE    		(1 << 2)  // receive data
#define USART_CR1_TE    		(1 << 3)  //transmit data
#define USART_ISR_RXNE  		(1 << 5)  //Receive not empty  - received data sucessfully
#define USART_ISR_TXE   		(1 << 7)  //Transmit empty - ready to receive from rx

#define USART1_BAUD_9600   		833		//0x33E   	// 	= 8M / 9600 ≈ 69.44

#define TxPC4					4
#define RxPC5					5
#define USART1EN				14
#define PORTC_EN				19

static void uart1_init(void)
{

    RCC_AHBENR  |=  (1 << PORTC_EN);

    GPIOC_MODER &= ~((3    << (TxPC4*2)) | (3    << (RxPC5*2)));
    GPIOC_MODER |=  ((2    << (TxPC4*2)) | (2    << (RxPC5*2)));

    GPIOC_AFRL  &= ~((0xF  << (TxPC4*4)) | (0xF  << (RxPC5*4)));
    GPIOC_AFRL  |=  ((0x07 << (TxPC4*4)) | (0x07 << (RxPC5*4)));


    RCC_APB2ENR |= (1 << USART1EN);

    USART1_BRR = USART1_BAUD_9600;		// CPU f / Baud Rate = BRR Value = // 8000000 / 9600

    USART1_CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}



void uart1_tx_char(char c)
{
    while (!(USART1_ISR & USART_ISR_TXE));
    USART1_TDR = c;
}

char uart1_rx_char(void)
{
    while (!(USART1_ISR & USART_ISR_RXNE));
    return USART1_RDR;
}

static void uart1_print(const char* s)
{
    while (*s)
    {
        uart1_tx_char(*s++);
    }
    uart1_tx_char('\n');
}

// Buffer to store received characters
#define BUFFER_SIZE 32
char uart_buffer[BUFFER_SIZE];
uint8_t buffer_index = 0;

void uart1_receive_string(void)
{
    char c;
    while (buffer_index < BUFFER_SIZE)
    {
        c = uart1_rx_char();  // Receive character
        uart_buffer[buffer_index++] = c;  // Store in buffer

        if (c == '\n' || buffer_index >= BUFFER_SIZE)  // End of line or buffer full
        {
            uart_buffer[buffer_index] = '\0';  // Null-terminate string
            break;
        }
    }
}

int main(void)
{
    gpio_init();
    lcd_init();
    uart1_init();

    _delay_ms(2000);
    lcd_command(0x80);
    lcd_string("WELCOME ");
    _delay_ms(1500);
    lcd_command(0xC0);
    lcd_string("ALL..!");
    _delay_ms(2000);

    lcd_command(0x01);

    lcd_command(0x80);
    lcd_string("Testing USART!");
    lcd_command(0xC0);
    lcd_string("Communication!");
    _delay_ms(2000);

    uart1_print("USART1 READY!     ");
    uart1_print("TYPE ANY CHARACTER..");

    while (1)
    {
        uart1_receive_string();  // Receive a string of characters

        // Clear display and print the buffer on LCD
        lcd_command(0x01);  // Clear the display
        lcd_command(0x80);  // Move cursor to first line
        for (int i = 0; i< 16 && i < buffer_index; i++)
        {
            lcd_data(uart_buffer[i]);  // Display each character
        }
        if (buffer_index > 16)
               {
        lcd_command(0xc0);  // Move cursor to first line
        for (int i = 16; i < buffer_index; i++)
        {
            lcd_data(uart_buffer[i]);  // Display each character
        }
               }
        buffer_index = 0;  // Reset buffer index for the next string

        _delay_ms(500);  // Optional delay before receiving next string
    }
}




