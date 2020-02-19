/*
 * main.c
 *
 *  Created on: 18 lis 2017
 *      Author: Macko
 */


#include <avr/io.h>

#define PIN_DIODY (1<<PC5)
#define PRZYCISK_DIODA (1<<PC4)


int main(void){

	DDRC|=PIN_DIODY;
	PORTC|=PIN_DIODY;
	DDRC&=~PRZYCISK_DIODA;
	PORTC|=PRZYCISK_DIODA;


	while(1){

		PORTC|=PIN_DIODY;

		while(!(PINC & PRZYCISK_DIODA)){
			PORTC&=~PIN_DIODY;
		}

	}

}
