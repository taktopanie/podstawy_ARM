/*
 * main.c
 *
 *  Created on: 14 lut 2018
 *      Author: Macko
 *
 *      PROGRAM OBSLUGUHACY WYSWIETLACZ NUMERYCZNY
 *
 *      DANE DO WSZYSKICH DIOD :
 *
 *      	//a
			DDRD|=PIN_11;
			PORTD&=PIN_11;
			//b
			DDRD|=PIN_7;
			PORTD&=PIN_7;
			//c
			DDRD|=PIN_4;
			PORTD&=PIN_4;
			//d
			DDRD|=PIN_2;
			PORTD&=PIN_2;
			//e
			DDRB|=PIN_1;
			PORTB&=PIN_1;
			//f
			DDRD|=PIN_10;
			PORTD&=PIN_10;
			//g
			DDRB|=PIN_5;
			PORTB&=PIN_5;

			//KROPKI
			DDRD|=PIN_3;
			PORTD&=PIN_3;
			 *
 */
#include	<avr/io.h>
#include	<avr/interrupt.h>
#include	<util/delay.h>
#include<stdlib.h>

//anody
#define cyfra_1 (1<<PC5)
#define cyfra_2 (1<<PC4)
#define cyfra_3 (1<<PC3)
#define cyfra_4 (1<<PC2)

//katody
#define PIN_1 (1<<PB0)
#define PIN_2 (1<<PD7)
#define PIN_3 (1<<PD6)
#define PIN_4 (1<<PD5)
#define PIN_5 (1<<PB7)
#define PIN_7 (1<<PD2)
#define PIN_10 (1<<PD1)
#define PIN_11 (1<<PD0)

uint8_t godz_1=1, godz_2=5, min_1=2, min_2=1;

void wybor_liczby(uint8_t);


int main(void){

	////////////////////////////////////////////   TIMER

	OCR1A = 31250;
	TCCR1B|=(1<<WGM12);
	TCCR1B|=(1<<CS12);

	TIMSK1|=(1<<OCIE0A);
	TIFR1|=(1<<OCF1A);
	sei();

	///////////////////////////////////////////////////////


	// zmienna odœwierzania
	uint16_t n=6;

	// PODLACZNIENIE ANOD WYSWIETLACZY
	DDRC|=cyfra_1|cyfra_2|cyfra_3|cyfra_4;


 uint64_t czas = 0x0000;

 	 	 // zapisanie wartosci do zmiennych wyswietlacza
 		godz_1=(czas>>12) & 0x0F;
 		godz_2=(czas>>8) & 0x0F;
 		min_1=(czas>>4) & 0x0F;
 		min_2=(czas) & 0x0F;

	while(1){


		//wybor i wyswietlenie 1 cyfry
	wybor_liczby(godz_1);
	PORTC=cyfra_1;
	_delay_ms(n);

		//wybor i wyswietlenie 2 cyfry
	wybor_liczby(godz_2);
	PORTC=cyfra_2;
	_delay_ms(n);

		//wybor i wyswietlenie 3 cyfry
	wybor_liczby(min_1);
	PORTC=cyfra_3;
	_delay_ms(n);

		//wybor i wyswietlenie 4 cyfry
	wybor_liczby(min_2);
	PORTC=cyfra_4;
	_delay_ms(n);


	}
	return 0;
}


