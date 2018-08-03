#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<math.h>
#include"Sierpinski.h"
#include"Lindenmayer.h"
#include"Turtle.h"
#include"winbgi2.h"
#include<stdlib.h>

void DragonCurve()
{
	double turtle[4];
	int iter;

	printf("Prosze podac dane zolwia ktory narysuje krzywa.\nPolozenie (x,y) lewego ogona smoka w oknie grafiki: ");
	scanf("%lf %lf", &turtle[0], &turtle[1]);
	printf("Prosze podac dlugosc smoka i kat jaki tworzy z dodatnia polosia osi x: ");
	scanf("%lf %lf", &turtle[2], &turtle[3]);

	printf("Prosze podac liczbe iteracji fraktala:\n");
	scanf("%d", &iter);

	turtle[2] *= pow(1 / sqrt(2), iter);

	printf("Dla krzywej smoczej zolw przyjmuje nastepujace oznaczenia:\n");
	printf("'1' / '2' - idz prosto\n'3' - skrec w lewo o 45 stopni\n'4' - skrec w prawo o 45 stopni\n\n");

	int h;
	h = lindenmayerManual(iter);
	printf("%d\n", h);

	FILE *dane;

	graphics(800, 800);

	dane = fopen("lindenmayer.txt", "r");

	int ruch;
	double col = 0;

	for (int i = 1; i <= h; i++)
	{
		fscanf(dane, "%d\n", &ruch);

		setcolor(col / h);

		if (ruch == 1 || ruch == 2)
			draw(turtle);
		else if (ruch == 3)
			turnL(turtle, 45);
		else if (ruch == 4)
			turnR(turtle, 45);

		col++;
	}

	printf("Nacisnij dowolny przycisk aby zakonczyc...\n");
	getch();
}

void DragonCurveAuto()
{
	double turtle[4];

	printf("Prosze podac dane zolwia ktory narysuje krzywa.\nPolozenie (x,y) lewego ogona smoka w oknie grafiki: ");
	scanf("%lf %lf", &turtle[0], &turtle[1]);
	printf("Prosze podac dlugosc smoka i kat jaki tworzy z dodatnia polosia osi x: ");
	scanf("%lf %lf", &turtle[2], &turtle[3]);

	turtle[2] *= pow(1 / sqrt(2), 18);

	FILE *dane;

	graphics(800, 800);

	int ruch;
	double col = 0;

	dane = fopen("DragonCurve18.txt", "r");

	for (int i = 1; i <= 1310717; i++)
	{
		fscanf(dane, "%d\n", &ruch);

		setcolor(col/1310717.0);

		if (ruch == 1 || ruch == 2)
			draw(turtle);
		else if (ruch == 3)
			turnL(turtle, 45);
		else if (ruch == 4)
			turnR(turtle, 45);

		col++;
	}

	fclose(dane);
	
	printf("Nacisnij dowolny przycisk aby zakonczyc...\n");
	getch();
}

void LevyCurveAuto()
{
	double turtle[4];

	printf("Prosze podac dane zolwia ktory narysuje krzywa.\nPolozenie (x,y) lewego ogona smoka w oknie grafiki: ");
	scanf("%lf %lf", &turtle[0], &turtle[1]);
	printf("Prosze podac dlugosc smoka i kat jaki tworzy z dodatnia polosia osi x: ");
	scanf("%lf %lf", &turtle[2], &turtle[3]);

	turtle[2] *= pow(1 / sqrt(2), 15);

	FILE *dane;

	graphics(800, 800);

	int ruch;
	double col = 0;

	dane = fopen("LevyCurve15.txt", "r");

	for (int i = 1; i <= 163837; i++)
	{
		fscanf(dane, "%d\n", &ruch);

		setcolor(col / 163837.0);

		if (ruch == 1 || ruch == 2)
			draw(turtle);
		else if (ruch == 3)
			turnL(turtle, 45);
		else if (ruch == 4)
			turnR(turtle, 45);

		col++;
	}

	fclose(dane);

	printf("Nacisnij dowolny przycisk aby zakonczyc...\n");
	getch();
}

void DragonCurvePlus()
{
	double turtle[4];
	int iter;

	printf("Prosze podac dane zolwia ktory narysuje krzywa.\nPolozenie (x,y) lewego ogona smoka w oknie grafiki: ");
	scanf("%lf %lf", &turtle[0], &turtle[1]);
	printf("Prosze podac dlugosc smoka i kat jaki tworzy z dodatnia polosia osi x: ");
	scanf("%lf %lf", &turtle[2], &turtle[3]);

	printf("Prosze podac liczbe iteracji fraktala:\n");
	scanf("%d", &iter);

	turtle[2] *= pow(1.0 / sqrt(2), iter);

	int *var;
	var = (int*)malloc(2 * sizeof(int));
	var[0] = 1;
	var[1] = 2;
	int varN = 2;

	int **rule;
	rule = (int**)malloc(2 * sizeof(int*));
	rule[0] = (int*)malloc(40 * sizeof(int));
	rule[1] = (int*)malloc(40 * sizeof(int));

	for (int i = 0; i < 40; i++)
	{
		rule[0][i] = 0;
		rule[1][i] = 0;
	}

	FILE *rule1;
	rule1 = fopen("dragonrule1.txt", "r");

	for (int i = 0; i < 6; i++)
		fscanf(rule1, "%d", &rule[0][i]);

	for (int i = 0; i < 6; i++)
		fscanf(rule1, "%d", &rule[1][i]);

	fclose(rule1);

	FILE *axiom;
	axiom = fopen("lindenmayerPlus.txt", "w");
	fprintf(axiom, "%d %d", 1, 0);
	fclose(axiom);

	int h;
	h = lindenmayerPlus(iter, var, varN, rule);

	graphics(800, 800);

	FILE *dane;
	dane = fopen("lindenmayerPlus.txt", "r");
	
	int ruch;

	setcolor(0.2);

	for (int i = 1; i <= h; i++)
	{
		fscanf(dane, "%d ", &ruch);

		if (ruch == 1 || ruch == 2)
			draw(turtle);
		else if (ruch == 3)
			turnL(turtle, 45);
		else if (ruch == 4)
			turnR(turtle, 45);

	}

	printf("Nacisnij dowolny przycisk aby zakonczyc...\n");
	getchar();
	getchar();
}
