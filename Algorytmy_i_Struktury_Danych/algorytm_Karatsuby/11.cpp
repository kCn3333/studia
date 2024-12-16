/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|    11.cpp mnozenie duzych liczb algorytmem Karatsuby    |
|                                                         |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>

using namespace std;

//-----------------------------------------------------------
void karatsuba(int *A, int *B, int *C, int d)
{
  int i;
  int *a1 = &A[0];                // pierwsza polowa z A
  int *a2 = &A[d / 2];            // druga polowa z A
  int *b1 = &B[0];                // pierwsza polowa z B
  int *b2 = &B[d / 2];            // druga polowa z B
  int *a_sum = &C[d * 5];         // a1 + a2
  int *b_sum = &C[d * 5 + d / 2]; // b1 + b2
  int *x1 = &C[d * 0];            // a1 * b1
  int *x2 = &C[d * 1];            // a2 * b2
  int *x3 = &C[d * 2];            // a_sum * b_sum

  if (d <= 4)
  {
    for (int n = 0; n < 2 * d; n++)
      C[n] = 0;

    for (i = 0; i < d; i++)
    {
      for (int j = 0; j < d; j++)
        C[i + j] += A[i] * B[j];
    }
    return;
  }

  for (i = 0; i < d / 2; i++)
  {
    a_sum[i] = a2[i] + a1[i];
    b_sum[i] = b2[i] + b1[i];
  }

  karatsuba(a1, b1, x1, d / 2); // rekurencja
  karatsuba(a2, b2, x2, d / 2);
  karatsuba(a_sum, b_sum, x3, d / 2);

  for (i = 0; i < d; i++)
    x3[i] = x3[i] - x1[i] - x2[i];

  for (i = 0; i < d; i++)
    C[i + d / 2] += x3[i];
}
//-----------------------------------------------------------

int main()
{
  int A[1024];     // pierwszy czynnik mnozenia
  int B[1024];     // drugi czynnik
  int C[6 * 1024]; // wynik mnozenia
  int a_dl = 0;    // dlugosc a
  int b_dl = 0;    // dlugosc b
  int d;           // max dlugosc
  int i;           // licznik
  int z;

  cout << "\n  podaj liczbe A : ";

  while (1)
  {
    z = getchar(); // wczytanie A
    if (z == '\n' || z == EOF)
      break;
    A[a_dl] = z - '0';
    ++a_dl;
  }
  for (int i = 0; i * 2 < a_dl - 1; i++)
  {
    z = A[i];
    A[i] = A[a_dl - i - 1];
    A[a_dl - i - 1] = z;
  }

  cout << "  podaj liczbe B : ";
  while (1)
  {
    z = getchar(); // wczytanie B
    if (z == '\n' || z == EOF)
      break;
    B[b_dl] = z - '0';
    ++b_dl;
  }
  for (int i = 0; i * 2 < b_dl - 1; i++)
  {
    z = B[i];
    B[i] = B[b_dl - i - 1];
    B[b_dl - i - 1] = z;
  }

  i = (a_dl > b_dl) ? a_dl : b_dl;
  for (d = 1; d < i; d *= 2)
    ;
  for (i = a_dl; i < d; i++)
    A[i] = 0;
  for (i = b_dl; i < d; i++)
    B[i] = 0;

  karatsuba(A, B, C, d);

  z = 0;
  for (i = 0; i < 2 * d; i++)
  {
    C[i] += z;
    if (C[i] < 0)
    {
      z = -(-(C[i] + 1) / 10 + 1);
    }
    else
    {
      z = C[i] / 10;
    }
    C[i] -= z * 10;
  }
  if (z != 0)
    cout << ":: przepelnienie bufora... " << z << "\n";

  cout << "\n  A*B = ";
  for (i = 2 * d - 1; i > 0; i--)
    if (C[i] != 0)
      break;
  for (; i >= 0; i--)
    cout << C[i]; // wypisanie C
  cout << "\n\n";
}
