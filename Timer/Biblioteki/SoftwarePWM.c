/*
 * SOFTWARE PWM 
 *
 *  Created on: 27 lis 2018
 *      Author: macko
 *
 *
 *      ZACZECIE GENEROWANIA PWM NA 2 PINIE ZACZYNA SIE W CHWILI WYWOLANIA FUNKCJI
 *      Software_PWM()
 *      i Podaniu jej atrbutow
 *      wypenienie i czestotliwosci w Hz(1Hz,5Hz,10Hz,20Hz,50Hz lub 100 Hz)
 */

#include<avr/io.h>
#include<avr/interrupt.h>

volatile int licznik_A;
volatile int licznik_B;
int wypelnienie; // WYPELNIENIE W %
int czestotliwosc; // CZESTOTLIWOSC W HZ
int pin;

int licznik_gora_A;
int licznik_gora_B;
int wypelnienie_licznika_A; // WYPELNIENIE W ILOSCI KROKOW
int wypelnienie_licznika_B; // WYPELNIENIE W ILOSCI KROKOW

void inicjacja_Software_PWM(void){
	// 1 PIN PWM
	DDRD|=(1<<PD2);
	PORTD&=~(1<<PD2);
	// 2 PIN PWM
	DDRD|=(1<<PD3);
	PORTD&=~(1<<PD3);

	TCCR1B |=(1<<WGM12);//Tryb CTC

	TCCR1B |=(1<<CS11);//preskaler 8x czyli 2 MHz
	OCR1A = 200; // liczy w przedziale 0-200

	TIMSK1 |= (1<<OCIE1A);

	sei();
}

void Software_PWM (int czestotliwosc_zadana,int wypelnienie_zadane, int pin){
	if(pin == 5){
	switch(czestotliwosc_zadana){
		case 0:
			//1Hz
			licznik_gora_A = 9900; //100*99;
			wypelnienie_licznika_A = wypelnienie_zadane*100;
			break;
		case 1:
			// 5 Hz
			licznik_gora_A = 1980; //20*99;
			wypelnienie_licznika_A = wypelnienie_zadane*20;
			break;
		case 2:
			// 10 Hz
			licznik_gora_A = 990; //10*99;
			wypelnienie_licznika_A = wypelnienie_zadane*10;
			break;
		case 3:
			// 20 Hz
			licznik_gora_A = 495; //5*99;
			wypelnienie_licznika_A = wypelnienie_zadane*5;
			break;
		case 4:
			// 50 Hz
			licznik_gora_A = 198; //2*99;
			wypelnienie_licznika_A = wypelnienie_zadane*2;
			break;
		case 5:
			// 100 Hz
			licznik_gora_A = 99;
			wypelnienie_licznika_A = wypelnienie_zadane;
			break;
		}
	}else if(pin == 6){
		switch(czestotliwosc_zadana){
			case 0:
				//1Hz
				licznik_gora_B = 9900; //100*99;
				wypelnienie_licznika_B = wypelnienie_zadane*100;
				break;
			case 1:
				// 5 Hz
				licznik_gora_B = 1980; //20*99;
				wypelnienie_licznika_B = wypelnienie_zadane*20;
				break;
			case 2:
				// 10 Hz
				licznik_gora_B = 990; //10*99;
				wypelnienie_licznika_B = wypelnienie_zadane*10;
				break;
			case 3:
				// 20 Hz
				licznik_gora_B = 495; //5*99;
				wypelnienie_licznika_B = wypelnienie_zadane*5;
				break;
			case 4:
				// 50 Hz
				licznik_gora_B = 198; //2*99;
				wypelnienie_licznika_B = wypelnienie_zadane*2;
				break;
			case 5:
				// 100 Hz
				licznik_gora_B = 99;
				wypelnienie_licznika_B = wypelnienie_zadane;
				break;
			}
	}
}



// PRZERWANIA
ISR(TIMER1_COMPA_vect){
	// LICZNIK A
	if(licznik_A == licznik_gora_A && wypelnienie_licznika_A != 0){
	PORTD|=(1<<PD2);
	licznik_A=0;
	}else if(licznik_A == licznik_gora_A){
		licznik_A = 0;
	}
	if(licznik_A == wypelnienie_licznika_A){
	PORTD&=~(1<<PD2);
	}
	// LICZNIK B
	if(licznik_B == licznik_gora_B && wypelnienie_licznika_B != 0){
	PORTD|=(1<<PD3);
	licznik_B=0;
	}else if(licznik_B == licznik_gora_B){
		licznik_B = 0;
	}
	if(licznik_B == wypelnienie_licznika_B){
	PORTD&=~(1<<PD3);
	}

	licznik_B++;
	licznik_A++;

}
