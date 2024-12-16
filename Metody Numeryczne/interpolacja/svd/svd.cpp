#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <sys/time.h>

#define SIZE 130
#define eps 0.0000001
#define SIGN(a, b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
#define SQR(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(A, B) ((A) < (B) ? (A) : (B))

using namespace std;

const int n = 3;
const int m = 128;
double A[n][n], U[m][n], V[n][n], W[m], X[SIZE], Y[SIZE], wsp[n], COV[n][n], B[n];

double pythag(const double a, const double b)
{
  double absa = abs(a), absb = abs(b);
  return (absa > absb ? absa * sqrt(1.0 + SQR(absb / absa)) : (absb == 0.0 ? 0.0 : absb * sqrt(1.0 + SQR(absa / absb))));
}

void svd()
{
  bool flag;
  int i, j, jj, its, k, l, nm;
  double anorm, c, f, g, h, s, scale, x, y, z;
  double rv1[n];

  g = scale = anorm = 0.0; // Hausolder
  for (i = 0; i < n; i++)
  {
    l = i + 2;
    rv1[i] = scale * g;
    g = s = scale = 0.0;
    if (i < m)
    {
      for (k = i; k < m; k++)
        scale += abs(U[k][i]);
      if (scale != 0.0)
      {
        for (k = i; k < m; k++)
        {
          U[k][i] /= scale;
          s += U[k][i] * U[k][i];
        }
        f = U[i][i];
        g = -SIGN(sqrt(s), f);
        h = f * g - s;
        U[i][i] = f - g;
        for (j = l - 1; j < n; j++)
        {
          for (s = 0.0, k = i; k < m; k++)
            s += U[k][i] * U[k][j];
          f = s / h;
          for (k = i; k < m; k++)
            U[k][j] += f * U[k][i];
        }
        for (k = i; k < m; k++)
          U[k][i] *= scale;
      }
    }
    W[i] = scale * g;
    g = s = scale = 0.0;
    if ((i + 1 <= m) && ((i + 1) != n)) // ?!??!?!?!??!?!
    {
      for (k = l - 1; k < n; k++)
        scale += abs(U[i][k]);
      if (scale != 0.0)
      {
        for (k = l - 1; k < n; k++)
        {
          U[i][k] /= scale;
          s += U[i][k] * U[i][k];
        }
        f = U[i][l - 1];
        g = -SIGN(sqrt(s), f);
        h = f * g - s;
        U[i][l - 1] = f - g;
        for (k = l - 1; k < n; k++)
          rv1[k] = U[i][k] / h;
        for (j = l - 1; j < m; j++)
        {
          for (s = 0.0, k = l - 1; k < n; k++)
            s += U[j][k] * U[i][k];
          for (k = l - 1; k < n; k++)
            U[j][k] += s * rv1[k];
        }
        for (k = l - 1; k < n; k++)
          U[i][k] *= scale;
      }
    }
    anorm = MAX(anorm, (abs(W[i]) + abs(rv1[i])));
  }
  for (i = n - 1; i >= 0; i--) // akumulacja prawej strony transformacji
  {
    if (i < n - 1)
    {
      if (g != 0.0)
      {
        for (j = l; j < n; j++) //
          V[j][i] = (U[i][j] / U[i][l]) / g;
        for (j = l; j < n; j++)
        {
          for (s = 0.0, k = l; k < n; k++)
            s += U[i][k] * V[k][j];
          for (k = l; k < n; k++)
            V[k][j] += s * V[k][i];
        }
      }
      for (j = l; j < n; j++)
        V[i][j] = V[j][i] = 0.0;
    }
    V[i][i] = 1.0;
    g = rv1[i];
    l = i;
  }

  for (i = MIN(m, n) - 1; i >= 0; i--) // akumulacja lewej strony transformacji
  {
    l = i + 1;
    g = W[i];
    for (j = l; j < n; j++)
      U[i][j] = 0.0;
    if (g != 0.0)
    {
      g = 1.0 / g;
      for (j = l; j < n; j++)
      {
        for (s = 0.0, k = l; k < m; k++)
          s += U[k][i] * U[k][j];
        f = (s / U[i][i]) * g;
        for (k = i; k < m; k++)
          U[k][j] += f * U[k][i];
      }
      for (j = i; j < m; j++)
        U[j][i] *= g;
    }
    else
      for (j = i; j < m; j++)
        U[j][i] = 0.0;
    ++U[i][i];
  }
  for (k = n - 1; k >= 0; k--) // diagonalizacja
  {
    for (its = 0; its < 30; its++)
    {
      flag = true;
      for (l = k; l >= 0; l--) // test
      {
        nm = l - 1;
        if (l == 0 || (abs(rv1[l]) <= eps * anorm))
        {
          flag = false;
          break;
        }
        if (abs(W[nm]) <= eps * anorm)
          break;
      }
      if (flag)
      {
        c = 0.0;
        s = 1.0;
        for (i = l; i < k + 1; i++)
        {
          f = s * rv1[i];
          rv1[i] = c * rv1[i];
          if (abs(f) <= eps * anorm)
            break;
          g = W[i];
          h = pythag(f, g);
          W[i] = h;
          h = 1.0 / h;
          c = g * h;
          s = -f * h;
          for (j = 0; j < m; j++)
          {
            y = U[j][nm];
            z = U[j][i];
            U[i][nm] = y * c + z * s;
            U[j][i] = z * c - y * s;
          }
        }
      }
      z = W[k];
      if (l == k) // konwengencja
      {
        if (z < 0.0) //
        {
          W[k] = -z;
          for (j = 0; j < n; j++)
            V[j][k] = -V[j][k];
        }
        break;
      }
      if (its == 29)
        throw("\n #no convergence in 30 iterations...\n");
      x = W[l];
      nm = k - 1;
      y = W[nm];
      g = rv1[nm];
      h = rv1[k];
      f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0 * h * y);
      g = pythag(f, 1.0);
      f = ((x - z) * (x + z) + h * ((y / (f + SIGN(g, f))) - h)) / x;
      c = s = 1.0; // transformacja QR
      for (j = l; j <= nm; j++)
      {
        i = j + 1;
        g = rv1[i];
        y = W[i];
        h = s * g;
        g = c * g;
        z = pythag(f, h);
        rv1[j] = z;
        c = f / z;
        s = h / z;
        f = x * c + g * s;
        g = g * c - x * s;
        h = y * s;
        y *= c;
        for (jj = 0; jj < n; jj++)
        {
          x = V[jj][j];
          z = V[jj][i];
          V[jj][j] = x * c + z * s;
          V[jj][i] = z * c - x * s;
        }
        z = pythag(f, h);
        W[j] = z;
        if (z) // obrot gdy z=0
        {
          z = 1.0 / z;
          c = f * z;
          s = h * z;
        }
        f = c * g + s * y;
        x = c * y - s * g;
        for (jj = 0; jj < m; jj++)
        {
          y = U[jj][j];
          z = U[jj][i];
          U[jj][j] = y * c + z * s;
          U[jj][i] = z * c - y * s;
        }
      }
      rv1[l] = 0.0;
      rv1[k] = f;
      W[k] = x;
    }
  }
}

