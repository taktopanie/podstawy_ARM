/*
 * Zegar.c
 *
 *  Created on: 15 sie 2018
 *      Author: Macko
 */

#include<avr/io.h>
#include<util/delay.h>
#include<UART_BIBL.h>

#define ACK 1
#define NACK 0
#define ADRES_ZEGAR 0xD0



// FUNKCJA WYSYLAJACA START
void TWI_START(void){
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	while(!(TWCR & (1<<TWINT)));

}

// FUNKCJA WYSYLAJACA STOP
void TWI_STOP(void){
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while(!(TWCR&(1<<TWSTO)));
}

// FUNKCJA WYSYLAJACA DANE
void TWI_SEND_DATA(uint8_t data){
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
}

// FUNKCJA ODBIERAJACA DANE
uint8_t TWI_READ_DATA(uint8_t ack){
	TWCR=(1<<TWINT)|(1<<TWEN)|(ack<<TWEA);
	while(!(TWCR&(1<<TWINT)));
	return TWDR;

}

////// ALGORYTM WYSYLANIA ZMIENNYCH

void wysylanie_danych(uint8_t dev_addr, uint8_t mem_addr, uint8_t dane){
	TWI_START();
	TWI_SEND_DATA(dev_addr);
	TWI_SEND_DATA(mem_addr);
	TWI_SEND_DATA(dane);
}

void odbieranie_danych(uint8_t dev_addr,uint8_t mem_addr,uint8_t ilosc_danych, uint8_t* bufor){
	TWI_START();
	TWI_SEND_DATA(dev_addr);
	TWI_SEND_DATA(mem_addr);
	TWI_START();
	TWI_SEND_DATA(dev_addr|0x01);
	while(ilosc_danych--){
		*bufor++ = TWI_READ_DATA(ilosc_danych ? ACK : NACK);
	}
	TWI_STOP();
}


int main (void){
	// funkcja uruchamiajaca uart
		inicjacja();

		WYSYLANIE_TEXTU("START PROGRAMU I2C \n");
	uint8_t ilosc_znakow = 2;
	uint8_t BUFOR[10];

		// Pin PC4, PC5 Jako wejœcia (SDA,SCL)
		DDRC&=~(1<<PC4)&~(1<<PC5);
		// Pin PC4, PC5 PULL_UP
		PORTC|=(1<<PC4)|(1<<PC5);

		// ustawianie sekund
		wysylanie_danych(ADRES_ZEGAR,0x00,0x30);
		//ustawianie minut
		wysylanie_danych(ADRES_ZEGAR,0x01,0x38);
		//ustawianie godzin
		wysylanie_danych(ADRES_ZEGAR,0x02,0x10);

		while(1){

			char g_do_wysw[3], m_do_wysw[3],s_do_wysw[3];
			// odczytywanie godzin

			odbieranie_danych(ADRES_ZEGAR,0x02,ilosc_znakow,BUFOR);

						uint8_t godz_d,godz_j;

						godz_d=((((BUFOR[0])>>4)&0x03));
						godz_j=(((BUFOR[0]))&0x0F);

						uint8_t godz = godz_j + godz_d*10;

						utoa(godz,g_do_wysw,10);


				// odczytywanie minut

						odbieranie_danych(ADRES_ZEGAR,0x01,ilosc_znakow,BUFOR);

						uint8_t minuty_d,minuty_j;

						minuty_d=((((BUFOR[0])>>4)&0x0F));
						minuty_j=(((BUFOR[0]))&0x0F);

						uint8_t minuty = minuty_j + minuty_d*10;

						utoa(minuty,m_do_wysw,10);


			// odczytywanie sekund

						odbieranie_danych(ADRES_ZEGAR,0x00,ilosc_znakow,BUFOR);



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
