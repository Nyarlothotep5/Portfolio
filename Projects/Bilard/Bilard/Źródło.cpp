#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"winbgi2.h"

void tableDraw();
void ballShow(double **bil);
void ballInit(double **bil);
void ballMove(double **ball);
void ballPoint(double **ball);
void whiteShot(double **ball, double x, double y);
void whiteFail(double **ball);
void wallHit(double **ball);
void collideBall(double **ball);

double iloczynSkalarnyWek(double *x, double *y);

const double st1 = 366.0 * 2;		//dlugosc dluzszego boku stolu
const double st2 = st1 / 2.0;		//dlugosc krotszego boku stolu
const double ods = 50.0;			//odstep miedzy stolem a krawedzia okna graficznego
const double ballRad = 12;			//promien bili
const double enDis = 0.99;			//wspolczynnik utraty energii w czasie (cos jak wspolczynnik tarcia)

int n = 15;

int main(void)
{
	double **ball;

	ball = (double**)malloc(4 * sizeof(double*));
	for (int i = 0; i<4; i++)
		ball[i] = (double*)malloc(16 * sizeof(double));

	ballInit(ball);
	graphics(st1 + 3 * ods, st2 + 3 * ods);

	while (animate(60) && n != 0)
	{
		tableDraw();
		ballShow(ball);

		if (mousedown() && fabs(ball[2][0]) < 0.01 && fabs(ball[3][0]) < 0.01)
		{
			double x = mouseclickx();
			double y = mouseclicky();

			whiteShot(ball, x, y);
		}

		ballMove(ball);
		collideBall(ball);
		wallHit(ball);
		whiteFail(ball);
		ballPoint(ball);
	}

	wait();
}

void tableDraw()
{
	double tloX[4] = { 0, st1 + 4 * ods, st1 + 4 * ods, 0 };
	double tloY[4] = { 0, 0, st2 + 4 * ods, st2 + 4 * ods };

	double stolX[4] = { ods, ods + st1, ods + st1, ods };
	double stolY[4] = { ods, ods, ods + st2, ods + st2 };

	setgray(0.3);

	polygon(tloX, tloY, 4);

	setcolor(0.47);

	polygon(stolX, stolY, 4);

	pieslice(ods, ods, 0, 360, 2 * ballRad);
	pieslice(ods + st1 / 2.0, ods, 0, 360, 2 * ballRad);
	pieslice(ods + st1, ods, 0, 360, 2 * ballRad);

	pieslice(ods, ods + st2, 0, 360, 2 * ballRad);
	pieslice(ods + st1 / 2.0, ods + st2, 0, 360, 2 * ballRad);
	pieslice(ods + st1, ods + st2, 0, 360, 2 * ballRad);

	setgray(1);

	line(ods + st1 / 4.0, ods, ods + st1 / 4.0, ods + st2);
}

void ballShow(double **ball)
{
	setgray(1.0);
	pieslice(ball[0][0], ball[1][0], 0, 360, ballRad);

	setcolor(0.0);
	for (int i = 1; i < 16; i++)
		pieslice(ball[0][i], ball[1][i], 0, 360, ballRad);
}

void ballInit(double **ball)
{
	srand(time(NULL));

	ball[0][0] = ods + st1 / 4.0 - 15;
	ball[1][0] = ods + st2 / 2.0;
	ball[2][0] = 0;
	ball[3][0] = 0;

	int L1 = (int)(ods + st1 - ballRad * 2.0) - (ods + st1 / 4.0) + 1;
	int L2 = (int)(ods + st2 - ballRad * 2.0) - (ods + ballRad*2.0) + 1;

	for (int i = 1; i < 16; i++)
	{
		ball[0][i] = rand() % L1 + (ods + st1 / 4.0);
		ball[1][i] = rand() % L2 + (ods + ballRad*2.0);
		ball[2][i] = 0;
		ball[3][i] = 0;

		bool ok = 1;

		for (int j = i - 1; j > 0; j--)
			if (pow(ball[0][i] - ball[0][j], 2) + pow(ball[1][i] - ball[1][j], 2) <= pow(ballRad*2.05, 2))
				ok = 0;

		while (ok == 0)
		{
			ok = 1;

			ball[0][i] = rand() % L1 + (ods + st1 / 4.0);
			ball[1][i] = rand() % L2 + (ods + ballRad*2.0);

			for (int j = i - 1; j > 0; j--)
				if (pow(ball[0][i] - ball[0][j], 2) + pow(ball[1][i] - ball[1][j], 2) <= pow(ballRad*2.05, 2))
					ok = 0;
		}
	}
}

