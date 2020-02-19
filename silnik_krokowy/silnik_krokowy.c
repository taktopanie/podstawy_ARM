/*
 * main.c
 *
 *  Created on: 20 lut 2018
 *      Author: Macko
 *
 *      PROGRAM STERUJ�CY SERVOMECHANIZMEM TYPU TOWER PRO 9G
 *
 *      zakres dzialania 16 - 42 - 70
 */

#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define PIN_PWM1 PB1 	//PIN PWM1
#define PIN_PWM PB2		//PIN PWM2


void lewo(uint8_t);
void prawo(double);

void delay_ms(int czas){
	for(int i = 0; i<czas; i++)
	_delay_ms(1);
}

int main (void){

	int n = 200;

	DDRD=(1<<PD0)|(1<<PD1)|(1<<PD2)|(1<<PD3);

	DDRC&=~(1<<PC0)&~(1<<PC1);

	PORTC&=~(1<<PC0)&~(1<<PC1);
while(1){
//	while(PINC & (1<<PC0)){
			prawo(n);
/*		}
	while(PINC & (1<<PC1)){
			lewo(n);
		}
*/
	/*	uint8_t n = 5;
	while(1){
	for(int i =0;i<40;i++){
	lewo(n);
	}
	_delay_ms(500);

	for(int i =0;i<40;i++){
	prawo(n);
	}
	_delay_ms(500); */



	}
}

void lewo(uint8_t czas){
	PORTD=(1<<PD0);
		_delay_ms(2);
		PORTD=(1<<PD1);
		_delay_ms(2);
		PORTD=(1<<PD2);
		_delay_ms(2);
		PORTD=(1<<PD3);
		_delay_ms(2);
}

void prawo(double czas){
	PORTD=(1<<PD3);
		delay_ms(czas);
		PORTD=(1<<PD2);
		delay_ms(czas);
		PORTD=(1<<PD1);
		delay_ms(czas);
		PORTD=(1<<PD0);
		delay_ms(czas);
}
