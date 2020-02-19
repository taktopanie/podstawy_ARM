/*
 * UART_obs�uga.c
 *
 *  Created on: 17 pa� 2018
 *      Author: Macko
 */

#include "UART_obsluga.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include <string.h>
#include<stdlib.h>

#define CLK 8000000
#define baud 9600
#define REJESTR_CZAS CLK/16/baud-1

#define ROZMIAR_BUFORA 32
#define Buff_Mask 31 // 0b00011111 ograniczenie z gory

volatile char BUFOR[ROZMIAR_BUFORA];
volatile uint8_t GORA_BUFORA;
volatile uint8_t DOL_BUFORA;


void inicjacja_usart(void){
USART_INIT(REJESTR_CZAS);
UCSR0B|=(1<<RXCIE0);
sei();
}

void USART_INIT (unsigned int predkosc){
	//wyslanie predkosci transmisji
	UBRR0L=(unsigned char)predkosc;
	UBRR0H=(unsigned char)(predkosc>>8);
	//ustawienie przesy�u 8 bitowego 1 bit stopu
	UCSR0C |= (1<UCSZ01)|(1<<UCSZ00);
	//wlaczenie transmitowania i odbierania danych
	UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
	//wlaczenie przerwania gdy przeslane dane
	//UCSR0B|=(1<<TXCIE0);
	}

void USART_WYSYLANIE(char dane){
		while(!UDRE0);
		UDR0 = dane;
		_delay_ms(50);
	}

void WYSYLANIE_TEXTU(char* tekst){
		while(*tekst){
			USART_WYSYLANIE(*tekst);
			tekst++;
		}
}

// funkcja pobierajaca bajt z bufora i zmniejszajaca dol bufora
char GET_BYTE(void){

	if(GORA_BUFORA==DOL_BUFORA) return 0;
	DOL_BUFORA=(DOL_BUFORA+1)&Buff_Mask;
	return BUFOR[DOL_BUFORA];
}



ISR(USART_RX_vect){
	uint8_t tmp_GORA;
	char data;
	data=UDR0;

	tmp_GORA=(GORA_BUFORA+1)&Buff_Mask;
	if(tmp_GORA==DOL_BUFORA){
		//error
	}else{
		GORA_BUFORA=tmp_GORA;
		BUFOR[tmp_GORA]=data;
	}
}
