/*
 * test.c
 *
 *  Created on: 23 lip 2018
 *      Author: Macko
 */


#include<avr/io.h>
#include<util/delay.h>

int main(void){

	DDRD|=(1<<PD7);
	PORTD&=~(1<<PD7);

	while(1){
		PORTD^=(1<<PD7);
		_delay_ms(1000);
		}
	return 0;


}
