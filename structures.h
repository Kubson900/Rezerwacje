/** @file */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
 Struktura opisujaca klienta
 */
typedef struct Client
{
	/** Nazwisko klienta */
	char* surname;
	/** Godzina rezerwacji */
	int hour;
	/** Ilosc osob */
	int number;
	/** Znizka dla klienta */
	int discount;
	/** Wskaznik na kolejny element listy */
	struct Client* pNextClient;
}Client;

/**
 Struktura opisujaca stolik
 */
typedef struct Table
{
	/** Numer stolika */
	int number;
	/** Wskaznik na liste klientow */
	struct Client* pHeadClient;
	/** Wskaznik na kolejny element listy */
	struct Table* pNextTable;
}Table;

#endif