void wybor_liczby(uint8_t liczba){

	switch(liczba)
	{
	case 0 :
		//ZEROWANIE
					DDRD=0;
					DDRB=0;

			//ZAPIS

			//a
			DDRD|=PIN_11;
			PORTD&=PIN_11;
			//b
			DDRD|=PIN_7;
			PORTD&=PIN_7;
			//c
			DDRD|=PIN_4;
			PORTD&=PIN_4;
			//d
			DDRD|=PIN_2;
			PORTD&=PIN_2;
			//e
			DDRB|=PIN_1;
			PORTB&=PIN_1;
			//f
			DDRD|=PIN_10;
			PORTD&=PIN_10;

			break;
	case 1 :
		//ZEROWANIE
					DDRD=0;
					DDRB=0;
			// ZAPIS
			DDRD=(PIN_4)|(PIN_7);
			PORTD&=PIN_4&PIN_7;
			break;

	case 2 :
		//ZEROWANIE
			DDRD=0;
			DDRB=0;
			//ZAPIS
			DDRB|=PIN_1;
			PORTB&=PIN_1;
			DDRD|=PIN_2;
			PORTD&=PIN_2;
			DDRB|=PIN_5;
			PORTB&=PIN_5;
			DDRD|=PIN_7;
			PORTD&=PIN_7;
			DDRD|=PIN_11;
			PORTD&=PIN_11;
			break;

	case 3 :
		//ZEROWANIE
			DDRD=0;
			DDRB=0;
			//ZAPIS
			//a
			DDRD|=PIN_11;
			PORTD&=PIN_11;
			//b
			DDRD|=PIN_7;
			PORTD&=PIN_7;
			//c
			DDRD|=PIN_4;
			PORTD&=PIN_4;
			//d
			DDRD|=PIN_2;
			PORTD&=PIN_2;
			//e
			DDRB|=PIN_5;
			PORTB&=PIN_5;
			break;
	case 4:
		//ZEROWANIE
			DDRD=0;
			DDRB=0;
			//ZAPIS

			//f
			DDRD|=PIN_10;
			PORTD&=PIN_10;
			//g
			DDRB|=PIN_5;
			PORTB&=PIN_5;
			//b
			DDRD|=PIN_7;
			PORTD&=PIN_7;
			//c
			DDRD|=PIN_4;
			PORTD&=PIN_4;
			break;
	case 5:
			//ZEROWANIE
			DDRD=0;
			DDRB=0;
			//ZAPIS
			//a
			DDRD|=PIN_11;
			PORTD&=PIN_11;
			//f
			DDRD|=PIN_10;
			PORTD&=PIN_10;
			//g
			DDRB|=PIN_5;
			PORTB&=PIN_5;
			//c
			DDRD|=PIN_4;
			PORTD&=PIN_4;
			//d
			DDRD|=PIN_2;
			PORTD&=PIN_2;
			break;
	case 6:
		//ZEROWANIE
			DDRD=0;
			DDRB=0;
			//ZAPIS
			//a
			DDRD|=PIN_11;
			PORTD&=PIN_11;
			//c
			DDRD|=PIN_4;
			PORTD&=PIN_4;
			//d
			DDRD|=PIN_2;
			PORTD&=PIN_2;
			//e
			DDRB|=PIN_1;
			PORTB&=PIN_1;
			//f
			DDRD|=PIN_10;
			PORTD&=PIN_10;
			//g
			DDRB|=PIN_5;
			PORTB&=PIN_5;

			break;
	case 7:
		//ZEROWANIE
			DDRD=0;
			DDRB=0;
			//ZAPIS
			//a
			DDRD|=PIN_11;
			PORTD&=PIN_11;
			//c
			DDRD|=PIN_4;
			PORTD&=PIN_4;
			//b
			DDRD|=PIN_7;
			PORTD&=PIN_7;
			break;
	case 8 :
			//ZEROWANIE
				DDRD=0;
				DDRB=0;

			//ZAPIS

			//a
			DDRD|=PIN_11;
			PORTD&=PIN_11;
			//b
			DDRD|=PIN_7;
			PORTD&=PIN_7;
			//c
			DDRD|=PIN_4;
			PORTD&=PIN_4;
			//d
			DDRD|=PIN_2;
			PORTD&=PIN_2;
			//e
			DDRB|=PIN_1;
			PORTB&=PIN_1;
			//f
			DDRD|=PIN_10;
			PORTD&=PIN_10;
			//g
			DDRB|=PIN_5;
			PORTB&=PIN_5;
			break;

	case 9 :
			//ZEROWANIE
				DDRD=0;
				DDRB=0;

			//ZAPIS

			//a
			DDRD|=PIN_11;
			PORTD&=PIN_11;
			//b
			DDRD|=PIN_7;
			PORTD&=PIN_7;
			//c
			DDRD|=PIN_4;
			PORTD&=PIN_4;
			//d
			DDRD|=PIN_2;
			PORTD&=PIN_2;
			//f
			DDRD|=PIN_10;
			PORTD&=PIN_10;
			//g
			DDRB|=PIN_5;
			PORTB&=PIN_5;

			break;

	case 10:
			//KROPKI
			DDRD|=PIN_3;
			PORTD&=PIN_3;
			break;
	}

}

ISR(TIMER1_COMPA_vect){


	min_2++;
	if(min_2==10){
						min_2=0;
						min_1++;
						if(min_1==6){

							min_1=0;
							godz_2++;

							if(godz_2==10){
								godz_2=0;
								godz_1++;
								if(godz_1==10){
									godz_1=0;
								}
							}
						}
				}



	}
