/* PROGRAM £¥CZ¥CY MIKROKONTROLER Z KOMPUTEREM ZA POMOC¥ UART
*/

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#import<string.h>
#include"stdlib.h"


#define CLK 8000000
#define baud 9600
#define REJESTR_CZAS CLK/16/baud-1

#define ROZMIAR_BUFORA 32
#define Buff_Mask 31 // 0b00011111 ograniczenie z góry

#define LED_ON PORTD&=~(1<<PD7)
#define LED_OFF PORTD|=(1<<PD7)


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
uint8_t stan1;

int main (void){

	USART_INIT(REJESTR_CZAS);

	// Pin PD7 jako wyjscie
	DDRD|=(1<<PD7);
	// Stan wysoki na PD7
	PORTD|=(1<<PD7);

	UCSR0B|=(1<<RXCIE0);

	//zezwolenie na uruchamianie przerwan
		sei();

char tmp_zmienna;
int stan =0;

WYSYLANIE_TEXTU("PROGRAM STERUJACY DIODA \n \naby zapalic diode nacisnij : T \naby zgasic nacisnij : N\n");
while(1){
// pobranie zmiennej z bufora
tmp_zmienna = GET_BYTE();

// jesli bufor zwraca cos innego niz zero to sprawdz co to jest
if(tmp_zmienna){
		if(tmp_zmienna == 'T'|| tmp_zmienna == 't'){
			if(!stan){
				LED_ON;
				WYSYLANIE_TEXTU("\nWLACZAM DIODE\n");
				stan = 1;
			}else{
				WYSYLANIE_TEXTU("\nDIODA JEST AKTUALNIE WLACZONA\n");
			}
		}
		else if(tmp_zmienna == 'N' || tmp_zmienna == 'n'){
			if (stan){
				LED_OFF;
				WYSYLANIE_TEXTU("\nWYLACZAM DIODE\n");
				stan = 0;
			}else{
				WYSYLANIE_TEXTU("\nDIODA JEST AKTUALNIE WYLACZONA\n");
			}

			}
		else{
			WYSYLANIE_TEXTU("\nNIEROZPOZNANE POLECENIE SPRUBUJ JESZCZE RAZ.\n");
		}
	}

}
/*	tmp_zmienna = GET_BYTE();
		if(tmp_zmienna){
			zmienna[i]=tmp_zmienna;
			i++;
			if(tmp_zmienna=='\n'){
				WYSYLANIE_TEXTU(zmienna);
				if(zmienna[0]=='l'){
				PORTC&=~(1<<PC5);
				}else if(zmienna[0]=='k'){
				PORTC|=(1<<PC5);
				}
				for(i=0;i<20;i++)
				zmienna[i]=0;
				i=0;
*/


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

		//if(data == '\n')
		//{
		//WYSYLANIE_TEXTU();
		//}
	}
}
