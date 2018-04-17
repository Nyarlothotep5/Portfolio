#define _CRT_SECURE_NO_WARNINGS

//funkcja glowna, rysujaca 
//zawiera funkcje transformujace w postaci tabeli 
void BarnsleyFern();
//funkcja przeprowadzajaca transformacje punktu
//*f - tabela z funkcjami transformujacymi, *pos - tabela z obecna pozycja punktu
void transform(double *f, double *pos);
