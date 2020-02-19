/*
 * i2c_main.c
 *
 *  Created on: 5 sty 2018
 *      Author: Macko
 */


#include<avr/io.h>
#include<util/delay.h>
#include"UART_BIBL.h"
#include<stdlib.h>
#include<ctype.h>

#define ACK 1
#define NACK 0
#define ADRES_ZEGAR 0xD0

//definicja funkcji

void i2c_START(void);
void i2c_stop(void);
void i2c_write(uint8_t);
uint8_t i2c_read(uint8_t);
void odczytanie_zmiennej(uint8_t, uint8_t, uint8_t, uint8_t*);
void wysylanie_zmiennej(uint8_t, uint8_t, uint8_t, uint8_t);

char char_addr[3];
char liczba_do_zapis[3];

int main(void){
// funkcja uruchamiajaca uart
	inicjacja();
	uint8_t BUFOR_EEPROM[10];
	char b_do_wys[3];
	volatile uint8_t tmp_zmienna;

	// Pin PC4, PC5 Jako wej�cia (SDA,SCL)
	DDRC&=~(1<<PC4)&~(1<<PC5);
	// Pin PC4, PC5 PULL_UP
	PORTC|=(1<<PC4)|(1<<PC5);
	// zmiana prędkości transmisji I2C
	TWSR = (1<<0);
	TWBR = (0x0F);

//	odczytanie_zmiennej()
	uint8_t dev_addr = 0b1010;
	volatile uint8_t blok;
	//uint8_t adres_zmiennej=45;

	//odczytanie_zmiennej(dev_addr,blok,adres_zmiennej,BUFOR_EEPROM);

	WYSYLANIE_TEXTU("\n##############PROGRAM GLOWNY##############\nAby zapisac wartosci w pamieci nacisnij z\nAby odczytac wartosci nacisnij o.\n##########################################\n:");
	while(1){

/*
		for(int i=0;i<255;i++){
		wysylanie_zmiennej(dev_addr,1,i,i);
		_delay_ms(10);
		}
*/
	tmp_zmienna = GET_BYTE();
		if(tmp_zmienna=='o'){
			tmp_zmienna = 0;
			WYSYLANIE_TEXTU("Podaj blok z ktorego chcesz odczytac wartosc (0 - 3):");
			CZYSZCZENIE_BUFORA();
			while((tmp_zmienna!='0')&&(tmp_zmienna!='1')&&(tmp_zmienna!='2') && (tmp_zmienna!='3')){
				tmp_zmienna = GET_BYTE();
			}
			// ZAMIANA ASCII NA INT
			blok = (int)(tmp_zmienna)-48;

			WYSYLANIE_TEXTU("Podaj adres (0-255):");

			CZYSZCZENIE_BUFORA();
			// ZAPELNIENIE ZMIENNEJ CZYMS INNYM NIZ LICZBA
			tmp_zmienna = 'f';

			for(int i=0;i<3;i++){
			// SPRAWDZENIE CZY TO NAPEWNO LICZBA
			while(!isdigit(tmp_zmienna)){
				tmp_zmienna = GET_BYTE();
			}
			char_addr[i]=tmp_zmienna;
			CZYSZCZENIE_BUFORA();
			tmp_zmienna='f';
			}

			// zamiana char na int liczbe
			int adres_z = (((int)char_addr[0])-48)*100 + (((int)char_addr[1])-48)*10 + (((int)char_addr[2])-48);

			WYSYLANIE_TEXTU("Podany adres to : ");
			WYSYLANIE_TEXTU(char_addr);
			if(adres_z >= 0 && adres_z <= 255){
				odczytanie_zmiennej(dev_addr,blok, adres_z,BUFOR_EEPROM);
				WYSYLANIE_TEXTU("\n\nOdczytano :");
				utoa(*BUFOR_EEPROM,b_do_wys,10);
				WYSYLANIE_TEXTU(b_do_wys);
				WYSYLANIE_TEXTU("\n");
			}
			else{
				WYSYLANIE_TEXTU("\nAdres powinien byc z zakresu 0-255.\nPowrot do menu glownego...\n");
			}
			_delay_ms(200);
			WYSYLANIE_TEXTU("\n##############PROGRAM GLOWNY##############\nAby zapisac wartosci w pamieci nacisnij z\nAby odczytac wartosci nacisnij o.\n##########################################\n:");
		}
		else if(tmp_zmienna=='z'){
			WYSYLANIE_TEXTU("Podaj blok do ktorego chcesz zapisac wartosc (0 - 3):");
			CZYSZCZENIE_BUFORA();
			while((tmp_zmienna!='0')&&(tmp_zmienna!='1')&&(tmp_zmienna!='2') && (tmp_zmienna!='3')){
				tmp_zmienna = GET_BYTE();
			}
			// ZAMIANA ASCII NA INT
			blok = (int)(tmp_zmienna)-48;

			WYSYLANIE_TEXTU("Podaj adres (0-255):");

			CZYSZCZENIE_BUFORA();
			// ZAPELNIENIE ZMIENNEJ CZYMS INNYM NIZ LICZBA
			tmp_zmienna = 'f';

			for(int i=0;i<3;i++){
			// SPRAWDZENIE CZY TO NAPEWNO LICZBA
			while(!isdigit(tmp_zmienna)){
				tmp_zmienna = GET_BYTE();
			}
			char_addr[i]=tmp_zmienna;
			CZYSZCZENIE_BUFORA();
			tmp_zmienna='f';
			}

			WYSYLANIE_TEXTU("Podaj liczbe jaka chcesz zapisac (0-255):");

			CZYSZCZENIE_BUFORA();
			// ZAPELNIENIE ZMIENNEJ CZYMS INNYM NIZ LICZBA
			tmp_zmienna = 'f';

			for(int i=0;i<3;i++){
			// SPRAWDZENIE CZY TO NAPEWNO LICZBA
			while(!isdigit(tmp_zmienna)){
				tmp_zmienna = GET_BYTE();
			}
			liczba_do_zapis[i]=tmp_zmienna;
			CZYSZCZENIE_BUFORA();
			tmp_zmienna='f';
			}

			// zamiana char na int liczbe
			int adres_z = (((int)char_addr[0])-48)*100 + (((int)char_addr[1])-48)*10 + (((int)char_addr[2])-48);
			int liczba_zapis = (((int)liczba_do_zapis[0])-48)*100 + (((int)liczba_do_zapis[1])-48)*10 + (((int)liczba_do_zapis[2])-48);

			WYSYLANIE_TEXTU("Podany adres to : ");
			WYSYLANIE_TEXTU(char_addr);

			if(adres_z >= 0 && adres_z <= 255 && liczba_zapis >= 0 && liczba_zapis <= 255){
				wysylanie_zmiennej(dev_addr,blok, adres_z,liczba_zapis);
				WYSYLANIE_TEXTU("\n\nTRWA ZAPIS...");
			}
			else{
				WYSYLANIE_TEXTU("\nAdres oraz liczba powinny byc z zakresu 0-255.\nPowrot do menu glownego...\n");
			}
		WYSYLANIE_TEXTU("\n##############PROGRAM GLOWNY##############\nAby zapisac wartosci w pamieci nacisnij z\nAby odczytac wartosci nacisnij o.\n##########################################\n:");
		}
	tmp_zmienna = 0;
	}
}

