// Interpolacja naturalnym splajnem kubicznym

#include <string>
#include <iostream>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sys/time.h>

#define N 512
using namespace std;

typedef vector<vector<double>> matrix;

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

int main(int argc, char *argv[])
{
	string plik;
	matrix macierz;
	vector<double> a;
	vector<double> b;
	vector<double> c;
	vector<double> d;
	vector<double> pochodne;

	double X[N + 1];
	double Y[N + 1];

	cout << "\n\t Interpolacja naturalnym splajnem kubicznym: " << endl;

	if (argc != 2)
	{
		cout << "Podaj nazwe pliku wejsciowego" << endl;
		cin >> plik;
	}
	else
		plik = argv[1];

	ifstream odczyt(plik.c_str());
	// wczytanie danych do macierzy rozszerzonej
	for (int i = 1; i <= N; i++)
	{
		odczyt >> X[i];
		odczyt >> Y[i];
	}

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
		 << " Rozwiazanie:" << endl;
	for (double i = -1.5; i < 1.5; i += 0.01)
		cout << i << " " << spline(i, pochodne, X, Y) << endl;
	odczyt.close();
}