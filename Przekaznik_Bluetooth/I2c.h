/*
 * I2c.h
 *
 *  Created on: 27 kwi 2018
 *      Author: Macko
 *
 *      Biblioteka s³u¿y do obs³ugi modu³u komunikacji i2c.
 *
 *      dane odczytywane i zapisywane s¹ za pomoc¹ 2 funkcji :
 *
 *      i2c_odebranie_danych -- s³u¿¹ca do odebrania danych
 *
 *      i2c_wyslanie_danych -- s³u¿¹ca do wys³ania danych
 *
 *     __________________________________________________________
 *
 *     Funkcje te s¹ z³o¿eniem poszczególnych podfunkcji.
 *
 *     aby komunikowac siê z odbiornikiem nalezy pamiêtac o podpiêciu odbiornika
 *     pod odpowiednie linie.
 *
 *     W moim przypadku w mikrokontrolerze atmega32 jest to pin PC5 i PC4.
 *
 *     Aby zainicjowac te piny nalezy wywolac funckje inicjacja_i2c();
 *
 */

#ifndef I2C_H_
#define I2C_H_

#include<avr/io.h>

#define ACK 1
#define NACK 0
#define ADRES_ZEGAR 0xD0

int adres_dev, adres_mmr;
uint8_t dane;
uint8_t ilosc_znakow =2;
uint8_t bufor[10];

void i2c_start(void);
void i2c_stop(void);
void i2c_wyslanie(char);
uint8_t i2c_odebranie(uint8_t);

void i2c_odebranie_danych(int,int,uint8_t,uint8_t*);
void i2c_wyslanie_danych(int,int ,uint8_t );

void inicjacja_i2c(void){

	DDRC&=~(1<<PC5)&~(1<<PC4);		//uruchomienie pinów pod i2c
	PORTC|=(1<<PC5)|(1<<PC4);		// podlaczenie rezystorow pull_up
}

void i2c_start(void){

	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
}

void i2c_stop(void){
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	while(!(TWCR&(1<<TWSTO)));
}

void i2c_wyslanie(char DATA){
	TWDR = DATA;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

uint8_t i2c_odebranie(uint8_t ack){
TWCR=(1<<TWINT)|(ack<<TWEA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	return TWDR;
}

void i2c_odebranie_danych(int adres_dev,int adres_mmr,uint8_t ilosc_zmiennych,uint8_t* bufor){
	i2c_start();									//generowanie startu
	i2c_wyslanie(adres_dev);						//wysylanie adresu dev
	i2c_wyslanie(adres_mmr);						//wysylanie adresu pamieci
	i2c_start();									// powtorzony start aby przejsc w tryb odczytywania
	i2c_wyslanie(adres_dev+0x01);					// przejscie w stan odczytywania

	while(ilosc_zmiennych--){
		*bufor++=i2c_odebranie(ilosc_zmiennych ? ACK : NACK);
	}
	i2c_stop();
}

void i2c_wyslanie_danych(int adres_dev,int adres_mmr,uint8_t dane){
	i2c_start();									//generowanie startu
	i2c_wyslanie(adres_dev);						//wysylanie adresu dev
	i2c_wyslanie(adres_mmr);						//wysylanie adresu pamieci
	i2c_wyslanie(dane);								//wyslanie danych
	i2c_stop();										//generowanie stop
}

#endif /* I2C_H_ */
