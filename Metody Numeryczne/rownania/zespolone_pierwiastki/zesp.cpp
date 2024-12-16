#include <cmath>
#include <iostream>
#include <complex>

using namespace std;

double blad = 0.0000000000001;

double MAX(double a, double b)
{
  if (a >= b)
    return a;
  else
    return b;
}

void laguer(complex<double> a[], complex<double> &x, int &its, int n)
{
  int MR = 8, MT = 10, MAXIT = MT * MR;
  double frac[9] = {0.0, 0.5, 0.25, 0.75, 0.13, 0.38, 0.62, 0.88, 1.0};

  complex<double> dx, x1, b, d, f, g, h, sq, gp, gm, g2;
  int m = n - 1;
  for (int iter = 1; iter <= MAXIT; iter++)
  {
    its = iter;
    b = a[m];
    double err = abs(b);
    d = f = complex<double>(0.0, 0.0);
    double abx = abs(x);
    for (int j = m - 1; j >= 0; j--)
    {
      f = x * f + d;
      d = x * d + b;
      b = x * b + a[j];
      err = abs(b) + abx * err;
    }
    err *= blad;
    if (abs(b) <= err)
      return;
    g = d / b;
    g2 = g * g;
    h = g2 - 2.0 * f / b;
    sq = sqrt(double(m - 1) * (double(m) * h - g2));
    gp = g + sq;
    gm = g - sq;
    double abp = abs(gp);
    double abm = abs(gm);
    if (abp < abm)
      gp = gm;
    dx = MAX(abp, abm) > 0.0 ? double(m) / gp : polar(1 + abx, double(iter));
    x1 = x - dx;
    if (x == x1)
      return; // 
    if (iter % MT != 0)
      x = x1;
    else
      x -= frac[iter / MT] * dx; // 
  }
  throw("too many iterations in laguer()"); // 
}

void zroots(complex<double> a[], complex<double> roots[], int size)
{
  int i, its = 8000;
  complex<double> x, b, c;
  int m = size - 1;
  complex<double> ad[m + 1];
  for (int j = 0; j <= m; j++)
    ad[j] = a[j];
  for (int j = m - 1; j >= 0; j--)
  {
    x = complex<double>(0.0, 0.0);
    complex<double> ad_v[j + 2];
    for (int jj = 0; jj < j + 2; jj++)
      ad_v[jj] = ad[jj];
    laguer(ad_v, x, its, j + 2);
    if (abs(imag(x)) <= 2.0 * blad * abs(real(x)))
      x = complex<double>(real(x), 0.0);
    roots[j] = x;
    b = ad[j + 1];
    for (int jj = j; jj >= 0; jj--)
    {
      c = ad[jj];
      ad[jj] = b;
      b = x * b + c;
    }
  }
  for (int j = 0; j < m; j++)
    laguer(a, roots[j], its, size);
  for (int j = 1; j < m; j++)
  {
    x = roots[j];
    for (i = j - 1; i >= 0; i--)
    {
      if (real(roots[i]) <= real(x))
        break;
      roots[i + 1] = roots[i];
    }
    roots[i + 1] = x;
  }
}

int main()
{
  int N = 10, N2 = 4;
  complex<double> A[11];
  complex<double> roots[11];
  complex<double> B[5];
  complex<double> roots2[5];

  A[0] = complex<double>(-4.0, 0.0);
  A[1] = complex<double>(-4.0, 0.0);
  A[2] = complex<double>(-12.0, 0.0);
  A[3] = complex<double>(-8.0, 0.0);
  A[4] = complex<double>(-11.0, 0.0);
  A[5] = complex<double>(-3.0, 0.0);
  A[6] = complex<double>(-1.0, 0.0);
  A[7] = complex<double>(2.0, 0.0);
  A[8] = complex<double>(3.0, 0.0);
  A[9] = complex<double>(1.0, 0.0);
  A[10] = complex<double>(1.0, 0.0);

  B[0] = complex<double>(1.0, 0.0);
  B[1] = complex<double>(0.0, 1.0);
  B[2] = complex<double>(-1.0, 0.0);
  B[3] = complex<double>(0.0, -1.0);
  B[4] = complex<double>(1.0, 0.0);

  cout << "\n Metoda Laguerre'a + deflacja + wygladzanie \n";
  zroots(A, roots, 11);
  cout << " dokladnosc " << blad << endl;
  cout << "\n 1. policzone pierwiastki:\n"
       << " -------------------------" << endl;
  for (int I = 0; I < N; I++)
    cout << " " << I + 1 << " " << roots[I] << endl;
  cout << endl;

  zroots(B, roots2, 5);
  cout << "\n 2. policzone pierwiastki:\n"
       << " -------------------------" << endl;
  for (int I = 0; I < N2; I++)
    cout << " " << I + 1 << " " << roots2[I] << endl;
  cout << endl;
  return 0;
}