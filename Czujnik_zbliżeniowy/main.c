/*
 * main.c
 *
 *  Created on: 23 lut 2018
 *      Author: Macko
 *
 *      PROGRAM OBS£UGUJ¥CY CZUJNIK DO POMIARU ODLEG£OŒCI
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "UART_BIBL.h"


#define W_LED (1<<PC5);
#define Y_LED (1<<PC4);
#define R_LED (1<<PC3);

volatile int ilosc_przep;

float pomiar(void);

void wysylanie_do_uart(int watosc_pomiaru);

void zapalenie_diod(float wartosc);



int main(void){

	inicjacja();			// INICJACJA UART


	DDRD|=(1<<PD2);			//PD0 JAKO WYJSCIE TRIG
	DDRD&=~(1<<PD3);		//PD1 JAKO WEJSCIE ECHO

	//INICJACJA TIMERA 2 DO ZLICZANIA CZASU POMIARU
	TCCR2B|=(1<<CS21);//|(1<<CS21)|(1<<CS22);  // ustawienia preskalera 8
	TIMSK2|=(1<<TOIE2);						// uruchomienie przerwania przepe³nienia
	sei();

	DDRC|= (1<<PC5)|(1<<PC4)|(1<<PC3);	// DIODY JAKO WYJSCIA


	while(1){
		float wartosc_pomiaru = pomiar();
		_delay_ms(100);
		//wysylanie_do_uart(wartosc_pomiaru);
		zapalenie_diod(wartosc_pomiaru);


	}

}

// FUNKCJE POBOCZNE
float pomiar(void){
	long int ilosc_cykli=0;
			TCNT2=0;
			ilosc_przep=0;


			PORTD&=~(1<<PD3);	//STAN NISKI NA ECHO



			PORTD|=(1<<PD2);	//STAN WYSOKI NA TRIG
			_delay_us(10);
			PORTD&=~(1<<PD2);	//wy³acz trig
			while(!(PIND & (1<<PD3)));
			while((PIND & (1<<PD3))){
				TCCR2B|=(1<<CS21);		//START POMIARU
			}
			TCCR2B=0;					// STOP POMIARU
			ilosc_cykli = TCNT2+ilosc_przep*0xFF;
			float wartosc_w_cm=ilosc_cykli*340.3/20000;
			return wartosc_w_cm;


}

void wysylanie_do_uart(int watosc_pomiaru){
				char wartosc_do_uart[4];
				dtostrf(watosc_pomiaru,2, 0,wartosc_do_uart);


				//itoa(ilosc_cykli,wartosc_do_uart,10);
				WYSYLANIE_TEXTU(wartosc_do_uart);
				WYSYLANIE_TEXTU("\n");
				_delay_ms(500);

}

void zapalenie_diod(float wartosc){

if(wartosc<5 && wartosc >0){
	PORTC|=R_LED;
	PORTC&=~W_LED;
	PORTC|=Y_LED;
}else if(wartosc<10){
	PORTC|=Y_LED;
	PORTC&=~R_LED;
	PORTC&=~W_LED;
	}else if(wartosc >10 && wartosc<30){
		PORTC|=W_LED;
		PORTC&=~Y_LED;
		PORTC&=~R_LED;
	}else{
		PORTC&=~W_LED;
		PORTC&=~Y_LED;
		PORTC&=~R_LED;
	}
}

// PRZERWANIA
ISR(TIMER2_OVF_vect){

	ilosc_przep++;
}
