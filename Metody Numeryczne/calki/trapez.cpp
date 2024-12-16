#include <iostream>
#include <cmath>

#define ZERO 0.0
#define MAX 17
#define precyzja 0.00000001

using namespace std;

double f(double x)
{
  return sin((1.0 + sqrt(x)) / (1.0 + x * x)) * exp(-x);
}

double f2(double x)
{
  return cos((1.0 + x) / (x * x + 0.04)) * exp(-x * x);
}

double trapez()
{
  double a, b, suma, dx, tmp1 = 0, tmp2 = 1;
  int i = 1, n;
  int k = 1;
  a = ZERO; // dolna granica
  b = MAX;  // gorna granica
  n = 1;    // liczba podzialow

  do
  {
    n *= 2;
    tmp1 = tmp2;
    suma = (f(a) + f(b)) / 2;
    dx = (b - a) / n;
    for (i = 1; i <= n; i++)
      suma = suma + f(a + i * dx);
    tmp2 = suma * dx;
    k++;
  } while (fabs(tmp1 - tmp2) > precyzja);

  cout.precision(14);
  cout << fixed << "N = 2^" << k << ", pole = " << tmp2 << endl;

  return tmp2;
}

int main()
{
  trapez();
}
