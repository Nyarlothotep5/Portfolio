#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"winbgi2.h"

//to jest funckja rozwazana w programie, mozna dowolnie zmienic
double funkcja(double x); double funkcja(double x)
{
	return x*x*sin(x);
}

//te dwie to zwykle funkcje do liczenia troche zaokraglonych ekstremow w danym przedziale (a,b)
double minimumF(double(*f)(double), double a, double b);
double maksimumF(double(*f)(double), double a, double b);

//funkcja rysujaca wykres podanej funkcji
void drawF(double(*f)(double), double skalaOX, double skalaOY, double a, double b, double osOX, double osOY);

//ta funkcja rysuje prostokat pokazujacy przedzial dla ktorego stosuje sie metode Monte Carlo
double integralRect(double a, double b, double skalaOX, double skalaOY, double osOX, double osOY, double maxF, double minF);

//ta funkcja podaje juz liczbe punktow dla ktorych oblicza sie calke 
double MonteCarlo(double(*f)(double), double a, double b, double skalaOX, double skalaOY, double minF, double maxF, double osOX, double osOY, int prec);

const double prec = 1000000;		//precyzja liczenia, czyli calkowita liczba punktow

int main(void)
{
	srand(time(NULL));

	//to jest nasz przedzial w ktorym chcemy liczyc calke
	//dodatkowo zmienna na pole prostokata oraz liczba pkt z ktorych liczy sie calke
	//czyli pkt = (punkty nad osia OX ale pod wykresem f(x)) - (punkty pod osia OX ale nad wykresem f(x))
	double a, b, P, pkt;

	printf("Prosze podac przedzial (a,b), w ktorym liczona bedzie calka oznaczona dla funkcji: \n");
	scanf("%lf %lf", &a, &b);

	//zeby dobrze narysowac funkcje w oknie chce znac max i min funkcji w tym przedziale
	double maksF = maksimumF(funkcja, a, b);
	double minF = minimumF(funkcja, a, b);

	//osie w oknie graficznym zaleza od skalowania - chcemy zeby (a,b) zajelo prawie cala os X, a os OY by³a w dobrym miejscu 
	//dodatkowo te skale przydadza sie do narysowania OX i OY w dobrych miejscach w oknie
	double skalaOY = 500 / fabs(maksF - minF);
	double skalaOX = 1000 / fabs(b - a);

	//te dwie zmienne pomagaja rysowac linie i funkcje
	double osOX = 300 + skalaOY*(maksF + minF) / 2.0;
	double osOY = 550 - skalaOX*(b + a) / 2.0;

	printf("\nMaksimum oraz minimum funkcji w przedziale:\n");
	printf("%lf %lf", maksF, minF);
	graphics(1100, 600);
	line(osOY, 0, osOY, 600);
	line(0, osOX , 1100, osOX);

	//rysujemy sama funkcje plus ladne osie OX i OY
	drawF(funkcja, skalaOX, skalaOY, a, b, osOX, osOY);

	//tutaj rysujemy prostokat ktory okreslony jest przez przedzialy (a,b) oraz (minF, maksF)
	//przy okazji obliczamy P, czyli jego pole
	P = integralRect(a, b, skalaOX, skalaOY, osOX, osOY, maksF, minF);

	//tu rysujemy odpowiednie punkty na wykresie oraz liczymy sume punktow ktora potrzebna jest nam do calki
	pkt = MonteCarlo(funkcja, a, b, skalaOX, skalaOY, minF, maksF, osOX, osOY, prec);

	//wynikiem jest pole prostokata pomnozone przez (pkt obliczone dla calki / calkowita liczba pkt)
	double wyn = P * (pkt / prec);

	printf("\n\nWynikiem calki jest:\n%lf", wyn);
	wait();
}

