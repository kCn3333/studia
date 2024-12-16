// interpolacja funkcjami wymiernymi, algorytm Floatera i Hormanna

#include <stdio.h>
#include <math.h>
#include <iostream>

#define NMAX 100
#define krok 0.01

using namespace std;

int N, D = 3;
double X[NMAX], Y[NMAX];
double W[NMAX];
double X1[6], Y1[6];
double y, x;

void wk(int N, double *X, int D)
{
  double iloczyn = 1.0;
  double suma = 1.0;
  int k = 1;
  while (k <= N)
  {
    W[k] = 0.0;
    for (int i = 1; i <= N - D; i++)
    {
      suma = 1.0;
      iloczyn = 1.0;
      if (i >= k - D && i <= k)
      {
        for (int j = i; j <= i + D; j++)
          if (j != k)
            iloczyn *= 1.0 / (X[k] - X[j]);
        for (int l = i; l > 0; l--)
          suma *= (-1.0);
        W[k] += suma * iloczyn;
      }
    }
    k++;
  }
}

double RX(int N, double *X, double *Y, double x)
{
  double suma1 = 0.0;
  double suma2 = 0.0;
  for (int i = 1; i <= N; i++)
  {
    suma1 += W[i] / (x - X[i]) * Y[i];
    suma2 += W[i] / (x - X[i]);
  }
  return y = suma1 / suma2;
}

int main()
{
  int n = 1;

  for (double k = -1.0; k <= 1.0; n++)
  {
    X[n] = k;
    Y[n] = 1.0 / (1.0 + 5 * k * k);
    k += 1.0 / 32.0;
  }
  n = n - 1;

  N = n;
  wk(N, X, D);

  cout << "\n interpolacja funkcjami wymiernymi"
       << "\nalgorytm Floatera i Hormanna d=" << D << " (krok=" << krok << ") \n"
       << endl;
  cout << "\tX\t    Y";
  for (x = X[1] + krok; x < X[N]; x += krok)
  {
    for (int i = 2; i <= N; i++)
      if (x == X[i])
      {
        y = Y[i];
        goto e11;
      }
    y = RX(N, X, Y, x);
  e11:
    cout << fixed << "\n " << x << " " << y;
  }
  cout << endl
       << endl;
}
