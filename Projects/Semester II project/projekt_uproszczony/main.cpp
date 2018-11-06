//this program calculates the time step needed to get specified accuracy of calculations
//in this example we consider a ball that 'splashes' into water and moves according to laws of physics
//calculations are done using rk4 method for vectors

#include<iostream>
#include<math.h>
#include<fstream>
#include"rk4.h"
#include"winbgi2.h"

using namespace std;

//needed constants
const double pi = 4 * atan(1.0);
const double g = 9.81;
double waterDens = 1000;
double ballDens = waterDens / 2.0;

//ball geometry variables
double ballRad;
double ballM;

//vectors needed for vrk4 method
double y[2];
double Y[2];
double R[2];

//maximum calculations error
double eps = 0.0001;


double subV(double z);
void RHS(double t, double *y, double *r);

int main()
{
	cout << "Please enter ball's radius: ";
	cin >> ballRad;
	ballM = (4.0 * pi*ballRad*ballRad*ballRad / 3.0) * ballDens;

	double z0, v0;
	cout << "Please enter start conditions: z0 and v0: ";
	cin >> z0 >> v0;

	Y[0] = z0;
	Y[1] = v0;
	y[0] = Y[0];
	y[1] = Y[1];

	R[1] = (1 / ballM)*(subV(Y[0])*waterDens - ballM * g);
	R[0] = Y[1];

	ofstream wyn;
	wyn.open("results.txt");

	
	wyn << "Ball's radius: " << ballRad << "m"<< endl;
	wyn << "Start condition z0: " << z0 << "m" << endl;
	wyn << "Start condition v0: " << v0 << "m/s" << endl;
	wyn << "\nTime:\tz(t):\tv_z(t):\tE(t)\tEnergy error:" << endl;

	//energy variables
	double Ep, Eph, Ek, E;
	double Epocz = ballM * g*Y[0] + (1.0 / 2.0)*ballM*Y[1] * Y[1];
	double Er;

	graphics(400, 400);

	
	double rH = Y[0];
	double hMax = Y[0];

	double t = 0.0;
	double h = 2.0;

	//maximum number of 'splashes' and a variable for current number of 'splashes'
	int maxwyn = 3;
	int wynu = 0;

	do {
		h /= 2.0;
		t = 0.0;
		wynu = 0;

		Y[0] = z0;
		Y[1] = v0;
		y[0] = Y[0];
		y[1] = Y[1];

		R[1] = (1.0 / ballM)*(subV(Y[0])*waterDens - ballM * g);
		R[0] = Y[1];

		while (t <= 20.0 && animate(240))
		{
			//water and ball visualization
			clear();
			setcolor(0.0);
			line(0, 200, 400, 200);
			setcolor(1.0);
			pieslice(200, 200 - 20 * Y[0], 0, 360, 20 * ballRad);	//20-times scaling for better visual presentation

			//vrk4 and corresponding matrices changes
			vrk4(t, Y, h, 2, RHS, y);

			if (y[0] >= 0.0 && Y[0] < 0.0)
				wynu += 1;

			Y[0] = y[0];
			Y[1] = y[1];

			if (wynu == maxwyn && fabs(y[0] - hMax) < rH)
			{
				rH = fabs(y[0] - hMax);
			}

			//calculating and summation of energy components
			Ep = ballM * g * y[0];
			Ek = ballM * y[1] * y[1] / 2.0;
			if (y[0] <= ballRad && y[0] > 0.0)
				Eph = waterDens * g *subV(y[0]) * abs((y[0] - ballRad) / 2.0);
			else if (y[0] <= 0 && y[0] > -ballRad)
				Eph = waterDens * g *subV(y[0]) * (abs(y[0]) + ballRad) / 2.0;
			else if (y[0] <= -ballRad)
				Eph = waterDens * g *subV(y[0]) * abs((y[0]));
			else
				Eph = 0.0;

			E = Ep + Ek + Eph;
			Er = fabs(E - Epocz);

			wyn << t << "\t" << Y[0] << "\t" << Y[1] << "\t" << E << "\t" << Er << endl;

			t += h;
		}
		
	} while (rH > hMax*eps);


	cout << "\nTime step needed for given calculations accuracy:\n" << h << "s" << endl;
	cout << "\nCalculations complete!" << endl;
	cout << "Enter any sign to exit...\n";
	
	getchar();
	getchar();

}

double subV(double z)
{
	double h;

	if (z >= ballRad)
		return 0.0;

	if (z == 0.0)
	{
		return (1.0 / 2.0)*(4.0 / 3.0 * pi*ballRad*ballRad*ballRad);
	}
	else if (z > 0.0)
	{
		h = ballRad - z;
		return (pi*h*h / 3.0)*(3.0 * ballRad - h);
	}
	else if (z < 0.0 && z >= (-ballRad))
	{
		h = ballRad + z;
		return (4.0 / 3.0 * pi*ballRad*ballRad*ballRad) - (pi*h*h / 3.0)*(3.0 * ballRad - h);
	}

	return (4.0 / 3.0 * pi*ballRad*ballRad*ballRad);
}

void RHS(double t, double *y, double *r)
{
	r[0] = y[1];
	r[1] = (1.0 / ballM)*(subV(y[0])*waterDens*g - ballM * g);
}

