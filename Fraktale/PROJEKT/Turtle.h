#define _CRT_SECURE_NO_WARNINGS

//rysuje linie okreslona wektorem zolwia [x, y, odl, kat]
void draw(double *turt);
//skreca w prawo o podana liczbe stopni
void turnR(double *turt, double kat);
//skreca w lewo o podana liczbe stopni
void turnL(double *turt, double kat);
//cofa sie do poprzedniej pozycji
void turnB(double *turt);