// funkcja generujaca start
void i2c_START(void){
	TWCR = (1<<TWINT)| (1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));

}

// funkcja generujaca stop
void i2c_stop(void){
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while(!(TWCR&(1<<TWSTO)));

}

// funkckcja wysylajace dane do i2c
void i2c_write(uint8_t data){
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
}

// funkcja odczytujaca dane z i2c
uint8_t i2c_read(uint8_t ack){
	TWCR=(1<<TWINT)|(ack<<TWEA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	//WYSYLANIE_TEXTU("r\n");
	return TWDR;
}

// funkcja sekwencji odczytu z EEPROM
void odczytanie_zmiennej(uint8_t DEV_ADDR, uint8_t blok,uint8_t mmr_adres,uint8_t *bufor){

	i2c_START();
		// wyslanie bajtu ustawienia
	i2c_write((DEV_ADDR<<4)|(blok<<1));
		// wyslanie adresu zmiennej
	i2c_write(mmr_adres);
	i2c_START();
		// wyslanie bajtu ustawienia
	i2c_write((DEV_ADDR<<4)|(blok<<1)|0b1);
	*bufor = i2c_read(1);
	i2c_stop();
	}

// funkcja sekwencji zapisu do EEPROM
void wysylanie_zmiennej(uint8_t DEV_ADDR, uint8_t blok,uint8_t mmr_adres, uint8_t zmienna){
	//uint8_t CONTROL_BYTE =(DEV_ADDR<<4)&(1<<(1+blok))
	// wysy�anie startu
		i2c_START();
	// wyslanie bajtu ustawienia
		i2c_write((DEV_ADDR<<4)|(blok<<1));
	// wyslanie adresu zmiennej
		i2c_write(mmr_adres);
	// wyslanie wartosci
		i2c_write(zmienna);
	// wysy�anie stopu
		i2c_stop();
}
