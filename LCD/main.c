/*
 * main.c
 *
 *  Created on: 7 gru 2017
 *      Author: Macko
 */

/*
#include <avr/io.h>
#include <util/delay.h>
#include "HD44780.h"



int main(void){
	LCD_Initalize();

char tekst[20]="KURWA MAC!!!";
	LCD_WriteText(tekst);

while(1){
	int ilosc = (16 - sizeof("KURWA MAC!!!")+1);
			for(int i =0;i<ilosc;i++){
			LCD_WriteCommand(HD44780_SHIFT_DISPLAY|HD44780_DISPLAY_CURSOR_SHIFT|HD44780_SHIFT_RIGHT);
			_delay_ms(300);
			}
			for(int i =0;i<ilosc;i++){
			LCD_WriteCommand(HD44780_SHIFT_DISPLAY|HD44780_DISPLAY_CURSOR_SHIFT|HD44780_SHIFT_LEFT);
			_delay_ms(300);
			}
			for(int i =0;i<3;i++){
				LCD_WriteCommand(HD44780_DISPLAY_ONOFF|HD44780_DISPLAY_OFF);
						_delay_ms(200);
						LCD_WriteCommand(HD44780_DISPLAY_ONOFF|HD44780_DISPLAY_ON);
												_delay_ms(300);
						}

}

	}
*/

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "HD44780.h"

#define KEY_PIN (1<<PB0)

int wartosc_pomiaru;

void wyswietlanie(int);
void czyszczenie(void);


int main(void){
		LCD_Initalize();

		/*int pomiar =2562;
		wyswietlanie(pomiar);
		_delay_ms(2000);

		pomiar =123;
		wyswietlanie(pomiar);
		_delay_ms(2000);

		pomiar =3245;
		wyswietlanie(pomiar);
		_delay_ms(2000);

		czyszczenie();
	LCD_WriteText("LOL"); */

	DDRB &= ~KEY_PIN;			// KEY PIN JAKO WYJSCIE
	PORTB |=KEY_PIN;			// PODCIAGNIECIE KEYPIN DO 5 V


while(1){

	static short zmienna=0;

			if(!(PINB & KEY_PIN)){
				czyszczenie();

				LCD_WriteText("Maciej Zwolan");
			//ustawienie drugiego wiersza
				LCD_WriteCommand((0x80+ 0x40 +0x1));
				LCD_WriteText("Pozdrawiam");
				zmienna = 0;
				//oczekiwanie dopoki jest wcisniety przycisk
					while(!(PINB & KEY_PIN)){
					//LCD_WriteCommand(HD44780_DISPLAY_CURSOR_SHIFT|HD44780_SHIFT_DISPLAY|HD44780_SHIFT_RIGHT);
					_delay_ms(50);
					}
				}
	if(!zmienna){
						czyszczenie();

						//LCD_WriteText("BRAK");

						LCD_WriteText("Maciej Zwolan");
						zmienna = 1;
			}

		}
}


void wyswietlanie(int wartosc_do_wyswietlenia){

		char wartosc_do_wys[2];
		//	char *wsk_wartosc_do_wys;

		// wsk_wartosc_do_wys = (char*)wartosc_do_wys;

		itoa(wartosc_do_wyswietlenia,wartosc_do_wys,10);

		czyszczenie();

		LCD_WriteText("wynik  : ");
		LCD_WriteText(wartosc_do_wys);

	/*while(*wsk_wartosc_do_wys){
				LCD_WriteCommand(HD44780_DISPLAY_CURSOR_SHIFT|HD44780_SHIFT_CURSOR|HD44780_SHIFT_LEFT);
				wsk_wartosc_do_wys++;
			}
*/
}

void czyszczenie(){
	LCD_WriteCommand(HD44780_CLEAR); // czyszczenie zawartosæi pamieci DDRAM
	_delay_ms(2);
	LCD_WriteCommand(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);// inkrementaja adresu i przesuwanie kursora
	LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_ON | HD44780_CURSOR_BLINK);

}

