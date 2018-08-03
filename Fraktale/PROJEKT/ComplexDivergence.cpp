#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include"winbgi2.h"
#include<math.h>
#include"ComplexDivergence.h"

const double pi = 4.0 * atan(1.0);
const double dokl = 1000;		//dokladnosc liczenia, czyli maksymalna liczba zastosowan funkcji


void ComplexDivergence()
{
	double z[2] = {};		//dwie tablice, odpowiednio na liczby zespolone 'z' oraz 'c' uzywane we wzorach rekurencyjnych fraktali 
	double c[2] = {};

	int ver;		//zmienne dokladnosci liczenia oraz wersji, czyli wyboru jednego z fraktali

	printf("Prosze podac, ktory fraktal chcesz otrzymac:\n1. Zbior Mandelbrota\n2. Zbior Julii\n3. Plonacy Statek\n4. Armada z Plonacego Statku\n5. BuddhaBrot\nProsze wybrac:");
	scanf("%d", &ver);

	if (ver == 2)
	{
		printf("Prosze podac poczatkowe wspolczynniki a oraz b liczby zespolonej c = a + i*b dla zbioru Julii:\n");		//dla zbioru Julii dodatlowo okreslamy na poczatku poczatkowe 'c'
		scanf("%lf %lf", &c[0], &c[1]);
	}

	if (ver == 1 || ver == 2)
	{
		graphics(910, 910);

		for (int i = 0; i < 900; i++)		//dla kazdego piksela licze odpowiadajacy mu ciag liczb zespolonych
			for (int j = 0; j < 900; j++)
			{
				double x = (i / 300.0) - 2.0;		//odpowiednio zmieniam wspolrzedne, aby otrzymac uklad (-2, 1) x (-1.5, 1.5)
				double y = (j / 300.0) - 1.5;

				if (ver == 1)		//dla zbioru Mandelbrota dla kazdego piksela trzeba definiowac na nowo 'z' oraz 'c', co wynika z budowy funkcji
				{
					z[0] = 0;
					z[1] = 0;

					c[0] = x;
					c[1] = y;
				}
				else		//dla zbioru Julii dla kazdego piksela na poczatku 'z' przyjmuje postac x + yi				
				{
					z[0] = x;
					z[1] = y;
				}

				double r;		//zmienna przechowujaca wartosc koloru
				r = divergence(z, c, dokl, ver);		//kolor jest obliczany z funkcji divergence

				setcolor(r);		//ustawiam kolor
				point(i, j);		//i rysuje punkt odpowiadajacy rozpatrywanemu obecnie pikselowi
			}
	}
	else if(ver == 3)
	{
		graphics(910, 910);

		for (int i = 0; i < 900; i++)
			for (int j = 0; j < 900; j++)
			{
				double x = (i / 300.0) - 2.0;		//chce otrzymac uklad taki sam jak dla zbioru Mandelbrota
				double y = (j / 300.0) - 2.0;

				z[0] = 0;		//dla kazdego piksela na nowo definiuje 'z' oraz 'c'
				z[1] = 0;

				c[0] = x;
				c[1] = y;

				double r;		//zmienna przechowujaca wartosc koloru
				r = divergence(z, c, dokl, ver);		//kolor obliczany z funkcji divergence

				setcolor(r);		//ustawiam kolor
				point(i, j);		//rysuje punkt odpowiadajacy obecnie rozpatrywanemu pikselowi
			}
	}
	else if (ver == 4)		//tu podobnie jak wyzej ale ze zmienionym ukladem wspolrzednych
	{
		graphics(910, 910);

		for (int i = 0; i < 900; i++)
			for (int j = 0; j < 900; j++)
			{
				double x = (i / 1800.0) - 1.87;
				double y = (j / 1800.0) - 0.3;

				z[0] = 0;
				z[1] = 0;

				c[0] = x;
				c[1] = y;

				double r;
				r = divergence(z, c, dokl, ver);
				
				setcolor(r);
				point(i, j);
			}
	}
	else if (ver == 10)		//czesc dla fraktala Newtona, nieudana czesc ale do naprawienia
	{
		double **root;

		root = (double**)malloc(3 * sizeof(double*));
		for (int i = 0; i < 3; i++)
			root[i] = (double*)malloc(2 * sizeof(double));

		root[0][0] = 1.0;
		root[0][1] = 0.0;

		root[1][0] = -0.5;
		root[1][1] = -0.86603;

		root[2][0] = -0.5;
		root[2][1] = 0.86603;

		double eps, a;
		printf("Prosze podac epsilon szukanych pierwiastkow oraz wspolczynnik a:\n");
		scanf("%lf %lf", &eps, &a);

		graphics(910, 910);

		for (int i = 0; i < 900; i++)
			for (int j = 0; j < 900; j++)
			{
				double x = (i / 300.0) - 2.0;
				double y = (j / 300.0) - 2.0;

				z[0] = x;
				z[1] = y;

				double r;
				r = divergenceNewton(z, root, dokl, eps, a);
				
				setcolor(r);
				point(i, j);
			}
	}
	else if (ver == 5)
	{
		int *licz[900];		//alokuje tablice na sumy punktow
		for (int k = 0; k < 900; k++)
			licz[k] = (int*)malloc(900 * sizeof(int));


		for (int i = 0; i < 900; i++)		//zeruje tablice zeby moc liczyc punkty
			for (int j = 0; j < 900; j++)
				licz[i][j] = 0;

		double maxL = 0;

		for(int i=0; i<900; i++)
			for (int j = 0; j < 900; j++)
			{
				double x = (i / 300.0) - 2.0;
				double y = (j / 300.0) - 1.5;

				z[0] = 0;
				z[1] = 0;

				c[0] = x;
				c[1] = y;

				BuddhaBrot(z, c, licz, dokl);
			}

		graphics(910, 910);

		//znajduje maksymalna liczbe w tablicy zeby na podstawie tego przydzielac kolor
		for (int k = 0; k < 900; k++)
			for (int h = 0; h < 900; h++)
				if (licz[k][h] > maxL)
					maxL = licz[k][h];

		for(int i = 0; i<900; i++)
			for (int j = 0; j < 900; j++)
			{
				double r;
				double t = (double)licz[i][j];
				r = (double)(t / maxL);
				setcolor(r);
				point(i, j);
			}
	}

	printf("\nNacisnij dowolny przycisk aby zakonczyc...\n");
	getch();
}

