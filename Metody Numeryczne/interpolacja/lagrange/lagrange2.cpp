#include <stdio.h>
#include <math.h>
#include <iostream>

#define krok 0.01

using namespace std;

double XL[70];
double X[70], Y[70];
double X1[6], Y1[6];

double xx, yy;
int iv, n;

double Interpol_Lagrange(double xx)
{
  double yy;
  int i, j, k;

  for (i = 0; i < n + 1; i++)
    XL[i] = 1.0;
  yy = 0.0;
  for (k = 1; k < n + 1; k++)
  {
    for (j = 1; j < n + 1; j++)
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

int main()
{
  n = 1;

  for (double k = -1.0; k <= 1.0; n++)
  {
    X[n] = k;
    Y[n] = 1.0 / (1.0 + 5 * k * k);
    k += 1.0 / 32.0;
  }
  n = n - 1;

  cout << "\n " << n << " interpolacja wielomianem Lagrange'a (krok=" << krok << ") \n"
       << endl;
  cout << "\tX\t    Y";
  for (xx = X[1] + krok; xx <= X[n]; xx += krok)
  {
    yy = Interpol_Lagrange(xx);
    cout << fixed << "\n " << xx << " " << yy;
  }
  cout << endl
       << endl;
}
