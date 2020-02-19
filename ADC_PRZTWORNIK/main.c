/*
 * main.c
 *
 *  Created on: 13 gru 2017
 *      Author: Macko
 */


#include<avr/io.h>
#include<util/delay.h>
#include"HD44780.h"
#include<stdlib.h>
#include<avr/interrupt.h>

void czyszczenie_ekranu(void);
void pisanie_pomiaru(float);
float pomiar(int);

static int stan= 1;

int main(void){

	LCD_Initalize();

	//napiecie referencyjne 5v z mikrokontrolera
	ADMUX|=(1<<REFS0);
	// wlaczenie ADC i ustawienie preskalera
	ADCSRA|=(1<<ADEN)|(1<<ADPS1)|(1<<ADPS2);

	//wlaczenie timera i preskalera 64
	TCCR0B|=(1<<CS00)|(1<<CS02);
	TIMSK0|=(1<<TOIE0);
	TIFR0|=(1<<TOV0);
	sei();

	while(1){
	stan=1;
	float wartosc = pomiar(3);
	pisanie_pomiaru(wartosc);
	stan=0;
	_delay_ms(500);
	}
}


float pomiar (int ch){
			// zapis ktorego kanalu chce uzyc
			ADMUX = (ADMUX & 0xF8) | ch;
			// start pomiaru
			ADCSRA |=(1<<ADSC);
			//dopoki nie zwroci 0
			while(ADCSRA & (1<<ADSC));

			return ADCW;


}
void czyszczenie_ekranu(void){
	LCD_Clear();
	LCD_WriteCommand(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);// inkrementaja adresu i przesuwanie kursora
	LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);

}

void pisanie_pomiaru(float pomiar_int){
	czyszczenie_ekranu();


	float pomiar_f=(pomiar_int*5)/1024;
	char pomiar_char[10];
	//itoa(pomiar_int,pomiar_char,10);
	dtostrf(pomiar_f,1,2,pomiar_char);
	LCD_WriteText("pomiar :");
	LCD_WriteText(pomiar_char);

}

ISR(TIMER0_OVF_vect){
extern int stan;
if(!stan){
	//LCD_WriteCommand(0x80|0x40);
	//LCD_WriteText("text timer");

}


}
