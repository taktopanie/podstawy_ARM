/*
 * main.c
 *
 *  Created on: 20 lut 2018
 *      Author: Macko
 *
 *      PROGRAM STERUJ¥CY SERVOMECHANIZMEM TYPU TOWER PRO 9G
 *
 *      zakres dzialania 16 - 42 - 70
 */

#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>


#define PIN_SERVO PB1 	//PIN PB1 TO PIN OC1A




int main (void){

	DDRB|= 0xFF;
	//PORTC&=~(1<<PIN_SERVO)
	TCCR1A|=(1<<COM1A1)|(1<<COM1A0); // Inverted mode

	// ustawienie Fast PWM
	TCCR1A|=(1<<WGM11);
	TCCR1B|=(1<<WGM13)|(1<<WGM12);
	// ustawienie licznika


	//ustawienie preskalera
	TCCR1B|=(1<<CS10);

	// PB1 jako wyjscie
	//DDRB|=(1<<PIN_SERVO);

	//wywolanie funkcji odblokowywuj¹cej przerwania
	ICR1=19999;
	//sei();

	//OCR1A=ICR1-12121;

	while(1){
		//OCR1A=ICR1-700;
		//_delay_ms(1000);
		OCR1A=ICR1-1500;
		_delay_ms(1000);
		//OCR1A=ICR1-2500;
		//_delay_ms(1000);
	}
}
