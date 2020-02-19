/*
 * main.c
 *
 *  Created on: 26 paź 2018
 *      Author: macko
 */


#include<avr/io.h>
#include<util/delay.h>

#define LED_TOGGLE PORTD ^=(1<<PD6)

int main(void){
	DDRD|=(1<<PD6);
	while(1){
		LED_TOGGLE;
		_delay_ms(100);

	}
}
