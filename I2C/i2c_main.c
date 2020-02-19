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

#define ACK 1
#define NACK 0
#define ADRES_ZEGAR 0xD0

//definicja funkcji

void i2c_START(void);
void i2c_stop(void);
void i2c_write(uint8_t);
uint8_t i2c_read(uint8_t);
void odczytanie_zmiennej(uint8_t, uint8_t, uint8_t ,uint8_t *);
void wysylanie_zmiennej(uint8_t, uint8_t, uint8_t);




int main(void){
// funkcja uruchamiajaca uart
	inicjacja();

	WYSYLANIE_TEXTU("START PROGRAMU I2C \n");
uint8_t ilosc_znakow = 1;
uint8_t BUFOR[10];

	// Pin PC4, PC5 Jako wej�cia (SDA,SCL)
	DDRC&=~(1<<PC4)&~(1<<PC5);
	// Pin PC4, PC5 PULL_UP
	PORTC|=(1<<PC4)|(1<<PC5);

	wysylanie_zmiennej(ADRES_ZEGAR,0x0E,0x18);
	// ustawianie sekund
	wysylanie_zmiennej(ADRES_ZEGAR,0x00,0x50);
	//ustawianie minut
	wysylanie_zmiennej(ADRES_ZEGAR,0x01,0x58);
	//ustawianie godzin
	wysylanie_zmiennej(ADRES_ZEGAR,0x02,0x11);

	while(1){

		char g_do_wysw[3], m_do_wysw[3],s_do_wysw[3];
		// odczytywanie godzin

					odczytanie_zmiennej(ADRES_ZEGAR,0x02,ilosc_znakow,BUFOR);

					uint8_t godz_d,godz_j;

					godz_d=((((BUFOR[0])>>4)&0x03));
					godz_j=(((BUFOR[0]))&0x0F);

					uint8_t godz = godz_j + godz_d*10;

					utoa(godz,g_do_wysw,10);


			// odczytywanie minut

					odczytanie_zmiennej(ADRES_ZEGAR,0x01,ilosc_znakow,BUFOR);

					uint8_t minuty_d,minuty_j;

					minuty_d=((((BUFOR[0])>>4)&0x0F));
					minuty_j=(((BUFOR[0]))&0x0F);

					uint8_t minuty = minuty_j + minuty_d*10;

					utoa(minuty,m_do_wysw,10);


		// odczytywanie sekund

			odczytanie_zmiennej(ADRES_ZEGAR,0x00,ilosc_znakow,BUFOR);



			uint8_t sekundy_d,sekundy_j;

			//sekundy_d=bcd2ded(BUFOR[0]);
			sekundy_d=((((BUFOR[0])>>4)&0x0F));
			sekundy_j=(((BUFOR[0]))&0x0F);

			uint8_t sekundy = sekundy_j + sekundy_d*10;

			utoa(sekundy,s_do_wysw,10);

			// WYSWIETLANIE NA UART
								WYSYLANIE_TEXTU("CZAS :    ");

								WYSYLANIE_TEXTU(g_do_wysw);
								WYSYLANIE_TEXTU(":");

								WYSYLANIE_TEXTU(m_do_wysw);
								WYSYLANIE_TEXTU(":");

								WYSYLANIE_TEXTU(s_do_wysw);
								WYSYLANIE_TEXTU("\n");


				_delay_ms(200);
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

// funkcja sekwencji odczytu z i2c
void odczytanie_zmiennej(uint8_t dev_adres, uint8_t mmr_adres, uint8_t ilosc_zmiennych,uint8_t *bufor){
// wysy�anie startu
	i2c_START();
// wysylanie adresu urz�dzenia
	i2c_write(dev_adres);
// wysy�anie adresu kom�rki pami�ci
	i2c_write(mmr_adres);
// ponowny start
	i2c_START();
	// Ponowne wys�anie adresu urz�dzenia +0x01
	i2c_write(dev_adres+0x01);

		while(ilosc_zmiennych--){
		*bufor++ =i2c_read(ilosc_zmiennych ? ACK : NACK);


		}
// wysy�anie stopu
	i2c_stop();

	}

void wysylanie_zmiennej(uint8_t dev_adres,uint8_t mmr_adres, uint8_t zmienna){
	// wysy�anie startu
		i2c_START();
	// wysylanie adresu urz�dzenia
		i2c_write(dev_adres);
	// wysy�anie adresu kom�rki pami�ci
		i2c_write(mmr_adres);

	// wysylanie zmiennej
		i2c_write(zmienna);

	// wysy�anie stopu
		i2c_stop();
}