void ballMove(double **ball)
{
	for (int i = 0; i < 16; i++)
	{
		ball[0][i] += ball[2][i];
		ball[1][i] += ball[3][i];

		ball[2][i] *= sqrt(enDis);
		ball[3][i] *= sqrt(enDis);
	}
}

void ballPoint(double **ball)
{
	for (int i = 1; i < 16; i++)
	{
		if (pow(ball[0][i] - ods, 2) + pow(ball[1][i] - ods, 2) <= pow(ballRad*3.0, 2))
		{
			n--;
			ball[0][i] = 1000;
			ball[1][i] = 1000;
			ball[2][i] = 0;
			ball[3][i] = 0;
		}
		else if (pow(ball[0][i] - (ods + st1 / 2.0), 2) + pow(ball[1][i] - ods, 2) <= pow(ballRad*3.0, 2))
		{
			n--;
			ball[0][i] = 1000;
			ball[1][i] = 1000;
			ball[2][i] = 0;
			ball[3][i] = 0;
		}
		else if (pow(ball[0][i] - (ods + st1), 2) + pow(ball[1][i] - ods, 2) <= pow(ballRad*3.0, 2))
		{
			n--;
			ball[0][i] = 1000;
			ball[1][i] = 1000;
			ball[2][i] = 0;
			ball[3][i] = 0;
		}
		else if (pow(ball[0][i] - ods, 2) + pow(ball[1][i] - (ods + st2), 2) <= pow(ballRad*3.0, 2))
		{
			n--;
			ball[0][i] = 1000;
			ball[1][i] = 1000;
			ball[2][i] = 0;
			ball[3][i] = 0;
		}
		else if (pow(ball[0][i] - (ods + st1 / 2.0), 2) + pow(ball[1][i] - (ods + st2), 2) <= pow(ballRad*3.0, 2))
		{
			n--;
			ball[0][i] = 1000;
			ball[1][i] = 1000;
			ball[2][i] = 0;
			ball[3][i] = 0;
		}
		else if (pow(ball[0][i] - (ods + st1), 2) + pow(ball[1][i] - (ods + st2), 2) <= pow(ballRad*3.0, 2))
		{
			n--;
			ball[0][i] = 1000;
			ball[1][i] = 1000;
			ball[2][i] = 0;
			ball[3][i] = 0;
		}
	}
}

void whiteShot(double **ball, double x, double y)
{
	ball[2][0] = (x - ball[0][0]) / (st2 / 6.0);		//to nie pomylka ze w obu st2, chce taki sam stosunek
	ball[3][0] = (y - ball[1][0]) / (st2 / 6.0);
}

void whiteFail(double **ball)
{
	if (pow(ball[0][0] - ods, 2) + pow(ball[1][0] - ods, 2) <= pow(ballRad*3.0, 2))			//trzy gorne dziury
	{
		ball[0][0] = ods + st1 / 4.0 - 15;
		ball[1][0] = ods + st2 / 2.0;
		ball[2][0] = 0;
		ball[3][0] = 0;
	}
	else if (pow(ball[0][0] - (ods + st1 / 2.0), 2) + pow(ball[1][0] - ods, 2) <= pow(ballRad*3.0, 2))
	{
		ball[0][0] = ods + st1 / 4.0 - 15;
		ball[1][0] = ods + st2 / 2.0;
		ball[2][0] = 0;
		ball[3][0] = 0;
	}
	else if (pow(ball[0][0] - (ods + st1), 2) + pow(ball[1][0] - ods, 2) <= pow(ballRad*3.0, 2))
	{
		ball[0][0] = ods + st1 / 4.0 - 15;
		ball[1][0] = ods + st2 / 2.0;
		ball[2][0] = 0;
		ball[3][0] = 0;
	}
	else if (pow(ball[0][0] - ods, 2) + pow(ball[1][0] - (ods + st2), 2) <= pow(ballRad*3.0, 2))		//trzy dolne dziury
	{
		ball[0][0] = ods + st1 / 4.0 - 15;
		ball[1][0] = ods + st2 / 2.0;
		ball[2][0] = 0;
		ball[3][0] = 0;
	}
	else if (pow(ball[0][0] - (ods + st1 / 2.0), 2) + pow(ball[1][0] - (ods + st2), 2) <= pow(ballRad*3.0, 2))
	{
		ball[0][0] = ods + st1 / 4.0 - 15;
		ball[1][0] = ods + st2 / 2.0;
		ball[2][0] = 0;
		ball[3][0] = 0;
	}
	else if (pow(ball[0][0] - (ods + st1), 2) + pow(ball[1][0] - (ods + st2), 2) <= pow(ballRad*3.0, 2))
	{
		ball[0][0] = ods + st1 / 4.0 - 15;
		ball[1][0] = ods + st2 / 2.0;
		ball[2][0] = 0;
		ball[3][0] = 0;
	}
}

