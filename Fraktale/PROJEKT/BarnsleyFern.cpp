//	PAPROC BARNSLEYA
//	program za pomoca IFS (iterated function system) dokonuje zmian wspolrzednych punktu
//	kolejne punkty narysowane w oknie tworza paproc lub inne rosliny, w zaleznosci od uzytych funkcji transfromujacych

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include"winbgi2.h"
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"BarnsleyFern.h"

void BarnsleyFern()
{
	int iter;		//zmienna na liczbe iteracji
	srand(time(NULL));

	printf("Prosze podac liczbe iteracji(punktow) paproci Barnsleya:\n");
	scanf("%d", &iter);

	double los;		//zmienna na liczbe w zakresie <0, 1>, na podstawie ktorej wybierana bedzie funkcja 

	//funkcje na podstawie ktorych przeprowadzane sa transformacje
	//sa to wektory zawierajace wspolczynniki do kolejnych dzia³añ zmieniaj¹cych wspó³rzêdne punktu
	//ostatnia pozycja jest prawdopodobienstwem wylosowania, mozna pominac, ale
	double f1[7] = { 0.0,0.0,0.0,0.16,0.0,0.0,0.01 };
	double f2[7] = { 0.85, 0.04, -0.04, 0.85, 0.0, 1.6, 0.85 };
	double f3[7] = { 0.2, -0.26, 0.23, 0.22, 0.0, 1.6, 0.07 };
	double f4[7] = { -0.15, 0.28, 0.26, 0.24, 0.0, 0.44, 0.07 };

	/*domyslne funkcje, na wypadek eksperymentowania lub nieumyslnej modyfikacji
	double f1[7] = { 0.0,0.0,0.0,0.16,0.0,0.0,0.01 };
	double f2[7] = { 0.85, 0.04, -0.04, 0.85, 0.0, 1.6, 0.85 };
	double f3[7] = { 0.2, -0.26, 0.23, 0.22, 0.0, 1.6, 0.07 };
	double f4[7] = { -0.15, 0.28, 0.26, 0.24, 0.0, 0.44, 0.07 };
	*/

	double pos[2] = {};		//pierwszy punkt paproci ma miec wspolrzedne (0, 0)

	graphics(800, 800);
	setcolor(0.5);		//wybieram kolor zielony

	//wlasciwe rysowanie i transformacje
	for (int i = 0; i <= iter; i++)
	{
		point(pos[0] + 400, -pos[1] + 600);		//rysowanie punktu wg obecnych wspolrzednych

		los = (double) rand() / RAND_MAX;		//losowanie na podstawie ktorego wybierana jest funkcja transformujaca

		if (los <= f1[6])
			transform(f1, pos);
		else if (los > f1[6] && los <= f1[6] + f3[6])
			transform(f3, pos);
		else if (los > f1[6] + f3[6] && los <= f1[6] + f3[6] + f4[6])
			transform(f4, pos);
		else
			transform(f2, pos);
	}

	printf("\nNacisnij dowolny przycisk aby zakonczyc...\n");
	getch();
}

void transform(double *f, double *pos)
{
	double pomX = pos[0];
	double pomY = pos[1];
	pos[0] = (f[0] * pomX) + (f[1] * pomY);	
	pos[1] = (f[2] * pomX) + (f[3] * pomY) + (50.0*f[5]);
}
