/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|            klucze.cpp program do generowania            |
|                       kluczy RSA                        |
|                                                         |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>
#include <string>

using namespace std;

int p, q, n, e, d;

//---------------------------------
int nwd(int a, int b)
{
  int t;
  while (b != 0)
  {
    t = b; // NWD dwoch liczb
    b = a % b;
    a = t;
  }
  return a;
}
//---------------------------------
int odwr_mod(int a, int n)
{
  int a0, n0, p0, p1, q, r, t;
  p0 = 0;
  p1 = 1;
  a0 = a;
  n0 = n;
  q = n0 / a0;
  r = n0 % a0;
  while (r > 0)
  {
    t = p0 - q * p1; // odwrotnosc modulo
    if (t >= 0)
      t = t % n;
    else
      t = n - ((-t) % n);
    p0 = p1;
    p1 = t;
    n0 = a0;
    a0 = r;
    q = n0 / a0;
    r = n0 % a0;
  }
  return p1;
}
//---------------------------------
// Procedura generowania kluczy RSA
//---------------------------------
void klucze_RSA()
{
  const int tp[10] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
  int phi;

  // wygenerowanie dwoch losowych liczb pierwszych
  do
  {
    p = tp[rand() % 10];
    q = tp[rand() % 10];
  } while (p == q);
  phi = (p - 1) * (q - 1);
  n = p * q;
  // wyznaczanie wykadnikow e i d
  for (e = 3; nwd(e, phi) != 1; e += 2)
    ;
  d = odwr_mod(e, phi);
  // wypisanie kluczy
  cout << " KLUCZ PUBLICZNY\n"
          " wykladnik e = "
       << e
       << "\n    modul n = " << n
       << "\n\n KLUCZ PRYWATNY\n"
       << " wykladnik d = " << d << "\n\n";
}
//---------------------------------

main()
{
  cout << "\n";
  cout << " ***********************************\n"
       << " ** Program generujacy klucze RSA **\n"
       << " ***********************************\n\n";

  klucze_RSA();
  cout << "-------------------\n\n";
  klucze_RSA();
}
