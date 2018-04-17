//	GRAFIKA ZOLWIA
//	funkcje sluzace do rysowania w oknie grafiki metoda grafiki zolwiowej
//	za zolwia sluzy tablica jednowymiarowa z 4 miejscami 
//	podstawowymi funkcjami sa: ruch do przodu, obrot w prawo, obrot w lewo oraz powrot do poprzedniej pozycji
//	przyjete zalozenie: os OY w oknie grafiki rozciaga sie do gory (aby uzytkownikowi latwiej bylo sie odnalezc)

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<math.h>
#include"winbgi2.h"
#include"Turtle.h"

const double pi = 4 * atan(1.0);

//rysowanie do przodu
//zolw rysuje linie prosta bedaca jego trasa
//po narysowaniu linii zolw zostaje w miejscu docelowym
void draw(double *turt)
{	
	double a = turt[3] * pi / 180.0;		//zmiana kata ze stopni na radiany

	line(turt[0], turt[1], turt[0] + (turt[2] * cos(a)), turt[1] - (turt[2] * sin(a)));		//rysowanie linii na zadanym odcinku

	turt[0] += turt[2] * cos(a);		//zmiana pozycji zolwia
	turt[1] -= turt[2] * sin(a);
}

//obrot w prawo o zadana liczbe stopni
void turnR(double *turt, double kat)
{
	turt[3] -= kat;		//zmiana orientacji zolwia wzgledem osi OX
}

//obrot w lewo o zadana liczbe stopni
void turnL(double *turt, double kat)
{
	turt[3] += kat;		//zmiana orientacji zolwia wzgledem osi OX
}

//powrot zolwia na pozycje przed narysowaniem linii
void turnB(double *turt)
{
	double a = turt[3] * pi / 180.0;		//zmiana kata ze stopni na radiany

	turt[0] -= turt[2] * cos(a);		//zmiana pozycji zolwia
	turt[1] += turt[2] * sin(a);
}