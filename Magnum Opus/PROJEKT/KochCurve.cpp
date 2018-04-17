#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include"winbgi2.h"
#include"Lindenmayer.h"
#include"Turtle.h"
#include"KochCurve.h"
#include<math.h>

const double pi = 4 * atan(1.0);

void KochFlake()
{
	double turtle[4];
	int iter;

	printf("Prosze podac dane zolwia ktory narysuje platek.\nPolozenie (x,y) w oknie grafiki: ");
	scanf("%lf %lf", &turtle[0], &turtle[1]);
	printf("Prosze podac dlugosc jednego boku platka i kat jaki tworzy z dodatnia polosia osi x: ");
	scanf("%lf %lf", &turtle[2], &turtle[3]);

	printf("Prosze podac liczbe iteracji fraktala:\n");
	scanf("%d", &iter);

	turtle[2] *= (double)pow(1.0/3.0, iter);

	printf("Dla krzywej Kocha zolw przyjmuje nastepujace oznaczenia:\n");
	printf("'1' - idz prosto\n'2' - skrec w prawo o 60 stopni\n'3' - skrec w lewo o 60 stopni\n\n");

	int h;
	h = lindenmayerManual(iter);
	printf("%d\n", h);

	FILE *dane;
	
	graphics(800, 800);

	for (int j = 0; j < 6; j++)
	{
		dane = fopen("lindenmayer.txt", "r");

		for (int i = 1; i <= h; i++)
		{
			int ruch;
			fscanf(dane, "%d\n", &ruch);

			if (ruch == 1)
				draw(turtle);
			else if (ruch == 2)
				turnL(turtle, 60);
			else if (ruch == 3)
				turnR(turtle, 60);
		}

		fclose(dane);
		turnR(turtle, 60);
	}

	printf("Nacisnij dowolny przycisk aby zakonczyc...\n");
	getch();
}

void KochFlakeAuto()
{
	double turtle[4];

	printf("Prosze podac polozenie srodka platka Kocha (x,y) oraz dlugosc jednego boku platka:\n");
	scanf("%lf %lf %lf", &turtle[0], &turtle[1], &turtle[2]);

	turtle[1] -= turtle[2];
	turtle[3] = 330.0;

	turtle[2] *= pow(1 / 3.0, 10);

	FILE *dane;

	graphics(800, 800);

	int ruch;
	double col = 0;

	for (int j = 0; j < 6; j++)
	{
		dane = fopen("KochCurve10.txt", "r");

		for (int i = 1; i <= 2446677; i++)
		{
			fscanf(dane, "%d\n", &ruch);

			setcolor(fabs(cos(pi*col / 2446677.0 / 6.0)));

			if (ruch == 1)
				draw(turtle);
			else if (ruch == 2)
				turnL(turtle, 60);
			else if (ruch == 3)
				turnR(turtle, 60);

			col++;
		}

		fclose(dane);
		turnR(turtle, 60);
	}

	printf("Nacisnij dowolny przycisk aby zakonczyc...\n");
	getch();
}

void KochIsland()
{
	double turtle[4];
	int iter;

	printf("Prosze podac dane zolwia ktory narysuje wyspe.\nPolozenie (x,y) w oknie grafiki: ");
	scanf("%lf %lf", &turtle[0], &turtle[1]);
	printf("Prosze podac dlugosc jednego boku wyspy i kat jaki tworzy z dodatnia polosia osi x: ");
	scanf("%lf %lf", &turtle[2], &turtle[3]);

	printf("Prosze podac liczbe iteracji fraktala:\n");
	scanf("%d", &iter);

	turtle[2] *= (double)pow(1.0 / 4.0, iter);

	printf("Dla krzywej Kocha (wyspy) zolw przyjmuje nastepujace oznaczenia:\n");
	printf("'1' - idz prosto\n'2' - skrec w prawo o 90 stopni\n'3' - skrec w lewo o 90 stopni\n\n");

	int h;
	h = lindenmayerManual(iter);
	printf("%d\n", h);

	FILE *dane;

	graphics(800, 800);

	int ruch;
	double col = 0;

	for (int j = 0; j < 4; j++)
	{
		dane = fopen("lindenmayer.txt", "r");

		for (int i = 1; i <= h; i++)
		{
			fscanf(dane, "%d\n", &ruch);

			setcolor(col / h);

			if (ruch == 1)
				draw(turtle);
			else if (ruch == 2)
				turnR(turtle, 90);
			else if (ruch == 3)
				turnL(turtle, 90);

			col++;
		}

		fclose(dane);
		turnR(turtle, 90);
	}

	printf("Nacisnij dowolny przycisk aby zakonczyc...\n");
	getch();
}