double divergenceNewton(double *z, double **root, int dokl, double eps, double a)
{
	int wynik = 0;
	double prom = 2;
	int licz = 0;
	int iter = 0;
	while ( licz <= dokl)
	{
		double pom[2];
		pom[0] = z[0];
		pom[1] = z[1];

		double pom2[2];
		pom2[0] = z[0];
		pom2[1] = z[1];

		double pom3[2];
		pom3[0] = 1;
		pom3[1] = 0;

		powIm(z, 3);
		z[0] -= 1;

		z[0] -= (1 / 3.0)*pom[0];
		z[1] -= (1 / 3.0)*pom[1];

		powIm(pom2, 2);
		pom3[0] *= 3;
		pom3[1] *= 3;

		double wyn[2] = {};

		divIm(pom3, pom2, wyn);

		z[0] += wyn[0];
		z[1] += wyn[1];

		for(int i=0; i<3; i++)
			if (sqrt(pow(z[0] - root[i][0], 2) + pow(z[1] - root[i][1], 2)) <= prom)
			{
				prom = sqrt(pow(z[0] - root[i][0], 2) + pow(z[1] - root[i][1], 2));
				wynik = i + 1;
				iter = licz;
				licz = dokl + 1;
			}

		licz++;
	}

		return (double)(log1p(licz) / log1p(dokl));
		//return (double)(licz / dokl);
		//return (double)(argZ(z) / (pi/2.0));
		//return (double)(iter / dokl);
		//return wynik / 3.0;
}

double divergence(double *z, double *c, int dokl, int ver)
{
	int licz = 0;

	while (z[0] * z[0] + z[1] * z[1] < 25.0 && licz <= dokl)
	{
		if (ver == 1 || ver == 2)
		{
			powIm(z, 2);
			addIm(z, c);
		}
		else if (ver == 3 || ver == 4)
			burningIter(z, c);

		licz++;
	}

	if (licz == dokl)
		return 0;
	
	//3 rozne sposoby zwracania wartosci, gwarantuja rozne kolorowanie pikseli
	return (double)(log1p(licz) / log1p(dokl));		//uzywam log1p, aby program nie crashowal sie, gdyby uzytkownik chcial liczyc rozbieznosc dla liczb zespolonych o promieniu wiekszym niz 5
	//return (double)(licz / dokl);
	//return (double)(argZ(z) / (pi/2.0));			//najciekawszy kolorystycznie sposob kolorowania
}

void BuddhaBrot(double *z, double *c, int **licz, int dokl)
{
	int liczI = 0;

	while (z[0] * z[0] + z[1] * z[1] < 4.0 && liczI <= dokl)
	{
		powIm(z, 2);
		addIm(z, c);

		double x = (300.0 * (z[0] + 2.0));
		double y = (300.0 * (z[1] + 1.5));

		if (x - (int)x >= 0.5)
			x++;

		if (y - (int)y >= 0.5)
			y++;

		int x1 = x, y1 = y;

		if (x < 900 && y < 900 && x>=0 && y>=0)
			licz[x1][y1] ++;

		liczI++;
	}
}

void powIm(double *z, int n)
{
	for (int i = 1; i < n; i++)
	{
		double x = z[0];
		double y = z[1];

		z[0] = x*x - y*y;
		z[1] = 2.0 * x*y;
	}
}

void pow2Im(double *z)
{
	double x, y;

	x = z[0];
	y = z[1];

	z[0] = x*x - y*y;
	z[1] = 2.0 * x*y;
}

void addIm(double *z, double *c)
{
	z[0] += c[0];
	z[1] += c[1];
}

void burningIter(double *z, double *c)
{
	z[0] = fabs(z[0]);
	z[1] = fabs(z[1]);

	pow2Im(z);
	addIm(z, c);
}

double argZ(double *z)
{
	if (z[0] == 0)
		return pi / 2.0;

	return atan(fabs(z[1] / z[0]));
}

void divIm(double *z, double *c, double *wyn)
{
	double k = sqrt(pow(c[0], 2) + pow(c[1], 2));

	double x = (z[0] * c[0]) + (z[1] * c[1]);
	double y = (z[1] * c[0]) - (z[0] * c[1]);

	wyn[0] = x / k;
	wyn[1] = y / k;
}