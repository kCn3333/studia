// Szukanie minimum - metoda Brenta

#include <string>
#include <iostream>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sys/time.h>
#include <time.h>

#define N 128
#define shft(a, b, c, d) \
	(a) = (b);           \
	(b) = (c);           \
	(c) = (d);
#define SIGN(a, b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
#define SWAP(a, b)  \
	{               \
		temp = (a); \
		(a) = (b);  \
		(b) = temp; \
	}

using namespace std;
typedef vector<vector<double>> matrix;

const double CGOLD = 0.3819660; // zloty podzial
double X[N + 1];
double Y[N + 1];
vector<double> pochodne;

const int nn = 3;
double B[nn];

double f(double x)
{
	double yy = 0.0, temp;
	for (int j = 0; j < nn; j++)
	{
		temp = 1.0;
		for (int k = nn - j - 1; k > 0; k--)
			temp *= x;
		temp *= B[j];
		yy += temp;
	}
	return yy;
}

vector<double> LU(vector<double> a, vector<double> b, vector<double> c, vector<double> d, int n)
{
	double l = 0;
	double y[n + 1];
	double u[n + 1];
	vector<double> x;
	x.resize(n + 1);

	u[1] = b[1];
	y[1] = d[1];
	for (int i = 2; i <= n; i++)
	{
		if (u[i - 1] != 0)
			l = a[i] / u[i - 1];
		else
		{
			cout << "\n #blad obliczen u[" << i - 1 << "] =0";
			return x;
		}
		u[i] = b[i] - l * c[i - 1];
		y[i] = d[i] - l * y[i - 1];
	}
	if (u[n] != 0)
		x[n] = y[n] / u[n];
	else
	{
		cout << "\n #blad obliczen u[" << n << "] =0";
		return x;
	}
	for (int i = n - 1; i >= 1; i--)
	{
		if (u[i] != 0)
		{
			x[i] = ((y[i] - c[i] * x[i + 1]) / u[i]);
		}
		else
		{
			cout << "\n #blad obliczen u[" << i << "] =0";
			return x;
		}
	}
	return x;
}

double spline(double x, vector<double> pochodne, double X[N + 1], double Y[N + 1])
{
	double A, B, C, D;
	for (int i = 1; i <= N; i++)
	{
		if (x == X[i])
			return Y[i];
		if (x > X[i] && x < X[i + 1])
		{
			A = (X[i + 1] - x) / (X[i + 1] - X[i]);
			B = (x - X[i]) / (X[i + 1] - X[i]);
			C = 1 / 6 * (A * A * A - A) / (X[i + 1] - X[i]) * (X[i + 1] - X[i]);
			D = 1 / 6 * (B * B * B - B) / (X[i + 1] - X[i]) * (X[i + 1] - X[i]);
			return A * Y[i] + B * Y[i + 1] + C * pochodne[i] + D * pochodne[i + 1];
		}
		if (x > X[N])
		{
			cout << " blad";
			return 0;
		}
	}
}

