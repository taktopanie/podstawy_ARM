/*
 * program.c
 *
 *  Created on: 8 maj 2018
 *      Author: Macko
 */


#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#define CLK 8000000
#define baud 9600
#define REJESTR_CZAS CLK/16/baud-1

#define ROZMIAR_BUFORA 32
#define Buff_Mask 31 // 0b00011111 ograniczenie z góry

#define PIN_SERVO PB2 	//PIN PB1 TO PIN OC1B PWM


//definicje funkcji
void USART_INIT(unsigned int);
void USART_WYSYLANIE(char);
void WYSYLANIE_TEXTU(char*);
char GET_BYTE(void);

//definicje zmiennych
volatile char BUFOR[ROZMIAR_BUFORA];
volatile uint8_t GORA_BUFORA;
volatile uint8_t DOL_BUFORA;
volatile uint8_t stan;


int main (void){

	USART_INIT(REJESTR_CZAS);


		TCCR1A|=(1<<COM1B1); //Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM (non-inverting mode)

		// ustawienie Fast PWM
		TCCR1A|=(1<<WGM11);
		TCCR1B|=(1<<WGM13)|(1<<WGM12);



		//ustawienie preskalera clk/8 = 1 000 000 Hz
		TCCR1B|=(1<<CS11);

		// PB1 jako wyjscie
		DDRB|=(1<<PIN_SERVO);
		// ustawienie licznika
		ICR1=19999;


		// PINY POD UART
	DDRC&=~(1<<PC5);
	PORTC|=(1<<PC5);
	UCSR0B|=(1<<RXCIE0);
	//zezwolenie na uruchamianie przerwan
		sei();

	//WYSYLANIE_TEXTU("PODAJ KIERUNEK \n\n L = LEWO, P = PRAWO, S = SRODEK : ");


		// OCR1A POWINNO MIEC WARTOSC LEWO = 16 SRODEK = 42 PRAWO = 70

	char zmienna,tmp_zmienna;

	while(1){
		tmp_zmienna = GET_BYTE();
		if(tmp_zmienna){
			zmienna=tmp_zmienna;

			if(tmp_zmienna=='L' || tmp_zmienna=='l'){
				//WYSYLANIE_TEXTU("\nLEWO\n");
				OCR1A=16;
			}else if(tmp_zmienna=='P'|| tmp_zmienna=='p'){
				//WYSYLANIE_TEXTU("\nPRAWO\n");
				OCR1A=70;

			}else if(tmp_zmienna=='S'|| tmp_zmienna=='s'){
				//WYSYLANIE_TEXTU("\nSRODEK\n");
				OCR1B=1805;
				}else{
				//	WYSYLANIE_TEXTU("\nNIE ZNAM KOMENDY\n");
				};
			}

		}

	}




void USART_INIT (unsigned int predkosc){
	//wyslanie predkosci transmisji
	UBRR0L=(unsigned char)predkosc;
	UBRR0H=(unsigned char)(predkosc>>8);
	//ustawienie przesy³u 8 bitowego 1 bit stopu
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

		if(data == '\n')
		{
		//WYSYLANIE_TEXTU();
		}
	}
}
