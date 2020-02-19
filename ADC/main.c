/*
 * main.c
 *
 *  Created on: 21 lut 2018
 *      Author: Macko
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART_BIBL.h"
#include <stdlib.h>

int pomiar(int);
uint16_t wartosc_do_sr;

int main(void){


	inicjacja(); // URUCHOMIENIE UART

	ADMUX|=(1<<REFS0); // POD£¥CZENIE WEWNÊTRZNEGO RÓD£A ZASILANIA DO AREF
	ADCSRA|=(1<<ADEN); // W£¥CZENIE ADC
	ADCSRA|=(1<<ADPS1)|(1<<ADPS2); //w³¹czenie preskalera 64


	while(1){
			wartosc_do_sr=0;
		for (uint8_t i=0;i<11;i++){
			wartosc_do_sr=wartosc_do_sr+pomiar(1); // usrednianie wynikow z 10 pomiarow

		}
		uint16_t wartosc_sr_pomiar = wartosc_do_sr/10; // usrednianie wynikow z 10 pomiarow


		double wartosc_do_wysw;
		wartosc_do_wysw = wartosc_sr_pomiar*0.0048; // zamoiana rozdzielczosci na temp


		char wartosc_do_uart[4];
		dtostrf(wartosc_do_wysw,2, 2,wartosc_do_uart);	// ZAMIANA DOUBLE NA CHAR
		//itoa(wartosc_sr_pomiar,wartosc_do_uart,10);	// ZAMIANA INT NA CHAR


		WYSYLANIE_TEXTU(wartosc_do_uart);				// WYSYLANIE POMIARU PRZEZ UART
		WYSYLANIE_TEXTU("\n");
	}
}


int pomiar (int kanal_ADC){

	ADMUX=(ADMUX & 0xF8) | kanal_ADC ; //wybor kanalu do pomiaru
	ADCSRA|=(1<<ADSC); //start conversation

	while(ADCSRA & (1<<ADSC));
	return ADCW;
}
