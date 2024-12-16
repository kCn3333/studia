#include <string>
#include <iostream>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sys/time.h>

using namespace std;

typedef vector<vector<double>> matrix;

vector<double> LU2(vector<double> a, vector<double> b,
				   vector<double> c, vector<double> d,
				   double p1, double q1, int n)
{

	double l[n + 1];
	double p[n + 1];
	double q[n + 1];
	double y[n + 1];
	double u[n + 1];
	vector<double> x;
	x.resize(n + 1);

	p[1] = p1;
	u[1] = b[1];
	l[2] = a[2] / u[1];
	q[2] = q1 / u[1];
	for (int i = 2; i < n - 1; i++)
	{ // L U
		u[i] = b[i] - l[i] * c[i - 1];
		l[i + 1] = a[i + 1] / u[i];
		q[i + 1] = ((-q[i]) * c[i - 1]) / u[i];
	}
	u[n - 1] = b[n - 1] - l[n - 1] * c[n - 2];
	q[n] = (a[n] - q[n - 1] * c[n - 2]) / u[n - 1];

	for (int i = 2; i < n - 1; i++)
		p[i] = (-l[i]) * p[i - 1];
	p[n - 1] = c[n - 1] - l[n - 1] * p[n - 2];

	u[n] = b[n];
	for (int i = 1; i < n; i++)
		u[n] -= p[i] * q[i + 1];

	// L y = d	U x = y
	y[1] = d[1];
	for (int i = 2; i < n; i++)
		y[i] = d[i] - l[i] * y[i - 1];
	y[n] = d[n];
	for (int i = 1; i < n; i++)
		y[n] -= y[i] * q[i + 1];

	x[n] = y[n] / u[n];
	x[n - 1] = (y[n - 1] - p[n - 1] * x[n]) / u[n - 1];
	for (int i = n - 2; i > 0; i--)
		x[i] = (y[i] - c[i] * x[i + 1] - p[i] * x[n]) / u[i];

	return x;
}

int main(int argc, char *argv[])
{
	string plik;
	int ile, n;
	matrix macierz;
	vector<double> a;
	vector<double> b;
	vector<double> c;
	vector<double> d;
	vector<double> rozwiazanie;

	cout << "\n\t rozwiazywanie ukladu z macierza"
		 << "\n\t    zblizona do trojdiagonalnej" << endl;
	cout << "\t     przy pomocy rozkladu LU\n"
		 << endl;

	if (argc != 2)
	{
		cout << "Podaj nazwe pliku wejsciowego" << endl;
		cin >> plik;
	}
	else
		plik = argv[1];

	ifstream odczyt(plik.c_str());
	odczyt >> ile;
	macierz.resize(ile);
	// wczytanie danych do macierzy rozszerzonej
	for (int i = 0; i < ile; i++)
	{
		macierz[i].resize(ile + 1);
		for (int j = 0; j < (ile + 1); j++)
			odczyt >> macierz[i][j];
	}

	cout << " Macierz rozszerzona ukladu:" << endl;

	for (unsigned int i = 0; i < macierz.size(); i++)
	{
		for (unsigned int j = 0; j < (macierz[i].size()); j++)
			cout << "\t" << macierz[i][j];
		cout << endl;
	}

	a.resize(ile + 1);
	b.resize(ile + 1);
	c.resize(ile + 1);
	d.resize(ile + 1);
	rozwiazanie.resize(ile + 1);

	n = ile;
	int k = 2; // wektor a [od 2 do n]
	for (int i = 1; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i - 1 == j)
			{
				a[k] = macierz[i][j];
				k++;
			}

	k = 1; // wektor b [od 1 do n]
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
			{
				b[k] = macierz[i][j];
				k++;
			}

	k = 1; // wektor c [od 1 do n-1]
	for (int i = 0; i < n - 1; i++)
		for (int j = 1; j < n; j++)
		{
			if (i + 1 == j)
			{
				c[k] = macierz[i][j];
				k++;
			}
			else
				c[k] = 0;
		}

	k = 1;
	for (int i = 0; i < n; i++)
	{
		d[k] = macierz[i][n];
		k++;
	}

	rozwiazanie = LU2(a, b, c, d, macierz[0][n - 1], macierz[n - 1][0], n);

	cout << endl
		 << " Rozwiazanie:" << endl;
	for (int i = 1; i < rozwiazanie.size(); i++)
	{
		cout.precision(10);
		cout << " x" << i << "= " << rozwiazanie[i] << endl;
	}
	odczyt.close();
}