void drawF(double(*f)(double), double skalaOX, double skalaOY, double a, double b, double osOX, double osOY)
{
	//tu kosmetyczne rysowanie - dodaje opisy do osi i oznaczam punkt srodkowy
	outtextxy(osOY + 5, osOX - 15, "O");
	outtextxy(1075, osOX + 10, "x");
	outtextxy(osOY - 15, 10, "y");

	//x to zmienna odpowiadajaca za rysowanie okregow w odpowiednich wspolrzednych x w oknie grafiki
	double x = 0;

	//poniewaz rysuje wykres z malym zapasem z lewej i prawej strony to dodaje zmienne odpowiadajace tym wartosciom
	double a1 = a - 50 / skalaOX;
	double b1 = b + 50 / skalaOX;

	//tu obliczam krok wykonywany przez x jakby na prawdziwej osi OX
	//dziele przez 110000 gdyz tyle krokow wykona zmienna x w trakcie petli
	double krok = (b1 - a1) / 110000.0;

	//tu kolorek dla funkcji i rysowanie :3
	setcolor(0);
	while (x < 1100)
	{
		//rysowalem okregami ale mozna tez liniami pomiedzy dwoma punktami
		circle(x, osOX - f(a1)* skalaOY, 1);

		//dodaje kroki obu zmiennych
		x += 0.01;
		a1 += krok;
	}
	//na koniec na wszelki wypadek wracam do koloru bialego
	setgray(1);
}

double integralRect(double a, double b, double skalaOX, double skalaOY, double osOX, double osOY, double maxF, double minF)
{
	//lewy i górny bok
	line(osOY + a*skalaOX, osOX - maxF*skalaOY, osOY + b*skalaOX, osOX - maxF*skalaOY);
	line(osOY + a*skalaOX, osOX - maxF*skalaOY, osOY + a*skalaOX, osOX - minF*skalaOY);

	//prawy i dolny bok
	line(osOY + b*skalaOX, osOX - maxF*skalaOY, osOY + b*skalaOX, osOX - minF*skalaOY);
	line(osOY + a*skalaOX, osOX - minF*skalaOY, osOY + b*skalaOX, osOX - minF*skalaOY);
	
	//to mowi samo za siebie xd
	double pole = (b - a) * (maxF - minF);

	return pole;
}

double MonteCarlo(double (*f)(double), double a, double b, double skalaOX, double skalaOY, double minF, double maxF, double osOX, double osOY, int prec)
{
	//zmienne na (x,y) punktow oraz zmienna na sume punktow na ktorych nam zalezy
	double x, y, pkt = 0;

	//l i p to odpowiednio lewa i prawa granica przedzialu ale wyrazona wspolrzednymi na osi X w oknie grafiki
	int l = osOY + a*skalaOX;
	int p = osOY + b*skalaOX;

	//tak samo tu ale na osi Y
	int d = osOX - minF*skalaOY;
	int g = osOX - maxF*skalaOY;

	//tu tworze znane zmienne L do losowania w podanym zakresie liczbowym
	int L1 = p - l + 1;
	int L2 = g - d + 1;

	for (int i = 0; i < prec; i++)
	{
		//losuje wspolrzedne jednego punktu 
		x = rand() % L1 + l;
		y = rand() % L2 + g;

		//yf jest wartoscia funkcji dla wylosowanego x tyle ze skaluje do normalnego ukladu wsplolrzednych 
		double yf = f((-osOY + x)/skalaOX);

		//jesli punkt lezy pomiedzy osia OX, a funkcja to w zaleznosci od tego czy lezy pod OX czy nad OX dodaje lub odejmuje sume pkt
		//czyli mowiac calkowo - jesli funkcja dla danego x jesy ujemna to pkt-- a jesli dodatnia do pkt++
		//no i do tego zmieniam kolor w zaleznosci od tego gdzie lezy punkt zeby sie wyroznial
		if (y <= osOX - yf*skalaOY && y > osOX)
		{
			setcolor(1.0);
			point(x, y);
			pkt--;
		}
		else if (y >= osOX - yf*skalaOY && y < osOX)
		{
			setcolor(0.5);
			point(x, y);
			pkt++;
		}

		setgray(1);
	}

	return pkt;
}

double maksimumF(double(*f)(double), double a, double b)
{
	double x = a;
	double maks = f(a);

	while (x <= b)
	{
		if (f(x) > maks)
			maks = f(x);

		x += 0.0001;
	}

	return maks;
}

double minimumF(double(*f)(double), double a, double b)
{
	double x = a;
	double min = f(a);

	while (x <= b)
	{
		if (f(x) < min)
			min = f(x);

		x += 0.0001;
	}

	return min;
}