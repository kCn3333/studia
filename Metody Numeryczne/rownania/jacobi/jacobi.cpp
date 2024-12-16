#include <string>
#include <iostream>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sys/time.h>

#define DLUGOSC 100
#define BLAD 0.0000001

using namespace std;

void pokaz(double macierzL[DLUGOSC][DLUGOSC])
{
    for (int i = 0; i < DLUGOSC; i++)
    {
        for (int j = 0; j < DLUGOSC; j++)
        {
            cout << macierzL[i][j] << " ";
        }
        cout << endl;
    }
}

double norma(double z[DLUGOSC])
{
    double tmp = 0;

    for (int i = 0; i < DLUGOSC; i++)
    {
        tmp = +(z[i] * z[i]);
    }
    return sqrt(tmp);
}

int JacobiMethod(double A[DLUGOSC][DLUGOSC], double b[DLUGOSC], double x1[DLUGOSC])
{
    double tmp;
    double x[DLUGOSC];
    double sumx, sumx1;
    int k = 0;
    int n = DLUGOSC;
    for (int i = 0; i < n; i++)
    {
        x1[i] = b[i] / A[i][i];
    }

    do
    {
        for (int i = 0; i < n; i++)
        {
            x[i] = x1[i];
        }

        for (int i = 0; i < n; i++)
        {
            tmp = 0;
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    tmp += A[i][j] * x[j];
                }
            }
            x1[i] = (1.0 / A[i][i]) * (b[i] - tmp);
        }

        sumx = 0;
        sumx1 = 0;
        for (int i = 0; i < n; i++)
        {
            sumx += x[i];
            sumx1 += x1[i];
        }

        ++k;
    } while (abs(sumx - sumx1) > BLAD);

    return k;
}

int main(int argc, char *argv[])
{
    double A[DLUGOSC][DLUGOSC];
    double x[DLUGOSC];
    string plik;
    int k;

    double b[DLUGOSC];
    for (int i = 0; i < DLUGOSC; i++)
        b[i] = 1;

    if (argc != 2)
    {
        cout << "Podaj nazwe pliku wejsciowego" << endl;
        cin >> plik;
    }
    else
    {
        plik = argv[1];
    }

    ifstream odczyt(plik.c_str());

    // wczytanie danych do macierzy
    for (int i = 0; i < DLUGOSC; i++)
    {
        for (int j = 0; j < DLUGOSC; j++)
        {
            odczyt >> A[i][j];
        }
    }

    cout << "\n [ metoda Jacobiego ]" << endl;
    cout << "\n rozwiazanie ukladu Ax=b, macierz A z pliku " << argv[1] << " ..." << endl
         << endl;

    timeval tim;
    gettimeofday(&tim, NULL);
    double t1 = tim.tv_sec + (tim.tv_usec / 1000000.0);
    k = JacobiMethod(A, b, x);
    gettimeofday(&tim, NULL);
    double t2 = tim.tv_sec + (tim.tv_usec / 1000000.0);

    cout << " zakonczono po " << k << " iteracjach" << endl;
    cout << " w czasie: " << fixed << t2 - t1 << " sekund" << endl
         << endl;

    cout << " wspolrzedne wektora x: \n";

    for (int j = 0; j < DLUGOSC; j++)
        cout << x[j] << "  ";
    cout << endl
         << endl;

    return 0;
}