double brent(double ax, double bx, double cx)
{
	double xmin, fmin;
	const double tol = 3.0e-8;
	const int ITMAX = 100;
	const double EPS = 1.0e-8;

	double a, b, d = 0.0, etemp, fu, fv, fw, fx;
	double p, q, r, tol1, tol2, u, v, w, x, xm;
	double e = 0.0;

	a = ax;
	b = cx;
	x = w = v = bx;
	fw = fv = fx = f(x); // spline(x,pochodne,X,Y);

	for (int i = 0; i < ITMAX; i++)
	{
		xm = 0.5 * (a + b);
		tol2 = 2.0 * (tol1 = tol * abs(x) * EPS);
		if (abs(x - xm) <= (tol2 - 0.5 * (b - a)))
		{
			fmin = fx;
			cout.precision(8);
			cout << fixed << " znaleziono minimum po " << i + 1 << " iteracjach,\t[ xmin=" << x << " ] f(xmin)=" << fx << " " << endl;
			return xmin = x;
		}
		if (abs(e) > tol1)
		{
			r = (x - w) * (fx - fv);
			q = (x - v) * (fx - fw);
			p = (x - v) * q - (x - w) * r;
			q = 2.0 * (q - r);
			if (q > 0.0)
				p = -p;
			q = abs(q);
			etemp = e;
			e = d;
			if (abs(p) >= abs(0.5 * q * etemp) || p <= q * (a - x) || p >= q * (b - x))
				d = CGOLD * (e = (x >= xm ? a - x : b - x));
			else
			{
				d = p / q;
				u = x + d;
				if (u - a < tol2 || b - u < tol2)
					d = SIGN(tol1, xm - x);
			}
		}
		else
			d = CGOLD * (e = (x >= xm ? a - x : b - x));
		u = (abs(d) >= tol1 ? x + d : x + SIGN(tol1, d));
		fu = f(u); // spline(u,pochodne,X,Y);
		if (fu <= fx)
		{
			if (u >= x)
				a = x;
			else
				b = x;
			shft(v, w, x, u);
			shft(fv, fw, fx, fu);
		}
		else
		{
			if (u < x)
				a = u;
			else
				b = u;
			if (fu <= fw || w == x)
			{
				v = w;
				w = u;
				fv = fw;
				fw = fu;
			}
			else if (fu <= fv || v == x || v == w)
			{
				v = u;
				fv = fu;
			}
		}
	}
	cout << " nie znaleziono po " << ITMAX << " iteracjach..." << endl;
}

int main(int argc, char *argv[])
{
	string plik;
	matrix macierz;
	vector<double> a;
	vector<double> b;
	vector<double> c;
	vector<double> d;
	double losowa1, losowa2, losowa3, temp;
	srand(time(NULL));

	if (argc != 2)
	{
		cout << "Podaj nazwe pliku wejsciowego" << endl;
		cin >> plik;
	}
	else
		plik = argv[1];

	ifstream odczyt(plik.c_str());

	for (int i = 1; i <= N; i++)
	{
		odczyt >> X[i];
		odczyt >> Y[i];
	}
	odczyt.close();

	B[0] = 0.1049470324;
	B[1] = 0.06461270521;
	B[2] = -0.03369484597;

	double h = X[512] - X[511];
	double hh = 6 / (h * h);

	a.resize(N + 1);
	b.resize(N + 1);
	c.resize(N + 1);
	d.resize(N + 1);

	for (int j = 0; j <= N; j++)
		a[j] = 1;
	for (int j = 0; j <= N; j++)
		b[j] = 4;
	for (int j = 0; j <= N; j++)
		c[j] = 1;
	for (int i = 0; i <= N; i++)
		d[i] = hh * (Y[i] - 2 * Y[i + 1] + Y[i + 2]);

	pochodne.resize(N + 1);
	pochodne = LU(a, b, c, d, N);

	cout << endl
		 << " Szukanie minimum - metoda Brenta:"
		 << endl
		 << " ---------------------------------" << endl;

	bool var = 1;
	for (int i = 0; i < 20; i++)
	{
		do
		{
			losowa1 = rand() / (RAND_MAX + 1.0) * 3.0 - 1.5;
			losowa2 = rand() / (RAND_MAX + 1.0) * 3.0 - 1.5;
			if (losowa2 < losowa1)
			{
				temp = losowa1;
				losowa1 = losowa2;
				losowa2 = temp;
			}
			losowa3 = losowa1 + ((losowa2 - losowa1) * CGOLD);
			if ((f(losowa1) > f(losowa3)))	   // spline(losowa1,pochodne,X,Y) > spline(losowa3,pochodne,X,Y) ) )
				if ((f(losowa2) > f(losowa3))) // spline(losowa2,pochodne,X,Y) > spline(losowa3,pochodne,X,Y) ))
					var = 0;
		} while (var);

		cout << " a=" << losowa1 << " b=" << losowa3 << " c=" << losowa2 << endl
			 << "f(a)=" << f(losowa1) << " f(b)=" << f(losowa3) << " f(c)=" << f(losowa2) << endl;
		//<<" f(a)="<<spline(losowa1,pochodne,X,Y)<<" f(b)="<<spline(losowa3,pochodne,X,Y)<<" f(c)="<<spline(losowa2,pochodne,X,Y)<< endl;
		brent(losowa1, losowa3, losowa2);
		cout << endl;
		var = 1;
	}
}