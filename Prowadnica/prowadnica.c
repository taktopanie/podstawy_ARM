/*
 * prowadnica.c
 *
 *  Created on: 29 kwi 2018
 *      Author: Macko
 */


#include<avr/io.h>
#include<util/delay.h>
#include"UART_BIBL.h"
#include<stdlib.h>


int main (void){

						// inicjacja UART
	inicjacja();
						// inicjacja pinu do pozycjonowania
	DDRC&=~(1<<PC3);
						// pullup na pinie pozycji
	PORTC|=(1<<PC3);


	DDRC&=~(1<<PC4);
	PORTC|=(1<<PC4);

	int licznik = 0;
	while(1){
		if(!(PINC & (1<<PC3))){
			licznik++;
			while(!(PINC & (1<<PC3)))
				if(!(PINC & (1<<PC4)))
					break;
		}

		if(!(PINC & (1<<PC4))){
			char wartosc_do_wysw[3];
			utoa(licznik,wartosc_do_wysw,10);
			WYSYLANIE_TEXTU("\nILOSC IMPULSOW TO : ");
			WYSYLANIE_TEXTU(wartosc_do_wysw);
			WYSYLANIE_TEXTU(". \n ");
			licznik=0;
		}
	}
return 0;
}
