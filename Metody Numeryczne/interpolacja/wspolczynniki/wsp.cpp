#include <stdio.h>
#include <math.h>
#include <iostream>

#define N 8

using namespace std;

double X[N + 1], Y[N + 1];
double C[N + 1];

void wspolczynniki(double X[], double Y[], double C[])
{
  double phi, ff, b;
  double s[N];
  for (int i = 0; i < N; i++)
    s[i] = C[i] = 0.0;
  s[N - 1] = -X[0];
  for (int i = 1; i < N; i++)
  {
    for (int j = N - 1 - i; j < N - 1; j++)
      s[j] -= X[i] * s[j + 1];
    s[N - 1] -= X[i];
  }
  for (int j = 0; j < N; j++)
  {
    phi = N;
    for (int k = N - 1; k > 0; k--)
      phi = k * s[k] + X[j] * phi;
    ff = Y[j] / phi;
    b = 1.0;
    for (int k = N - 1; k >= 0; k--)
    {
      C[k] += b * ff;
      b = s[k] + X[j] * b;
    }
  }
}

int main()
{
  X[0] = 0.062500;
  Y[0] = 0.687959;
  X[1] = 0.187500;
  Y[1] = 0.073443;
  X[2] = 0.312500;
  Y[2] = -0.517558;
  X[3] = 0.437500;
  Y[3] = -1.077264;
  X[4] = 0.562500;
  Y[4] = -1.600455;
  X[5] = 0.687500;
  Y[5] = -2.080815;
  X[6] = 0.812500;
  Y[6] = -2.507266;
  X[7] = 0.935700;
  Y[7] = -2.860307;

  wspolczynniki(X, Y, C);

  cout << "\n wyznaczony wielomian interpolacyjny : \n"
       << endl;
  cout << " W(x)= ";
  for (int i = 0; i < N; i++)
  {
    cout << C[i] << " x^" << i;
    if (C[i + 1] > 0 && i <= N)
      cout << " +";
    else
      cout << " ";
  }
  cout << endl
       << endl;
}
