/*
 * ledblinkprtc.c
 *
 *  Created on: Nov 9, 2025
 *      Author: Vishwa teja
 */

//led blink code

#include <stdint.h>
#include <globalfile.h>

void delay(){

	for(uint32_t loop=0;loop<1000;loop++);

}

int main(){


	RCC -> AHBENR |= (3<<PORTC);


	for(int i=0;i<=8;i++)
	{


		GPIOC -> MODER &= ~(3<<(i*2));
		GPIOC -> MODER |=  (1<<(i*2));

	}
		while(1){

			for(i=0;i<=8;i++)
			{

				GPIOE -> ODR &= ~(1<<i);
				delay();
				GPIOE -> ODR |=  (1<<i);
				delay();
			}
		}
	return 0;
}






//led blink code

#include <stdint.h>
#include <globalfile.h>

void delay(){

	for(uint32_t loop=0;loop<1000;loop++);

}

int main(){

	RCC -> AHBENR |= (1<<PORTC);

	for(i=0;i<8;i++){

			GPIOC -> MODER &= ~(3<<(i*2));
			GPIOC -> MODER |= (1<<(i*2));
	}
		while(1){

			for(i=0;i<8;i++){

				GPIOE -> ODR &= ~(1<<i);
				delay();
				GPIOE -> ODR |= (1<<i);
				delay();
			}


		}
	return 0;
}




//led increment program

#include <stdint.h>
#include <globalfile.h>

void delay(){

	for(uint32_t loop=0;loop<1000;loop++);
}

int main(){

	RCC -> AHBENR |= (3<<PORTB);

	for(i=0;i<8;i++){

		GPIOB -> MODER &= ~(i<<(i*2));
		GPIOB -> MODER |= (i<<(i*2));
	}
			while(1){

				for(i=0;i<=3;i++){

					//GPIOB -> ODR &= ~(1<<i);
					//delay();
					GPIOB -> ODR |=  (1<<i);
					delay();
				}

				for(i=3;i>=0;i--){

					//GPIOB -> ODR &= ~(1<<i);
					//delay();
					GPIOB -> ODR |=  (1<<i);
					delay();
				}
			}
		return 0;
}







//led code with switch

#include<stdint.h>
#include<globalfile.h>

void delay(){

	for(uint32_t loop=0;loop<1000;loop++);
}

int main(){

	for(i=0;i<=15;i++){

		RCC -> AHBENR |= (1<<PORTA);
		RCC -> AHBENR |= (1<<PORTB);


		GPIOA -> MODER &= ~(3<<(i*2));
		GPIOA -> MODER |=  (1<<(i*2));

		GPIOB -> MODER &= ~(3<<0*2);
		GPIOB -> IDR   |=  (1<<1);

	}

	while(1){

		for(i=0;i<=8;i++){

			GPIOA -> ODR |= (1<<i);
			delay();
			GPIOA -> ODR |= (1<<i);
			delay();
		}
	}

	return 0;
}



//switch buzz code

#include<stdint.h>
#include<globalfile.h>

void delay(){

	for(uint32_t loop=0;loop<1000;loop++);
}

int main(){

	RCC -> AHBENR |= (1<<PORTC);
	RCC -> AHBENR |= (1<<PORTA);

		GPIOA -> MODER &= ~(3<<(0*2));

		GPIOC -> MODER &= ~(1<<(0*2));
		GPIOC -> MODER |=  (1<<(0*2));


		while(1){

			if(GPIOA -> IDR & (1<<0)){

				GPIOC -> ODR |= (1<<0);

			  }
				else {

					GPIOC -> ODR &= ~(1<<0);

				    }
			delay();
		}

		return 0;

	}










