/*
 * przerwania_main.c
 *
 *  Created on: 30 sty 2019
 *      Author: macko
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include"Biblioteki/UART_obsluga.h"

volatile uint16_t licznik;
volatile uint16_t licznik_obrotow;

volatile uint8_t licznik_do_przerwania;


int main(void){


		inicjacja_usart();

		TCCR0A |= (1<<WGM01);// CTC mode

		TCCR0B |=(1<<CS00)|(1<<CS02); // preskaler 1024

		TIMSK0 |= (1<<OCIE0A); // przerwanie po zrownaniu z OCRA

		OCR0A = 155;



	DDRB |= (1<<PB0); // PB0 jako wyjscie
	PORTB &=~ (1<<PB0); // PB0 - stan niski (pull-down)

	DDRD &=~ (1<<PD2); // PD2 jako wejscie
	PORTD |= (1<<PD2); // stan niski na PD2 (int0)

	EICRA |= (1<<ISC01)|(1<<ISC00); // risin edge at int0 generates interrupt

	EIMSK |= (1<<INT0); // enable int0 interrupt

	sei();

	while(1){

	}

}


ISR(INT0_vect){

	licznik ++;
	if(licznik == 34){
	PORTB ^= (1<<PB0);
	licznik_obrotow++;
	licznik = 0;
	}

}

ISR(TIMER0_COMPA_vect){
	licznik_do_przerwania++;

	if(licznik_do_przerwania == 100){
	char zmienna_do_char[2];

	double zmienna = (double)licznik_obrotow/24;

	dtostrf(zmienna,2,2,zmienna_do_char);

	//itoa(licznik_obrotow,zmienna_do_char,10);
	licznik_obrotow = 0;
	WYSYLANIE_TEXTU(zmienna_do_char);
	licznik_do_przerwania = 0;
	}
}
