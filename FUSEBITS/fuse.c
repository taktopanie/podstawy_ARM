/*
 * fuse.c
 *
 *  Created on: 27 paź 2018
 *      Author: macko
 */

//#######FUSEBITS DLA Atmega328p ZEGARA 8 MHz WEWNETRZNEGO 0xE2 0xD9 0xFF
//#######FUSEBITS DLA Atmega328p ZEGARA 1 MHz WEWNETRZNEGO 0x62 0xD9 0xFF

int main(void){
	while(1);
}
/* LINUX TERMINAL ZMIANA FUSEBITOW
avrdude -c usbasp -p m328p -U lfuse:w:0x62:m
avrdude -c usbasp -p m328p -U hfuse:w:0x62:m
avrdude -c usbasp -p m8 -U hfuse:w:0xFF:m -U lfuse:w:0xFF:m

lub np -U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

http://www.engbedded.com/fusecalc/
*/
