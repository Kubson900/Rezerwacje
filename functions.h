/** @file */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structures.h"

/** Funkcja dodaje stoliki do posortowanej listy
@param pHead Reprezentant listy stolikow
@param number Numer stolika i max ilosc osob
@return Wskaznik na stolik
*/
Table* AddTable(Table** pHead, int number);

/** Funkcja dodaje klienta do konkretnego stolika
@param pHead Reprezentant listy klientow
@param surname Nazwisko klienta
@param hour Godzina rezerwacji
@param number Ilosc osob
@param discount Znizka dla klienta
*/
void AddClient(Client** pHead, const char* surname, int hour, int number, int discount);

/** Funkcja wyswietla liste klientow
@param pHead Reprezentant listy klientow
*/
void ShowClient(Client* pHead);

/** Funkcja wyswietla wszystkie stoliki
@param pHead Reprezentant listy stolikow
*/
void ShowTable(Table* pHead);

/** Funkcja sprawdza przy ktorym stoliku moze usiasc klient
@param pHead Reprezentant listy stolikow
@param number Ilosc osob
@return Wskaznik na stolik
*/
Table* CheckNumber(Table* pHead, int number);

/** Funkcja sprawdza czy jest dostepna wskazana godzina
@param pHead Reprezentant listy klientow
@param hour Godzina rezerwacji
@return Prawda lub falsz
*/
int CheckHour(Client* pHead, int hour);

/** Funkcja odczytuje numer stolika z nazwy pliku
@param nazwa Nazwa pliku
@return Numer stolika
*/
int ExtractNumber(char* nazwa);

/** Funkcja odczytuje z pliku i tworzy strukture dynamiczna (lista w liscie)
@param pHead Wskaznik na reprezentanta listy przystankow
@param files Tablica z nazwami plikow
@param num Ilosc plikow do wczytania
*/
void Upload(Table** pHead, char* files[], int num);

/** Funkcja pobiera dane od uzytkownika i sprawdza czy moze utworzyc rezerwacje
@param pHead Reprezentant listy stolikow
*/
void Check(Table* pHead);

/** Funkcja zapisuje do plikow tekstowych
@param pHead Reprezentant listy stolikow
@param files Tablica z nazwami plikow
@param num Ilosc plikow do wczytania
*/
void SaveToFile(Table* pHead, char* files[], int num);

/** Funkcja usuwa liste klientow ze stolika
@param pHead Wskaznik na reprezentanta listy klientow
*/
void DeleteClient(Client** pHead);

/** Funkcja usuwa liste stolikow
@param pHead Wskaznik na reprezentanta listy stolikow
*/
void DeleteTable(Table** pHead);

#endif
