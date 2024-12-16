#include <stdio.h>
#include <math.h>
#include <iostream>

#define krok 0.001
#define N 8

using namespace std;

int iv = N, n = N;
double XL[N + 1];
double X[N + 1], Y[N + 1];
double C[N + 1];
double xx, yy;

double Interpol_Lagrange(double xx)
{
  double yy;
  int j, k;

  for (j = 1; j <= n; j++)
    XL[j] = 1.0;
  yy = 0.0;
  for (k = 1; k <= n; k++)
  {
    for (j = 1; j <= n; j++)
    {
      if (j == k)
        goto e1;
      XL[k] = XL[k] * (xx - X[j]) / (X[k] - X[j]);
    e1:;
    }
    yy = yy + XL[k] * Y[k];
  }
  return yy;
}

void wsp() // ilorazy roznicowe
{
  for (int i = 1; i <= N; i++)
    C[i] = Y[i];
  for (int j = 2; j <= N; j++)
    for (int i = N; i >= j; i--)
      C[i] = (C[i] - C[i - 1]) / (X[i] - X[i - j]);
}

void wspolczynniki()
{
  double t;
  for (int i = 1; i <= N; i++)
  {
    t = 1;
    for (int j = 1; j <= N; j++)
    {
      if (i != j)
        t = t * (X[i] - X[j]);
    }
    C[i] = Y[i] / t;
  }
}

double test(double x)
{
  double t1 = 0;
  double t2 = 1;
  for (int i = 1; i <= N; i++)
  {
    t2 = 1;
    for (int j = 1; j <= N; j++)
    {
      if (i != j)
        t2 = t2 * (x - X[j]);
    }
    t1 = t1 + C[i] * t2;
  }
  return t1;
}

int main()
{
  X[1] = 0.062500;
  Y[1] = 0.687959;
  X[2] = 0.187500;
  Y[2] = 0.073443;
  X[3] = 0.312500;
  Y[3] = -0.517558;
  X[4] = 0.437500;
  Y[4] = -1.077264;
  X[5] = 0.562500;
  Y[5] = -1.600455;
  X[6] = 0.687500;
  Y[6] = -2.080815;
  X[7] = 0.812500;
  Y[7] = -2.507266;
  X[8] = 0.935700;
  Y[8] = -2.860307;

  wspolczynniki();

  cout << "\n interpolacja wielomianem Lagrange'a (krok=" << krok << ") \n"
       << endl;
  cout << "\tX\t    Y";
  for (xx = X[1] + krok; xx < X[5]; xx += krok)
  {
    yy = Interpol_Lagrange(xx);
    cout << "\n   " << fixed << xx << "\t" << yy;
  }

  cout << "\n\n wyznaczony wielomian interpolacyjny : \n"
       << endl;
  cout << "W(x) = \t";
  for (int i = 1; i <= n; i++)
  {
    cout << C[i];
    for (int j = 1; j <= N; j++)
      if (i != j)
        cout << " (x-x" << j << ")";
    if (C[i + 1] > 0 && i < n)
      cout << endl
           << "\t+";
    else
      cout << endl
           << "\t";
  }
  cout << "\n\ttest: x=0.5  " << test(0.201) << endl;
}
