/*
 * przekaznik.c
 *
 *  Created on: 27 kwi 2018
 *      Author: Macko
 */

// ODCZYTANIE GODZINY I WLACZENIE PRZEKAZNIKA O GODZ NASTAWIONEJ NP 15:00

#include<util/delay.h>
#include<avr/io.h>
#include"UART_BIBL.h"
#include<stdlib.h>
#include<stdio.h>
#include"I2c.h"





int main (void){

	int godzina_do_wlaczenia = 15;
	int godzina_do_wylaczenia= 18;



	inicjacja()	;		//zainicjowanie uart
	inicjacja_i2c();
	WYSYLANIE_TEXTU("START PROGRAMU I2C \n");

	DDRC|=(1<<PC3);					// pin do wyjscia przekaznika


	// ustawianie sekund
	i2c_wyslanie_danych(ADRES_ZEGAR,0x00,0x50);
	//ustawianie minut
	i2c_wyslanie_danych(ADRES_ZEGAR,0x01,0x59);
	//ustawianie godzin
	i2c_wyslanie_danych(ADRES_ZEGAR,0x02,0x14);


while(1){


	char g_do_wysw[3], m_do_wysw[3],s_do_wysw[3];
				// odczytywanie godzin

						i2c_odebranie_danych(ADRES_ZEGAR,0x02,ilosc_znakow,bufor);

						uint8_t godz_d,godz_j;

						godz_d=((((bufor[0])>>4)&0x03));
						godz_j=(((bufor[0]))&0x0F);

						uint8_t godz = godz_j + godz_d*10;

						utoa(godz,g_do_wysw,10);


				// odczytywanie minut

						i2c_odebranie_danych(ADRES_ZEGAR,0x01,ilosc_znakow,bufor);

						uint8_t minuty_d,minuty_j;

						minuty_d=((((bufor[0])>>4)&0x0F));
						minuty_j=(((bufor[0]))&0x0F);

						uint8_t minuty = minuty_j + minuty_d*10;

						utoa(minuty,m_do_wysw,10);


			// odczytywanie sekund

						i2c_odebranie_danych(ADRES_ZEGAR,0x00,ilosc_znakow,bufor);



						uint8_t sekundy_d,sekundy_j;

						//sekundy_d=bcd2ded(BUFOR[0]);
						sekundy_d=((((bufor[0])>>4)&0x0F));
						sekundy_j=(((bufor[0]))&0x0F);

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


												// wlaczenie przekaznika o danej godzinie
				if(godz >= godzina_do_wlaczenia && godz < godzina_do_wylaczenia){
				PORTC&=~(1<<PC3);
				}else{
				PORTC|=(1<<PC3);
				}
	}
}
