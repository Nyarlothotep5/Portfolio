#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<math.h>
#include"winbgi2.h"

void smok(double *Ps, double *Pk, int fold);
void fold(double *Ps, double *Pk);
void vecSpin90(double *P, double *K);

int main(void)
{
	graphics(1200, 1200);
	double Ps[2] = { 600,600 };
	double Pk[2] = { 300,900 };
	setcolor(1);
	smok(Ps, Pk, 20);
	setcolor(0);
	vecSpin90(Ps, Pk);
	smok(Ps, Pk, 20);
	setcolor(0.33);
	vecSpin90(Ps, Pk);
	smok(Ps, Pk, 20);
	setcolor(0.66);
	vecSpin90(Ps, Pk);
	smok(Ps, Pk, 20);

	wait();
}

void smok(double *Ps, double *Pk, int n)
{
	if (n == 1)
	{
		fold(Ps, Pk);
	}
	else
	{
		double bok = sqrt(pow(Pk[0] - Ps[0], 2) + pow(Pk[1] - Ps[1], 2));

		double x2, y2, x3, y3;
		x2 = (Ps[0] + Pk[0]) / 2.0;
		y2 = (Ps[1] + Pk[1]) / 2.0;

		double a[2] = { Pk[0] - x2, Pk[1] - y2 };

		double b[2] = { -a[1], a[0] };

		x3 = x2 + b[0];
		y3 = y2 + b[1];

		double P3[2] = { x3,y3 };

		smok(P3, Pk, n - 1);
		smok(P3, Ps, n - 1);
	}
}

void fold(double *Ps, double *Pk)
{
	double bok = sqrt(pow(Pk[0] - Ps[0], 2) + pow(Pk[1] - Ps[1], 2));
	double x2, y2, x3, y3;
	x2 = (Ps[0] + Pk[0]) / 2.0;
	y2 = (Ps[1] + Pk[1]) / 2.0;

	double a[2] = { Pk[0] - x2, Pk[1] - y2 };

	double b[2] = { -a[1], a[0]};

	x3 = x2 + b[0];
	y3 = y2 + b[1];

	line(Ps[0], Ps[1], x3, y3);
	line(x3, y3, Pk[0], Pk[1]);
}

void vecSpin90(double *P, double *K)
{
	double a[2] = { K[0] - P[0], K[1] - P[1] };

	K[0] = P[0] - a[1];
	K[1] = P[1] + a[0];
}