void wallHit(double **ball)
{
	for (int i = 0; i < 16; i++)
	{
		if (ball[0][i] <= ods + ballRad)
			ball[2][i] = fabs(ball[2][i]);
		else if (ball[0][i] >= ods + st1 - ballRad)
			ball[2][i] = -fabs(ball[2][i]);

		if (ball[1][i] <= ods + ballRad)
			ball[3][i] = fabs(ball[3][i]);
		else if (ball[1][i] >= ods + st2 - ballRad)
			ball[3][i] = -fabs(ball[3][i]);
	}
}

double iloczynSkalarnyWek(double *x, double *y)
{

	double a = sqrt(pow(x[0], 2) + pow(x[1], 2));		//dlugosc wektora a
	double b = sqrt(pow(y[0], 2) + pow(y[1], 2));		//dlugosc wektora b

	double c = sqrt(pow(x[0] - y[0], 2) + pow(x[1] - y[1], 2));		//dlugosc dzialania wektorowego (-a) + b

	double cosa = ((a*a) + (b*b) - (c*c)) / (2.0 * (a*b));		//wartosc cos kata pomiedzy a i b
	double iloczyn = a*b*cosa;

	return iloczyn;
}

void collideBall(double **ball)
{
	double r1[2], r2[2], v1[2], v2[2], C;

	for (int i = 0; i < 15; i++)
	{
		for (int j = i + 1; j < 16; j++)
		{
			double a = sqrt(pow(ball[0][i] - ball[0][j], 2) + pow(ball[1][i] - ball[1][j], 2));		//odleglosc miedzy srodkami pilek

			if (a <= ballRad*2.02)
			{
				r1[0] = ball[0][i];		//tworzenie wektora wodzacego pierwszego punktu
				r1[1] = ball[1][i];

				r2[0] = ball[0][j];		//tworzenie wektora wodzacego drugiego punktu
				r2[1] = ball[1][j];

				v1[0] = ball[2][i];
				v1[1] = ball[3][i];

				v2[0] = ball[2][j];
				v2[1] = ball[3][j];

				double r1r2[2];		//tworze wektor ktory jest wynikiem dzialania r1 - r2
				r1r2[0] = r1[0] - r2[0];
				r1r2[1] = r1[1] - r2[1];

				double r2r1[2];		//tak samo tu
				r2r1[0] = r2[0] - r1[0];
				r2r1[1] = r2[1] - r1[1];

				double v1v2[2];		//teraz dla predkosci
				v1v2[0] = v1[0] - v2[0];
				v1v2[1] = v1[1] - v2[1];

				double r1r2_dlu = sqrt(pow(r1r2[0], 2) + pow(r1r2[1], 2));		//do obliczenia C potrzeba mi jeszcze dlugosci wektora r1 - r2

				C = iloczynSkalarnyWek(r1r2, v1v2) / pow(r1r2_dlu, 2);	//obliczam C
				double delV[2];		//tworze wektor zmiany predkosci
				delV[0] = C*r2r1[0];
				delV[1] = C*r2r1[1];

				ball[2][i] += delV[0];	//zmieniam wartosci predkosci pierwszej pilki
				ball[3][i] += delV[1];

				ball[2][j] -= delV[0];	//zmieniam wartosci predkosci drugiej pilki
				ball[3][j] -= delV[1];
			}
		}
	}
}