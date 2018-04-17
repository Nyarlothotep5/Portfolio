//	L-SYSTEM 
//	SYSTEM LINDENMAYERA
//	algorytm transformacji lancucha znakow
//	pozwala on produkowac instrukcje dla zolwia
//
//w przypadku duzej ilosci iteracji wystepowaly problemy z pamiecia, wiec zamiast lancucha znakow uzywane sa pliki tekstowe

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include"Lindenmayer.h"

int lindenmayerManual(int iter)
{
	int varN, consN;		//zmienne na liczbe zmiennych i stalych

	int *var;		//wskaznik tablicy zawierajacej zmeinne L-systemu
	int *cons;		//wskaznik tablicy zawierajacej stale
	int **rule;		//wskaznik do tablicy zasad systemu

	printf("Prosze podac liczbe zmiennych i liczbe stalych:\n");
	scanf("%d %d", &varN, &consN);

	var = (int*)malloc(varN * sizeof(int));		//alokacja pamieci na tablice zmiennych i stalych 
	cons = (int*)malloc(consN * sizeof(int));

	printf("\nZmienna nie moze wynosic '0'\n\n");		//czystosc

	vcInit(varN, consN, var, cons);

	printf("\n\n");		//czystosc

	rule = (int**)malloc(varN * sizeof(int*));			//liczba wierszy tablicy zasad bedzie taka sama jak liczba zmiennych

	for (int i = 0; i < varN; i++)
	{
		rule[i] = (int*)malloc(40 * sizeof(int));		//znowu zakladam ze zasady nie beda dluzsze niz 40
	}

	rulesInit(rule, varN, var);			//inicjacja zasad

	FILE *axiom;		//obsluga pliku z axiomem
	FILE *pomoc;		//chce otworzyc pomocniczy plik

	axiom = fopen("lindenmayer.txt", "w");
	
	axiomInit(axiom);		//inicjacja axiomu
	fclose(axiom);			//nie chce juz pisac w axiom.txt wiec zamykam

	for (int i = 0; i < iter; i++)		//petla przeksztalcajaca lancuch zadana liczbe razy
	{
		axiom = fopen("lindenmayer.txt", "r");		//otwieram oba pliki, tym razem z lindenmayer.txt czytam, a w pomoc.txt pisze 
		pomoc = fopen("pomoc.txt", "w");

		transformIter(axiom, rule, var, varN, consN, pomoc);		//przeksztalcam lancuch znakow z pliku "lindenmayer.txt"
		
		fclose(axiom);		//zamykam oba pliki, zeby za chwile moc je przepisac
		fclose(pomoc);

		axiom = fopen("lindenmayer.txt", "w");		//ponownie otwieram pliki ale z innymi przeznaczeniami
		pomoc = fopen("pomoc.txt", "r");

		rewrite(axiom, pomoc);		//przepisuje zawartosc "pomoc.txt" do "axiom.txt"

		fclose(axiom);		//zamykam pliki 
		fclose(pomoc);
	}

	axiom = fopen("lindenmayer.txt", "r");		//otwieram plik w celu policzenia elementow

	int h;		//zmienna na liczbe elementow

	h = countH(axiom);		//licze wszystkie elementy niezerowe
	
	fclose(axiom);		

	return h;		//zwracam liczbe elementow (krokow dla zolwia)
}

int lindenmayerPlus(int iter, int *var, int varN, int **rule)
{
	FILE *axiom;

	FILE *pomoc;		//chce otworzyc pomocniczy plik
	
	for (int i = 0; i < iter; i++)		//petla przeksztalcajaca lancuch zadana liczbe razy
	{
		axiom = fopen("lindenmayerPlus.txt", "r");		//otwieram oba pliki, tym razem z lindenmayer.txt czytam, a w pomoc.txt pisze 
		pomoc = fopen("pomocPlus.txt", "w");

		transformIter(axiom, rule, var, varN, 1, pomoc);		//przeksztalcam lancuch znakow z pliku "lindenmayer.txt"

		fclose(axiom);		//zamykam oba pliki, zeby za chwile moc je przepisac
		fclose(pomoc);

		axiom = fopen("lindenmayerPlus.txt", "w");		//ponownie otwieram pliki ale z innymi przeznaczeniami
		pomoc = fopen("pomocPlus.txt", "r");

		rewrite(axiom, pomoc);		//przepisuje zawartosc "pomoc.txt" do "axiom.txt"

		fclose(axiom);		//zamykam pliki 
		fclose(pomoc);
	}

	axiom = fopen("lindenmayerPlus.txt", "r");		//otwieram plik w celu policzenia elementow

	int h;		//zmienna na liczbe elementow

	h = countH(axiom);		//licze wszystkie elementy niezerowe

	fclose(axiom);

	return h;		//zwracam liczbe elementow (krokow dla zolwia)
}

