#define _CRT_SECURE_NO_WARNINGS

void ComplexDivergence();
//zbieznosc ciagu na liczbach zespolonych z[2] i c[2] o dokladnosci dokl oraz wersji fraktala ver
//1 - zbior Mandelbrota
//2 - zbior Julii
//3 - Plonacy statek
//4 - Armada z Plonacego Statku
double divergence(double *z, double *c, int dokl, int ver);
//fraktal newtona
//troche nieudany, wiec nie jest uwzgledniony w ostatecznym projekcie
double divergenceNewton(double *z, double **root, int dokl, double eps, double a);
//wyznacza kolory do narysowania BuddhaBrot
void BuddhaBrot(double *z, double *c, int **licz, int dokl);
//n-ta potega liczby zespolonej, zwraca z[2]
void powIm(double *z, int n);
//kwadrat liczby zespolonej, zwraca z[2]
void pow2Im(double *z);
//dodawanie liczb zespolonych (z + c), zwraca z[2]
void addIm(double *z, double *c);
//iteracja plonacego statku
void burningIter(double *z, double *c);
//zwraca wartosc argumentu glownego liczby zespolonej w stopniach
double argZ(double *z);
//dzielenie liczb zespolonych, zwraca wyn[2]
void divIm(double *z, double *c, double *wyn);