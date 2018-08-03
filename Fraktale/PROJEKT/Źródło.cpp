#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include"Lindenmayer.h"
#include"KochCurve.h"
#include"Turtle.h"
#include"winbgi2.h"
#include"ComplexDivergence.h"
#include"Sierpinski.h"
#include"Vicsec.h"
#include"BarnsleyFern.h"
#include"DragonCurve.h"

int main(void)
{
	int ver, ver1;
	printf("***FRAKTALE***\n\n");
	printf("Okno grafiki ma rozmiar 800x800.\n");
	printf("Program rysuje nastepujace fraktale:\n1. Platek Kocha\n2. Wyspa Kocha\n3. Trojkat Sierpinskiego\n4. Fraktal Vicseca\n5. Fraktale na liczbach zespolonych\n6. Paproc Barnsleya\n7. Krzywa Smocza\n\n");
	printf("Prosze wybrac wg numerka: ");
	scanf("%d", &ver);

	printf("\n\n");

	if (ver == 1)
	{
		printf("Opcje rysowania:\n1. Samodzielnie\n2. Automatycznie z okreslona liczba iteracji (szybko)\n3. Automatycznie\n\nProsze wybrac: ");
		scanf("%d", &ver1);
		printf("\n\n");

		if (ver1 == 1)
			KochFlake();
		else if (ver1 == 2)
			KochFlakeAuto();
		else if (ver1 == 3)
			KochFlakePlus();
	}
	else if (ver == 2)
	{
		printf("Opcje rysowania:\n1. Samodzielnie\n2. Automatycznie z okreslona liczba iteracji (szybko)\n3. Automatycznie\n\nProsze wybrac: ");
		scanf("%d", &ver1);
		printf("\n\n");

		if (ver1 == 1)
			KochIsland();
		else if (ver1 == 2)
			KochIslandAuto();
		else if (ver1 == 3)
			KochIslandPlus();
	}
	else if (ver == 3)
	{
		printf("Opcje rysowania:\n1. Samodzielnie\n2. Automatycznie z okreslona liczba iteracji (szybko) - zaokraglony\n3. Automatycznie z okreslona liczba iteracji (szybko) - normalny\n4. Automatycznie\n\nProsze wybrac: ");
		scanf("%d", &ver1);
		printf("\n\n");
		if (ver1 == 1)
			Sierpinski();
		else if (ver1 == 2)
			SierpinskiRoundedAuto();
		else if (ver1 == 3)
			SierpinskiAuto();
		else if (ver1 == 4)
			SierpinskiPlus();
	}
	else if (ver == 4)
	{
		printf("Opcje rysowania:\n1. Samodzielnie\n2. Automatycznie\n\nProsze wybrac: ");
		scanf("%d", &ver1);
		printf("\n\n");

		if (ver1 == 1)
			VicsecFractal();
		else
			VicsecFractalAuto();
	}
	else if (ver == 5)
		ComplexDivergence();
	else if (ver == 6)
		BarnsleyFern();
	else if(ver==7)
	{
		printf("Opcje rysowania:\n1. Samodzielnie\n2. Automatycznie z okreslona liczba iteracji (szybko) - zwykla krzywa smocza\n3. Automatycznie z okreslona liczba iteracji (szybko) - krzywa Levy'ego\n4. Automatycznie\n\nProsze wybrac: ");
		scanf("%d", &ver1);
		printf("\n\n");

		if (ver1 == 1)
			DragonCurve();
		else if (ver1 == 2)
			DragonCurveAuto();
		else if (ver1 == 3)
			LevyCurveAuto();
		else if (ver1 == 4)
			DragonCurvePlus();
	}
	else
	{
		printf("Blad! Niewlasciwy numer!\nWprowadz dowolny znak aby wyjsc z programu...\n");
		getchar();
		getchar();
	}
}