void vcInit(int varN, int consN, int *var, int *cons)
{
	printf("Prosze podac po kolei zmienne (w oddzielnych liniach):\n");
	for (int i = 0; i < varN; i++)
		scanf("%d", &var[i]);

	printf("\n");

	printf("Prosze podac po kolei stale (w oddzielnych liniach):\n");
	for (int i = 0; i < consN; i++)
		scanf("%d", &cons[i]);

	printf("\n");
}

void rulesInit(int **rule, int varN, int *var)
{
	for (int i = 0; i < varN; i++)		//na wszelki wypadek zeruje tablice
		for (int j = 0; j < 40; j++)
			rule[i][j] = 0;

	for (int i = 0; i < varN; i++)
	{
		int k;
		printf("Prosze podac liczbe elementow transformacji zmiennej '%d':\n", var[i]);
		scanf("%d", &k);

		printf("Prosze podac transformacje zmiennej '%d':\n", var[i]);
		for (int j = 0; j < k; j++)
			scanf("%d", &rule[i][j]);
	}
	printf("\n");
}

void axiomInit(FILE *axiom)
{
	printf("Podaj axiom (poczatkowy zestaw znakow, konczy sie '0'):\n");

	int k = 0, j = 1;
	while (j!=0)
	{
		scanf("%d", &j);
		fprintf(axiom, "%d\n", j);
		k++;
	}
}

void transformIter(FILE *axiom, int **rule, int *var, int varN, int consN, FILE *pomoc)
{
	int pom = 1;		//zmienna pomocnicza, ktora zarowno jest warunkiem trwania petli, jak rowniez warunkiem transformacji

	while (pom != 0)
	{
		fscanf(axiom, "%d ", &pom);		//skanuje element z pliku axiom
		bool zmiana = 0;		//zmienna logiczna mowiaca czy element axiomu jest jedna ze zmiennych

		for (int i = 0; i < varN; i++)		//tu dla kazdej zmiennej sprawdzam czy jest taka sama jak element axiomu
		{
			if (pom == var[i])		
			{
				zmiana = 1;		//jesli jest to zmiana zachodzi
				
				int k = 0;		//zmienna pomocnicza do petli
				while (rule[i][k] != 0)		//dopoki element zasady nie jest rowny 0, wypisuje do pliku pomocniczego elementy zasady (na poczatku tablica zasad jest wypelniona zerami)
				{
					fprintf(pomoc, "%d\n", rule[i][k]);		
					k++;
				}
			}
		}

		if (zmiana == 0)		//jesli element axiomu nie jest jedna ze zmiennych to wypisuje po prostu ten element
			fprintf(pomoc, "%d\n", pom);
	}

	fprintf(pomoc, "%d", 0);		//na koniec wypisuje zero, aby pomoc sobie dalej w liczeniu i sprawdzaniu, gdyz zalozylem na poczatku ze zaden z elementow L-systemu nie jest rowny 0
}

void rewrite(FILE *axiom, FILE *pomoc)
{
	int pom = 1;		//zmienna pomocnicza

	while (pom != 0)		//dopoki element pliku pomocniczego nie jest rowny 0 wypisuje elementy tego pliku do pliku axiom
	{
		fscanf(pomoc, "%d ", &pom);
		fprintf(axiom, "%d\n", pom);
	}
	fprintf(axiom, "%d", 0);		//na koniec dopisuje 0
}

int countH(FILE *axiom)
{
	int h = 0;		//zmienna na sume elementow, wyzerowana
	int pom = 1;	//zmienna pomocnicza

	while (pom != 0)		//licze elementy pliku dopoki element pliku axiom nie jest rowny 0 
	{
		fscanf(axiom, "%d ", &pom);
		h++;
	}

	return h;		
}