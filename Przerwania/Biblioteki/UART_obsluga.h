/*
 * UART_obsluga.h
 *
 *  Created on: 17 paz 2018
 *      Author: Maciej Zwolan
 */
#ifndef UART_OBSLUGA
#define UART_OBSLUGA

#include<avr/io.h>

extern volatile char BUFOR[];
extern volatile uint8_t GORA_BUFORA;
extern volatile uint8_t DOL_BUFORA;

extern uint8_t tmp_GORA;
extern char data;

//definicje funkcji
extern void USART_INIT(unsigned int);
extern void USART_WYSYLANIE(char);
extern void WYSYLANIE_TEXTU(char*);
extern char GET_BYTE(void);
//extern ISR(USART_RX_vect);

extern void inicjacja_usart(void);

#endif /* UART_OBSLUGA_ */
