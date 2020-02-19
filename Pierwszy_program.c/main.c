/*
 * main.c
 *
 *  Created on: 8 lis 2017
 *      Author: Macko
 */

// GENEROWANIE PRZERWABUA GDY wciœniêty przycisk


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define LED_PIN (1<<PC5)
#define KEY_PIN (1<<PC4)
#define KEY_DOWN !(PINC & KEY_PIN)
#define LED_TOG PORTC^=LED_PIN

int main(void){
	//wyjscie
	DDRC|=LED_PIN;
	//wejscie
	DDRC&=~KEY_PIN;
	DDRD&=~(1<<PD2);

	//podci¹gniêcie do 5v
	PORTC|=KEY_PIN|LED_PIN;

	//pod³¹czenie PCINT12 do modu³u przerwañ
	PCMSK1|=(1<<PCINT12);

	EICRA|=(1<<ISC01);
	EIMSK|=(1<<INT0);

	//zezwolenie na przerwanie;
	PCICR |=(1<<PCIE1);

	sei();

		while(1){


		}
}

ISR(PCINT1_vect){
	LED_TOG;


}

ISR(INT0_vect){
	LED_TOG;


}




