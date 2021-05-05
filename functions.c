/** @file */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdbool.h>

#include "functions.h"

Table* AddTable(Table** pHead, int number)
{
	bool exists = false; //istnienie stolika
	Table* p;
	//dodawanie na poczatek
	if (*pHead == NULL || (*pHead)->number >= number)
	{
		
		//jezeli dany stolik ju¿ istnieje
		if ((*pHead) != NULL && (*pHead)->number == number)
		{
			exists = true;
		}
		//jezeli dany stolik jeszcze nie istnieje
		if (!exists)
		{
			//stworz nowy stolik
			Table* NewTable = (Table*)malloc(sizeof(Table));
			NewTable->number = number;
			NewTable->pHeadClient = NULL;
			NewTable->pNextTable = (*pHead);
			(*pHead) = NewTable;
		}
		return (*pHead);
	}
	//jezeli numer stolika jest wiekszy
	else
	{
		p = *pHead;
		while (p->pNextTable != NULL && p->pNextTable->number < number)
		{
			p = p->pNextTable;
		}
		if (p->pNextTable != NULL && p->pNextTable->number == number)
		{
			exists = true;
		}
		if (!exists)
		{
			Table* NewTable = (Table*)malloc(sizeof(Table));
			NewTable->number = number;
			NewTable->pHeadClient = NULL;
			NewTable->pNextTable = p->pNextTable;
			p->pNextTable = NewTable;
		}
		return p->pNextTable;
	}
}

void AddClient(Client** pHead, const char* surname, int hour, int number, int discount)
{
	bool exists = false;
	Client* p;
	//dodawanie na pocz¹tek
	if (*pHead == NULL || (*pHead)->hour >= hour)
	{

		//jezeli stolik na dana godzine juz jest zajety
		if ((*pHead) != NULL && (*pHead)->hour == hour)
		{
			exists = true;
			printf("Ju¿ mamy rezerwacjê na t¹ godzinê\n");
		}
		//jezeli stolik na dana godzine jest wolny
		if (!exists)
		{
			//stworz nowa rezerwacje
			Client* NewClient = (Client*)malloc(sizeof(Client));
			NewClient->surname = malloc(strlen(surname) + 1);
			strcpy(NewClient->surname, surname);
			NewClient->hour = hour;
			NewClient->number = number;
			NewClient->discount = discount;
			NewClient->pNextClient = (*pHead);
			(*pHead) = NewClient;
		}
	}
	//jezeli godzina jest pozniejsza
	else
	{
		p = *pHead;
		while (p->pNextClient != NULL && p->pNextClient->hour < hour)
		{
			p = p->pNextClient;
		}
		if (p->pNextClient != NULL && p->pNextClient->hour == hour)
		{
			exists = true;
			printf("Ju¿ mamy rezerwacjê na t¹ godzinê\n");
		}
		if (!exists)
		{
			//stworz now¹ rezerwacjê
			Client* NewClient = (Client*)malloc(sizeof(Client));
			NewClient->surname = malloc(strlen(surname) + 1);
			strcpy(NewClient->surname, surname);
			NewClient->hour = hour;
			NewClient->number = number;
			NewClient->discount = discount;
			NewClient->pNextClient = p->pNextClient;
			p->pNextClient = NewClient;
		}
	}
}

void ShowClient(Client* pHead)
{
	while (pHead)
	{
		printf("Surname: %s \n",pHead->surname);
		printf("Hour: %d \n", pHead->hour);
		printf("Discount: %d%%\n", pHead->discount);
		printf("Number of people: %d \n\n", pHead->number);
		pHead = pHead->pNextClient;
	}
}

void ShowTable(Table* pHead)
{
	while (pHead)
	{
		printf("Table number: %d\n\n", pHead->number);
		ShowClient(pHead->pHeadClient);
		pHead = pHead->pNextTable;
	}
}

