/*
 * wyswietlacz.c
 *
 *  Created on: 14 sie 2018
 *      Author: Macko
 */
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include<stdlib.h>

// DEFINIOWANIE CZY UZYWAMY PINU RW
#define LCD_USE_RW 1

// DEFINIOWANIE PINOW DO WYSWIETLACZA
#define RS_PIN (1<<PC5)
#define RS_PORT PORTC
#define RS_DDR DDRC
#define RW_PIN (1<<PC4)
#define RW_PORT PORTC
#define RW_DDR DDRC
#define E_PIN (1<<PC3)
#define E_PORT PORTC
#define E_DDR DDRC
#define DATA4_PIN (1<<PC2)
#define DATA4_PORT PORTC
#define DATA4_DDR DDRC
#define DATA5_PIN (1<<PC1)
#define DATA5_PORT PORTC
#define DATA5_DDR DDRC
#define DATA6_PIN (1<<PC0)
#define DATA6_PORT PORTC
#define DATA6_DDR DDRC
#define DATA7_PIN (1<<PB1)
#define DATA7_PORT PORTB
#define DATA7_DDR DDRB


// definiowanie lini wyswietlacza
#define LCD_LINE1 0x00
#define LCD_LINE2 0x40

// stan wysoki na RS
#define Set_RS RS_PORT|=RS_PIN
// stan niski na RS
#define Reset_RS RS_PORT&=~RS_PIN

// stan wysoki na RW
#define Set_RW RW_PORT|=RW_PIN
// stan niski na RW
#define Reset_RW RW_PORT&=~RW_PIN

// stan wysoki na E
#define Set_E E_PORT|=E_PIN
// stan niski na E
#define Reset_E E_PORT&=~E_PIN




// funkcje wyswietlacza

#define SET_DDRAM_ADDR (1<<7)

#define SET_CGRAM_ADDR (1<<6)

#define FUNCTION_SET (1<<5)
	#define DATA_LENGHT_8BIT (1<<4)
	#define DATA_LENGHT_4BIT (0<<4)
	#define NUMBER_OF_LINES_1 (0<<3)
	#define NUMBER_OF_LINES_2 (1<<3)
	#define CHARACTER_FONT_5x10 (1<<2)
	#define CHARACTER_FONT_5x8 (0<<2)

#define LCD_CURSOR_DISPLAY_SHIFT (1<<4)
	#define DISPLAY_SHIFT (1<<3)
	#define CURSOR_SHIFT (0<<3)
	#define SHIFT_RIGHT (1<<2)
	#define SHIFT_LEFT (0<<2)

#define LCD_ONOFF (1<<3)
	#define LCD_DISPLAY_ON (1<<2)
	#define LCD_DISPLAY_OFF (0<<2)
	#define LCD_COURSOR_ON (1<<1)
	#define LCD_COURSOR_OFF (0<<1)
	#define LCD_BLINKINGCOURSOR_ON (1<<0)
	#define LCD_BLINKINGCOURSOR_OFF (0<<0)

#define ENTRY_MODE (1<<2)
	#define INCREMENT (1<<1)
	#define DECREMENT (0<<1)
	#define DISPLAY_SHIFT_ON (1<<0)
	#define DISPLAY_SHIFT_OFF (0<<0)

#define LCD_RETURN_HOME (1<<1)

#define LCD_CLEAR (1<<0)


// funkcja wysylajaca polbajt poniewaz korzystam z 4 pinow
void lcd_sendHalf(uint8_t data){
	if(data&(1<<0)){
		DATA4_PORT|=DATA4_PIN;
		}else{DATA4_PORT&=~DATA4_PIN;}

	if(data&(1<<1)){
		DATA5_PORT|=DATA5_PIN;
		}else{DATA5_PORT&=~DATA5_PIN;}

	if(data&(1<<2)){
		DATA6_PORT|=DATA6_PIN;
		}else{DATA6_PORT&=~DATA6_PIN;}

	if(data&(1<<3)){
		DATA7_PORT|=DATA7_PIN;
		}else{DATA7_PORT&=~DATA7_PIN;}
}

