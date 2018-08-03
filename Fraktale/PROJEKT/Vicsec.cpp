#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<math.h>
#include"Lindenmayer.h"
#include"winbgi2.h"
#include"Turtle.h"
#include"Vicsec.h"

void VicsecFractal()
{
	double turtle[4];
	int iter;

	printf("Prosze podac dane zolwia ktory narysuje fraktal Vicseca.\nPolozenie (x,y) lewego dolnego rogu fraktala w oknie grafiki: ");
	scanf("%lf %lf", &turtle[0], &turtle[1]);
	printf("Prosze podac dlugosc boku fraktala i kat jaki tworzy on z dodatnia polosia osi x: ");
	scanf("%lf %lf", &turtle[2], &turtle[3]);

	printf("Prosze podac liczbe iteracji fraktala:\n");
	scanf("%d", &iter);

	turtle[2] *= pow(1.0 / 3.0, iter);

	printf("Dla fraktala Vicseca zolw przyjmuje nastepujace oznaczenia:\n");
	printf("'1' - idz prosto\n'2' - skrec w lewo o 90 stopni\n'3' - skrec w prawo o 90 stopni\n\n");

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

		if (ruch == 1)
			draw(turtle);
		else if (ruch == 2)
			turnL(turtle, 90);
		else if (ruch == 3)
			turnR(turtle, 90);

		col++;
	}

	printf("Nacisnij dowolny przycisk aby zakonczyc...\n");
	getchar();
	getchar();
}

void VicsecFractalAuto()
{
	double turtle[4];

	printf("Prosze podac dane zolwia ktory narysuje fraktal Vicseca.\nPolozenie (x,y) lewego dolnego rogu fraktala w oknie grafiki: ");
	scanf("%lf %lf", &turtle[0], &turtle[1]);
	printf("Prosze podac dlugosc boku fraktala i kat jaki tworzy on z dodatnia polosia osi x: ");
	scanf("%lf %lf", &turtle[2], &turtle[3]);

	turtle[2] *= pow(1.0 / 3.0, 8);

	FILE *dane;
	dane = fopen("Vicsec8.txt", "r");

	graphics(800, 800);

	int ruch;
	double col = 0;

	for (int i = 1; i <= 3125001; i++)
	{
		fscanf(dane, "%d", &ruch);

		setcolor(col / 3125001.0);

		if (ruch == 1)
			draw(turtle);
		else if (ruch == 2)
			turnL(turtle, 90);
		else if (ruch == 3)
			turnR(turtle, 90);

		col++;
	}

	printf("Nacisnij dowolny przycisk aby zakonczyc...\n");
	getch();
}