void makeU()
{
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      U[i][j] = 1.0;
      for (int k = n - j - 1; k > 0; k--)
        U[i][j] *= X[i];
    }
  }
}

void reorder()
{
  int i, j, k, s, inc = 1;
  double sw;
  double su[m], sv[n];
  do
  {
    inc *= 3;
    inc++;
  } while (inc <= n);
  do // Shell's sort
  {
    inc /= 3;
    for (i = inc; i < n; i++)
    {
      sw = W[i];
      for (k = 0; k < m; k++)
        su[k] = U[k][i];
      for (k = 0; k < n; k++)
        sv[k] = V[k][i];
      j = i;
      while (W[j - inc] < sw)
      {
        W[j] = W[j - inc];
        for (k = 0; k < m; k++)
          U[k][j] = U[k][j - inc];
        for (k = 0; k < n; k++)
          V[k][j] = V[k][j - inc];
        j -= inc;
        if (j < inc)
          break;
      }
      W[j] = sw;
      for (k = 0; k < m; k++)
        U[k][j] = su[k];
      for (k = 0; k < n; k++)
        V[k][j] = sv[k];
    }
  } while (inc > 1);
  for (k = 0; k < n; k++) // odwrotne znaki
  {
    s = 0;
    for (i = 0; i < m; i++)
      if (U[i][k] < 0.0)
        s++;
    for (j = 0; j < n; j++)
      if (V[j][k] < 0.0)
        s++;
    if (s > ((m + n) / 2))
    {
      for (i = 0; i < m; i++)
        U[i][k] = -U[i][k];
      for (j = 0; j < n; j++)
        V[j][k] = -V[j][k];
    }
  }
}