Table* CheckNumber(Table* pHead, int number)
{
	if (pHead)
	{
		//dodawanie do najmniejszego mozliwego stolika
		while (pHead->pNextTable != NULL && pHead->number < number)
		{
			pHead = pHead->pNextTable;
		}
		if (pHead->number >= number)
		{
			//zwracam wskaznik zeby dodac pozniej klienta do wlasnie tego stolika
			return pHead;
		}
	}
	return NULL;
}

int CheckHour(Client* pHead, int hour)
{
	int decision;
	//godziny pracy restauracji
	if (hour < 6 || hour > 22)
	{
		decision = 0; //0 to brak miejsca, 1 jest miejsce
		return decision;
	}
	else
	{
		while (pHead->pNextClient != NULL && pHead->hour != hour)
		{
			pHead = pHead->pNextClient;
			decision = 1;
		}
		if (pHead->hour == hour)
		{
			decision = 0;
		}
		return decision;
	}
}

int ExtractNumber(char* nazwa)
{
	char numer = *(nazwa + 5);
	int num = numer - '0';
	return num;
}

void Upload(Table** pHead, char* files[], int num)
{
	for (int i = 0; i < num; i++)
	{
		//otwarcie pliku w trybie do odczytu
		FILE* plik_r = fopen(files[i], "r");
		if (plik_r)
		{
			//numer stolika odzyskany z nazwy pliku
			int number = ExtractNumber(files[i]);
			char surname[10];
			int hour;
			int people;
			int discount;
			//wczytywanie kolejnych wartoœci
			while (fscanf(plik_r, "%s %d %d %d", surname, &hour, &people, &discount) != EOF)
			{
				Table* temp = AddTable(pHead, number);
				AddClient(&(temp->pHeadClient), surname, hour, people, discount);
			}

			fclose(plik_r);
		}
	}
}

void Check(Table* pHead)
{
	printf("Na ile osob: ");
	int number;
	scanf("%d", &number);
	//Sprawdzenie czy jest stolik na tyle osób
	Table* temp = CheckNumber(pHead, number);
	//Jezeli jest
	if (temp != NULL)
	{
		printf("Na ktora godzine: ");
		int hour;
		scanf("%d", &hour);
		//Sprawdzenie czy jest wolna godzina
		int x = CheckHour(temp->pHeadClient, hour);
		if (x == 1)
		{
			printf("Na jakie nazwisko: ");
			char surname[10];
			scanf("%s",surname);
			printf("Jaka znizke naliczyc: ");
			int discount;
			scanf("%d", &discount);

			AddClient(&(temp->pHeadClient),surname,hour,number,discount);
		}
		else
		{
			printf("%s", "Nie mozna zarezerwowac na ta godzine\n\n");
		}
	}
	//Nie ma takiego stolika
	else
	{
		printf("%s", "Nie mozna zarezerwowac na tyle osob\n\n");
	}
}

void SaveToFile(Table* pHead, char* files[], int num)
{
	for (int i = 0; i < num; i++)
	{
		//otwarcie pliku w trybie do zapisu
		FILE* plik_w = fopen(files[i], "w");
		if (plik_w)
		{
			if (pHead)
			{
				while (pHead->pNextTable != NULL && pHead->number != ExtractNumber(files[i]))
				{
					pHead = pHead->pNextTable;
				}
				Client* p = pHead->pHeadClient;
				while (p)
				{
					fprintf(plik_w, "%s %d %d %d\n", p->surname, p->hour, p->number, p->discount);
					p = p->pNextClient;
				}
			}
			fclose(plik_w);
		}
		else
		{
			printf("B³ad odczytania pliku!\n");
		}
	}
}

void DeleteClient(Client** pHead)
{
	Client* tmp = NULL;
	while (*pHead)
	{
		tmp = (*pHead)->pNextClient;
		free((*pHead)->surname);
		free(*pHead);
		*pHead = tmp;
	}
}

void DeleteTable(Table** pHead)
{
	Table* tmp = NULL;
	while (*pHead)
	{
		tmp = (*pHead)->pNextTable;
		DeleteClient(&((*pHead)->pHeadClient));
		free(*pHead);
		*pHead = tmp;
	}
}