void KochIslandAuto()
{
	double turtle[4];

	printf("Prosze podac polozenie srodka wyspy Kocha (x,y) oraz jego odleglosc od rogu wyspy:\n");
	scanf("%lf %lf %lf", &turtle[0], &turtle[1], &turtle[2]);

	turtle[1] -= turtle[2];
	turtle[3] = 315.0;

	turtle[2] *= pow(1 / 4.0, 6);

	FILE *dane;

	graphics(800, 800);

	int ruch;
	double col = 0;

	for (int j = 0; j < 4; j++)
	{
		dane = fopen("KochIsland6.txt", "r");

		for (int i = 1; i <= 486839; i++)
		{
			fscanf(dane, "%d\n", &ruch);

			setcolor(fabs(cos(pi* col / 486839.0 / 4.0)));

			if (ruch == 1)
				draw(turtle);
			else if (ruch == 2)
				turnL(turtle, 90);
			else if (ruch == 3)
				turnR(turtle, 90);

			col++;
		}

		fclose(dane);
		turnR(turtle, 90);
	}

	printf("Nacisnij dowolny przycisk aby zakonczyc...\n");
	getch();
}

void KochFlakePlus()
{
	double turtle[4];
	int iter;

	printf("Prosze podac dane zolwia ktory narysuje platek.\nPolozenie (x,y) w oknie grafiki: ");
	scanf("%lf %lf", &turtle[0], &turtle[1]);
	printf("Prosze podac dlugosc jednego boku platka i kat jaki tworzy z dodatnia polosia osi x: ");
	scanf("%lf %lf", &turtle[2], &turtle[3]);

	printf("Prosze podac liczbe iteracji fraktala:\n");
	scanf("%d", &iter);

	turtle[2] *= (double)pow(1.0 / 3.0, iter);

	int *var;
	var = (int*)malloc(sizeof(int));
	var[0] = 1;
	int varN = 1;

	int **rule;
	rule = (int**)malloc(sizeof(int*));
	rule[0] = (int*)malloc(40 * sizeof(int));
	
	for (int i = 0; i < 40; i++)
		rule[0][i] = 0;

	FILE *rule1;
	rule1 = fopen("kochrule1.txt", "r");

	for (int i = 0; i < 8; i++)
		fscanf(rule1, "%d ", &rule[0][i]);

	fclose(rule1);

	FILE *axiom;
	axiom = fopen("lindenmayerPlus.txt", "w");
	fprintf(axiom, "%d\n%d", 1, 0);
	fclose(axiom);

	int h = lindenmayerPlus(iter, var, varN, rule);
	FILE *dane;

	graphics(800, 800);

	int ruch;

	for (int j = 0; j < 6; j++)
	{
		dane = fopen("lindenmayerPlus.txt", "r");

		for (int i = 1; i <= h; i++)
		{
			fscanf(dane, "%d", &ruch);

			if (ruch == 1)
				draw(turtle);
			else if (ruch == 2)
				turnL(turtle, 60);
			else if (ruch == 3)
				turnR(turtle, 60);
		}

		fclose(dane);
		turnR(turtle, 60);
	}

	printf("Nacisnij dowolny przycisk aby zakonczyc...\n");
	getch();
}

void KochIslandPlus()
{
	double turtle[4];
	int iter;

	printf("Prosze podac dane zolwia ktory narysuje platek.\nPolozenie (x,y) w oknie grafiki: ");
	scanf("%lf %lf", &turtle[0], &turtle[1]);
	printf("Prosze podac dlugosc jednego boku platka i kat jaki tworzy z dodatnia polosia osi x: ");
	scanf("%lf %lf", &turtle[2], &turtle[3]);

	printf("Prosze podac liczbe iteracji fraktala:\n");
	scanf("%d", &iter);

	turtle[2] *= (double)pow(1.0 / 4.0, iter);

	int *var;
	var = (int*)malloc(sizeof(int));
	var[0] = 1;
	int varN = 1;

	int **rule;
	rule = (int**)malloc(sizeof(int*));
	rule[0] = (int*)malloc(40 * sizeof(int));

	for (int i = 0; i < 40; i++)
		rule[0][i] = 0;

	FILE *rule1;
	rule1 = fopen("islandrule1.txt", "r");

	for (int i = 0; i < 14; i++)
		fscanf(rule1, "%d", &rule[0][i]);

	fclose(rule1);

	FILE *axiom;
	axiom = fopen("lindenmayerPlus.txt", "w");
	//fprintf(axiom, "%d %d %d %d %d %d %d %d %d", 1, 2, 1, 2, 1, 2, 1, 2, 0);
	fprintf(axiom, "%d %d", 1, 0);
	fclose(axiom);

	int h = lindenmayerPlus(iter, var, varN, rule);
	FILE *dane;

	graphics(800, 800);

	int ruch;
	double col = 0;

	for (int j = 0; j < 4; j++)
	{
		dane = fopen("lindenmayerPlus.txt", "r");
		for (int i = 1; i <= h; i++)
		{
			fscanf(dane, "%d", &ruch);

			setcolor(col / h / 4.0);

			if (ruch == 1)
				draw(turtle);
			else if (ruch == 2)
				turnR(turtle, 90);
			else if (ruch == 3)
				turnL(turtle, 90);

			col++;
		}

		turnR(turtle, 90);
	}

	fclose(dane);

	printf("Nacisnij dowolny przycisk aby zakonczyc...\n");
	getch();
}