void LUdist()
{
  int i, j, k;

  for (k = 0; k < n - 1; k++)
  {
    if (fabs(A[k][k]) < eps)
      throw("#LUdist() < eps");

    for (i = k + 1; i < n; i++)
      A[i][k] /= A[k][k];

    for (i = k + 1; i < n; i++)
      for (j = k + 1; j < n; j++)
        A[i][j] -= A[i][k] * A[k][j];
  }
}

void LUsolve(int k)
{
  int i, j;
  double s;

  for (i = 1; i < n; i++)
  {
    s = 0.0;
    for (j = 0; j < i; j++)
      s += A[i][j] * COV[j][k];
    COV[i][k] -= s;
  }
  if (fabs(A[n - 1][n - 1]) < eps)
    throw("#LUsolve() < eps");

  COV[n - 1][k] /= A[n - 1][n - 1];
  for (i = n - 2; i >= 0; i--)
  {
    s = 0.0;
    for (j = i + 1; j < n; j++)
      s += A[i][j] * COV[j][k];
    if (fabs(A[i][i]) < eps)
      throw("#LUsolve() < eps");
    COV[i][k] = (COV[i][k] - s) / A[i][i];
  }
}

double f(double x)
{
  double yy = 0.0, temp;
  for (int j = 0; j < n; j++)
  {
    temp = 1.0;
    for (int k = n - j - 1; k > 0; k--)
      temp *= x;
    temp *= wsp[j];
    yy += temp;
  }
  return yy;
}

int main(int argc, char *argv[])
{
  string plik;

  if (argc != 2)
  {
    cout << "Podaj nazwe pliku wejsciowego" << endl;
    cin >> plik;
  }
  else
    plik = argv[1];

  ifstream odczyt(plik.c_str());

  for (int i = 0; i < m; i++)
  {
    odczyt >> X[i];
    odczyt >> Y[i];
  }

  makeU();

  for (int k = 0; k < n; k++) // U^T U
    for (int j = 0; j < n; j++)
      for (int i = 0; i < m; i++)
        A[k][j] += U[i][k] * U[i][j];

  LUdist();
  for (int i = 0; i < n; i++) // macierz jednostkowa
  {
    for (int j = 0; j < n; j++)
      COV[i][j] = 0.0;
    COV[i][i] = 1.0;
  }
  for (int i = 0; i < n; i++)
    LUsolve(i);

  svd();
  reorder();

  double VS[n][n]; // V*S

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      VS[i][j] = V[i][j] * (1.0 / W[j]);

  double B[n];
  for (int i = 0; i < n; i++)
    B[i] = 0.0;

  for (int j = 0; j < n; j++) // U*y
  {
    for (int i = 0; i < m; i++)
    {
      B[j] += U[i][j] * Y[i];
    }
  }

  cout << "\n wspolczynniki dopasowanego wielomianu " << endl;
  for (int j = 0; j < n; j++)
  {
    wsp[j] = 0.0;
    for (int i = 0; i < n; i++)
    {
      wsp[j] += VS[j][i] * B[i]; //(V*S)*(U*b)
    }
    cout.precision(10);
    cout << wsp[j] << endl;
  }

  double bb = 0.0;
  for (int i = 0; i < m; i++)
    bb += SQR(Y[i] - f(X[i]));
  bb = bb / m;
  cout << "\n b=" << bb << endl;

  cout << "\n macierz kowariancji" << endl;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      cout << bb * COV[i][j] << " ";
    cout << endl;
  }
  cout << endl;
}
