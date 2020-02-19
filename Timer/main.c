/*
 * main.c
 *
 *  Created on: 18 lis 2017
 *      Author: Macko
 */


#include<avr/io.h>
#include<avr/interrupt.h>
#include"Biblioteki/UART_obsluga.h"

int main(void){
	inicjacja_usart();

	TCCR0A |= (1<<WGM01);// CTC mode

	TCCR0B |=(1<<CS00)|(1<<CS02); // preskaler 1024

	TIMSK0 |= (1<<OCIE0A); // przerwanie po zrownaniu z OCRA

	OCR0A = 155;

	sei();

	DDRB |= (1<<PD1);
	while(1){

	}

}

ISR(TIMER0_COMPA_vect){

	WYSYLANIE_TEXTU("taktopanie123456789abcdefghijklmnoprstq");
}
