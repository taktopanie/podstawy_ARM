/*
 * Odkodowywanie.h
 *
 *  Created on: 15 lis 2018
 *      Author: Maciej Zwolan
 */
// ABY ODKODOWAC KOD W POSTACI #FF*PP-SS/WWW+
// WYWOLAJ FUNKCJE ROZPOZNANIE(KOD_DO_ODKODOWANIA)
// ZWRACA ONA STRUKTURE KOD
// ZAWIERAJACA :
//	CHAR	STRUKTURA.FUNKCJA
//	CHAR	STRUKTURA.PIN
//	CHAR	STRUKTURA.STAN
//	INT		STRUKTURA.WYPELNIENIE
//
#ifndef ODKODOWYWANIE_H_
#define ODKODOWYWANIE_H_


#include <string.h>
char tmp_zmienna[4];
char tmp_tablica[30];

//char zmienna[] = "#01*01-01/000+";

char* odkodowywanie(char*, char, int);

struct KOD{
int funkcja;
int pin;
int stan;
int wypelnienie;
};

struct KOD rozpoznawanie(char* zdanie){
struct KOD tmp_struktura;

tmp_struktura.funkcja = atoi(odkodowywanie(zdanie,'#',2));
tmp_struktura.pin = atoi(odkodowywanie(zdanie,'*',2));
tmp_struktura.stan = atoi(odkodowywanie(zdanie,'-',2));
tmp_struktura.wypelnienie = atoi(odkodowywanie(zdanie,'/',3));
return tmp_struktura;
}


char* odkodowywanie(char* wsk_do_tablicy,char znak,int ilosc_znakow){
		// WYCZYSCZENIE ZMIENNEJ TMP
		int z =0;
	    while(tmp_zmienna[z]){
	    tmp_zmienna[z++]=0;
	    }

    strcpy(tmp_tablica,wsk_do_tablicy);
    int indeks = 0;
    while(tmp_tablica[indeks]!=znak){
    indeks++;}

    for(int n = 0;n<ilosc_znakow;n++){
    tmp_zmienna[n] = tmp_tablica[n+(indeks+1)];
    }
    return tmp_zmienna;
}


#endif /* ODKODOWYWANIE_H_ */
