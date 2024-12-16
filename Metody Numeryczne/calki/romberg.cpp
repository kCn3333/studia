#include <iostream>
#include <cmath>

#define ZERO 0.0
#define MAX 17
#define precyzja 0.00000001
#define size 50

using namespace std;

double f(long double x)
{
  return sin((1 + sqrt(x)) / (1 + x * x)) * exp(-x);
}

double f2(long double x)
{
  return cos((1.0 + x) / (x * x + 0.04)) * exp(-x * x);
}

int Romberg(long double a, long double b, long double R[size][size])
{
  int i = 0, j, k;
  long double h, sum;

  h = b - a;
  R[0][0] = (h / 2) * (f(a) + f(b));

  do
  {
    i++;
    h = h / 2;
    sum = 0;
    for (k = 1; k <= int(pow(2.0, i) - 1); k += 2)
      sum += f(a + k * h);
    R[i][0] = R[i - 1][0] / 2 + sum * h;
    for (j = 1; j <= i; j++)
    {
      R[i][j] = R[i][j - 1] + (R[i][j - 1] - R[i - 1][j - 1]) / (pow(4.0, j) - 1);
    }
  } while (fabs(R[i - 1][i - 1] - R[i][i]) >= precyzja);
  return i;
}

int main()
{
  int iter;
  long double R_tab[size][size];

  iter = Romberg(ZERO, MAX, R_tab);

  cout.precision(14);
  cout << "\n  Pole = " << R_tab[iter][iter] << endl;
}