//funkcja ustawiajaca piny jako wyjsca
void data_dir_out(void){
	// USTAWIENIE WYJSC PINOW
	DATA4_DDR |= DATA4_PIN;
	DATA5_DDR |= DATA5_PIN;
	DATA6_DDR |= DATA6_PIN;
	DATA7_DDR |= DATA7_PIN;
}

// funkcja wysylajaca caly bajt
void lcd_sendbyte(unsigned char data){
	// ustawienie pinów jako wyjsc
	data_dir_out();
	Set_E;
	lcd_sendHalf(data>>4);
	Reset_E;

	Set_E;
	lcd_sendHalf(data);
	Reset_E;

	_delay_us(120);
}

// funkcja wpisywania komend
void lcd_send_command(unsigned char wartosc){
	Reset_RS;
	lcd_sendbyte(wartosc);
}

// funkcja wpisywania danych
void lcd_send_data(unsigned char wartosc){
	Set_RS;
	lcd_sendbyte(wartosc);
}

//funkcja inicjujaca wyswietlacz
void lcd_init(void){
	data_dir_out();
	RS_DDR |= RS_PIN;
	RW_DDR |= RW_PIN;
	E_DDR |= E_PIN;
	// wyzerowanie pinow RS,RW,E
	Reset_RS;
	Reset_RW;
	Reset_E;
	_delay_ms(50);

	Reset_RS;
	Reset_RW;

	lcd_sendHalf(0b0011);
	_delay_ms(4.1);
	lcd_sendHalf(0b0011);
	_delay_us(100);
	lcd_sendHalf(0b0011);
	_delay_us(100);
	lcd_sendHalf(0b0010);


	// ustawienie 4bitow 2 wierszy i rozdzielczosci znakow
	lcd_send_command(FUNCTION_SET|DATA_LENGHT_4BIT|NUMBER_OF_LINES_2|CHARACTER_FONT_5x8);
	_delay_ms(100);
	// wylaczenie wyswietlacza
	lcd_send_command(LCD_ONOFF|LCD_DISPLAY_ON|LCD_BLINKINGCOURSOR_ON);
	_delay_ms(100);
	//wyczysczenie wyswietlacza
	lcd_send_command(LCD_CLEAR);
	_delay_ms(100);
	// entry mode
	lcd_send_command(ENTRY_MODE|INCREMENT);
	_delay_ms(100);



}

void wysylanie_tekstu(char *tekst){
	while(*tekst){
		lcd_send_data(*tekst);
		tekst++;
	}
}


int main(void){

	lcd_init();

	wysylanie_tekstu("Przelaczenie nr:");
	_delay_ms(100);

	////////////////////////////////////////////////////////PRZERWANIA
	DDRD|=(1<<PD0);
	PORTD&=~(1<<PD0);
	PORTD|=(1<<PD3);
	MCUCR |=(0<<ISC10)|(0<<ISC11);
	EIMSK |=(1<<INT1);
	sei();

	///////////////////////////////////////////////////////////////////////
	while(1){

	}

}

//////////przerwanie
// LICZNIK max 65536
ISR(INT1_vect){
	static int licznik = 0;
	static int stan = 1;
	if (licznik == 65536)
		stan = 0;
	if(stan){
		licznik ++;
		char zmienna_do_wyswietlacza[1];
		utoa(licznik,zmienna_do_wyswietlacza,10);
		lcd_send_command(SET_DDRAM_ADDR | LCD_LINE2);
		wysylanie_tekstu(zmienna_do_wyswietlacza);
		while(!(PIND & (1<<PD3)));
		_delay_ms(20);
	}else{
		lcd_send_command(SET_DDRAM_ADDR | LCD_LINE2);
		wysylanie_tekstu("PRZELADOWANIE");
	}


}
