/*
 * pwm_soft_main.c
 *
 *  Created on: 27 lis 2018
 *      Author: macko
 */

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/atomic.h>

volatile int licznik;
int wypelnienie; // WYPELNIENIE W %

int czestotliwosc; // CZESTOTLIWOSC W HZ

void Software_PWM (int,int);

int main(void){
	Software_PWM(5,100);
	while(1){

	}
}


void Software_PWM (int czestotliwosc_zadana,int wypelnienie_zadane){
	czestotliwosc = czestotliwosc_zadana;
	wypelnienie= wypelnienie_zadane;
	DDRD|=(1<<PD2);

	TCCR1B |=(1<<WGM12);//Tryb fast CTC

	TCCR1B |=(1<<CS11);//preskaler 8x czyli 1 MHz
	switch(czestotliwosc){
	case 1:
		OCR1A=20000;
		break;
	case 5:
		OCR1A= 4000;
		break;
	case 10:
		OCR1A= 2000;
		break;
	case 20:
		OCR1A = 1000;
		break;
	case 50:
		OCR1A = 400;
		break;
	case 100:
		OCR1A = 200;
		break;
	}

	TIMSK1 |= (1<<OCIE1A);

	sei();
}


ISR(TIMER1_COMPA_vect){
	if(licznik == 100){
	PORTD|=(1<<PD2);
	licznik=0;
	}
	if(licznik == wypelnienie){
	PORTD&=~(1<<PD2);
	}
	licznik++;

}

