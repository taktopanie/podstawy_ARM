#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<string.h>
#include<stdlib.h>


#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/atomic.h>

volatile int licznik_A;
volatile int licznik_B;
int wypelnienie; // WYPELNIENIE W %
int czestotliwosc; // CZESTOTLIWOSC W HZ
int pin;

int licznik_gora_A;
int licznik_gora_B;
int wypelnienie_licznika_A; // WYPELNIENIE W ILOSCI KROKOW
int wypelnienie_licznika_B; // WYPELNIENIE W ILOSCI KROKOW


void Software_PWM (int czestotliwosc_zadana,int wypelnienie_zadane, int pin){
	if(pin == 5){
	switch(czestotliwosc_zadana){
		case 0:
			//1Hz
			licznik_gora_A = 100*99;
			wypelnienie_licznika_A = wypelnienie_zadane*100;
			break;
		case 1:
			// 5 Hz
			licznik_gora_A = 20*99;
			wypelnienie_licznika_A = wypelnienie_zadane*20;
			break;
		case 2:
			// 10 Hz
			licznik_gora_A = 10*99;
			wypelnienie_licznika_A = wypelnienie_zadane*10;
			break;
		case 3:
			// 20 Hz
			licznik_gora_A = 5*99;
			wypelnienie_licznika_A = wypelnienie_zadane*5;
			break;
		case 4:
			// 50 Hz
			licznik_gora_A = 2*99;
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
				licznik_gora_B = 100*99;
				wypelnienie_licznika_B = wypelnienie_zadane*100;
				break;
			case 1:
				// 5 Hz
				licznik_gora_B = 20*99;
				wypelnienie_licznika_B = wypelnienie_zadane*20;
				break;
			case 2:
				// 10 Hz
				licznik_gora_B = 10*99;
				wypelnienie_licznika_B = wypelnienie_zadane*10;
				break;
			case 3:
				// 20 Hz
				licznik_gora_B = 5*99;
				wypelnienie_licznika_B = wypelnienie_zadane*5;
				break;
			case 4:
				// 50 Hz
				licznik_gora_B = 2*99;
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


int main(){
DDRD|=(1<<PD2);
PORTD&=~(1<<PD2);

DDRD|=(1<<PD3);
PORTD&=~(1<<PD3);

// zadanie wartosci
czestotliwosc = 5;
wypelnienie = 50;
pin =  6;

TCCR1B |=(1<<WGM12);//Tryb CTC

TCCR1B |=(1<<CS11);//preskaler 8x czyli 2 MHz
OCR1A = 200;


TIMSK1 |= (1<<OCIE1A);

sei();
Software_PWM(czestotliwosc,wypelnienie,5);
Software_PWM(0,20,6);
while(1);
}




// PRZERWANIA
ISR(TIMER1_COMPA_vect){
	// LICZNIK A
	if(licznik_A == licznik_gora_A && wypelnienie_licznika_A > 0){
	PORTD|=(1<<PD2);
	licznik_A=0;
	}else if(licznik_A == licznik_gora_A){
		licznik_A = 0;
	}
	if(licznik_A == wypelnienie_licznika_A){
	PORTD&=~(1<<PD2);
	}
	// LICZNIK B
	if(licznik_B == licznik_gora_B && wypelnienie_licznika_B > 0){
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
