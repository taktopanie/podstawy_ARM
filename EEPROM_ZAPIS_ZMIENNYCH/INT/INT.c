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


char liczba_do_zapis[3];

int main(void){
// funkcja uruchamiajaca uart
	inicjacja();
	uint8_t BUFOR_EEPROM[10];
	char b_do_wys[3];
	char* wsk = b_do_wys;
	// Pin PC4, PC5 Jako wej�cia (SDA,SCL)
	DDRC&=~(1<<PC4)&~(1<<PC5);
	// Pin PC4, PC5 PULL_UP
	PORTC|=(1<<PC4)|(1<<PC5);
	// zmiana prędkości transmisji I2C
	TWSR = (1<<0);
	TWBR = (0x0F);

//	odczytanie_zmiennej()
	uint8_t dev_addr = 0b1010;
	uint8_t blok=0;
	uint8_t adres_zmiennej=0;

	odczytanie_zmiennej(dev_addr,blok,adres_zmiennej,BUFOR_EEPROM);
	uint8_t zmienna_low = *BUFOR_EEPROM;
	odczytanie_zmiennej(dev_addr,blok,adres_zmiennej+1,BUFOR_EEPROM);
	uint8_t zmienna_high = *BUFOR_EEPROM;

	int zmienna_int = (zmienna_high<<8) | (zmienna_low);
	itoa(zmienna_int, wsk, 10);
	WYSYLANIE_TEXTU("liczba int odczytana to :");

	//USART_WYSYLANIE(*b_do_wys);
	WYSYLANIE_TEXTU(b_do_wys);
	WYSYLANIE_TEXTU("\n");
	while(1){

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
