/*
 * main.c
 *
 *  Created on: 8 gru 2017
 *      Author: Macko
 */

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include"HD44780.h"
#include<stdlib.h>


uint8_t stan;
int czas_w_godz;
int czas_w_min;
int czas_w_s;



void pisanie_na_lcd(int czas_w_godz, int czas_w_min,int czas_w_s){
	LCD_Clear();//wyczysc ekran
	LCD_WriteCommand(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);// inkrementaja adresu i przesuwanie kursora
	//LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK); // w³¹cz LCD, bez kursora i mrugania
	LCD_WriteText("CZAS OD STARTU: ");
	//Przejscie do drugiego wiersza i pierwszego znaku
	LCD_WriteCommand(0x80|0x40|0x00);

	char czas_w_ch_godz[2];
	char czas_w_ch_min[2];
	char czas_w_ch_s[2];

	itoa(czas_w_godz,czas_w_ch_godz,10);
	LCD_WriteText(czas_w_ch_godz);
	LCD_WriteText(" h");

	LCD_WriteCommand(0x80|0x40|0x05);
	itoa(czas_w_min,czas_w_ch_min,10);
	LCD_WriteText(czas_w_ch_min);
	LCD_WriteText("min ");

	LCD_WriteCommand(0x80|0x40|0x0B);
	itoa(czas_w_s,czas_w_ch_s,10);
	LCD_WriteText(czas_w_ch_s);
	LCD_WriteText(" s ");


}



ISR(TIMER1_COMPA_vect){
	PORTB^=(1<<PB0);
	PORTD^=(1<<PD7);



		pisanie_na_lcd(czas_w_godz,czas_w_min,czas_w_s);
		czas_w_s++;

		if(czas_w_s==60){
			czas_w_min++;
			czas_w_s=0;
				if(czas_w_min==60){
					czas_w_godz++;
					czas_w_min=0;
				}

			}

	}






int main (void)
{
	/*
//USTAWIENIE TIMERA I PRZERWANIA 8 bitowego
	TIFR0 |=(1<<OCF0A ) ;
	TCCR0A|=(1<<WGM01);

	TCCR0B|=(1<<CS02)|(1<<CS00);
	TIMSK0=(1<<OCIE0A);

	OCR0A=255;
	sei();
//////////////////////////////////
	*/




	//USTAWIENIE TIMERA I PRZERWANIA 16 bitowego kana³u A
		TIFR1 |=(1<<OCF1A ) ;
		TCCR1B  |=(1<<WGM12);

		TIMSK0 |=(1<<OCIE1A);
		OCR1A=31250;
		sei();


	//PIN B0, D7 JAKO WYJŒCIE i PB1 jako wejœcie
		DDRB|=(1<<PB0);
		DDRB&=~(1<<PB1);
		DDRD|=(1<<PD7);

	//PODCIAGNIECIE WEJSCIA DO 5V I USTAWIENIE DIODY PD7
		PORTD|=(1<<PD7);
		PORTB|=(1<<PB1);

		//LCD
		LCD_Initalize();

	while(1){
		if(!(PINB&(1<<PB1)))
		{
			TCCR1B |=(1<<CS12);//podzielenie 8MHz przez 256
		}
	}

}


