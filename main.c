/** @file */



#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "structures.h"
#include "functions.h"

int main() 
{
	Table* pHeadTable = NULL; //reprezentant struktury dynamicznej

	char* files[] = { "Table2.txt", "Table4.txt", "Table6.txt", "Table8.txt" }; //pliki do wczytania
	int num_files = sizeof(files) / sizeof(*files); //ilosc plikow
	Upload(&pHeadTable, files, num_files); //wczytanie plikow

	int number;
	do
	{
		printf("WITAMY W NASZEJ RESTAURACJI!\n");
		printf("Godziny otwarcia 6:00 - 22:00\n");
		printf("Stoliki do 8 osob\n\n");

		printf("[1]  Zarezerwuj stolik\n");
		printf("[2]  Wyswietl wszystkich gosci\n");
		printf("[3]  Zakoncz\n");
		printf("Wybierz numer: ");
		scanf("%d", &number);

		switch (number)
		{
		case 1:
			system("cls");
			Check(pHeadTable);
			break;
		case 2:
			system("cls");
			ShowTable(pHeadTable);
			break;
		case 3:
			system("cls");
			SaveToFile(pHeadTable, files, num_files);
			DeleteTable(&pHeadTable);
			printf("Zakonczono dzialanie programu\n");
			break;
		default:
			printf("\nZyy wybor! Prosze wybrac liczbe od 1 do 3\n\n");
		}
	} while (number != 3);

	return 0;
}
