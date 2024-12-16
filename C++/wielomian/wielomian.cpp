#include "zespolone.h"
#include "wielomian.h"

zesp zero = 0;
//-----------------------------------------------------------
wielomian::wielomian(const int stopien) // KONSTRUKTOR 1
{
  st = stopien;           // ustwia stopien wielomianu
  wsp = new zesp[st + 1]; // tablica wspolczynnikow
  for (int i = 0; i <= st; ++i)
  {
    wsp[i] = 0;
  } // wy_zerowana
}
//-----------------------------------------------------------
wielomian::wielomian(const int stopien, const zesp wspolcz[])
{ // KONSTRUKTOR 2
  st = stopien;
  wsp = new zesp[st + 1];
  for (int i = 0; i <= st; ++i)
  {
    wsp[i] = wspolcz[i];
  }
} // wczytuje z tablicy
//-----------------------------------------------------------
wielomian::wielomian(const zesp &z) // JEDNOMIAN
{
  st = 0;
  wsp = new zesp[st + 1];
  wsp[st] = z;
}
//-----------------------------------------------------------
wielomian::wielomian(const wielomian &w1) // KONSTRUKTOR-K
{
  if (this != &w1)
  {
    st = w1.st;
    wsp = new zesp[st + 1];
    for (int i = 0; i <= st; ++i)
    {
      wsp[i] = w1.wsp[i];
    }
  }
}
//-----------------------------------------------------------
wielomian &wielomian::operator=(const wielomian &w1)
{ // PRZYPISANIE
  if (this == &w1)
  {
    return *this;
  }
  st = w1.st;
  wsp = new zesp[st + 1];
  for (int i = 0; i <= st; ++i)
  {
    wsp[i] = w1.wsp[i];
  }
  return *this;
}
//-----------------------------------------------------------
zesp &wielomian::operator[](const int n) // WSPOLCZYNNIK
{
  if (n < 0)
  {
    cout << " #stopien nie moze byc ujemny";
    exit(1);
  }
  else if (n <= st)
  {
    return wsp[n];
  }
  else
    return zero; // globalne zespolone zero
}
//-----------------------------------------------------------
zesp wielomian::operator()(const zesp z) // WARTOSC W
{
  zesp wynik = wsp[0];
  for (int i = 1; i <= st; ++i)
  {
    wynik = wynik * z; // Horner
    wynik = wynik + wsp[i];
  }
  return wynik;
}
//-----------------------------------------------------------
ostream &operator<<(ostream &wypisz, const wielomian w1)
{ // WYPISYWANIE
  for (int i = 0; i < w1.st; ++i)
  {
    wypisz << w1.wsp[i] << "x^" << w1.st - i << " + ";
  }
  wypisz << w1.wsp[w1.st];
  return wypisz;
}
//-----------------------------------------------------------
wielomian &operator>>(istream &wpisz, wielomian &w1)
{ // WPISYWANIE
  cout << "\n podaj stopien wielomianu: ";
  wpisz >> w1.st;
  if (w1.st < 0)
  {
    cout << " #stopien nie moze byc ujemny\n";
    exit(1);
  }
  delete[] w1.wsp;
  w1.wsp = new zesp[w1.st + 1];
  cout << " podaj wspolczynniki wielomianu\n";
  for (int i = 0; i <= w1.st; ++i)
  {
    cout << " wspolczynnik przy x^" << w1.st - i << " : ";
    wpisz >> w1.wsp[i];
  }
  return w1;
}
//-----------------------------------------------------------
wielomian operator+(const wielomian &w1, const wielomian &w2)
{ // DODAWANIE
  int i = 0, j = 0;
  int stopien = (w1.st > w2.st) ? w1.st : w2.st;
  zesp *buf = new zesp[stopien + 1]; // bufor
  if (w1.st > w2.st)
  {
    for (i = 0; i <= stopien; ++i)
      buf[i] = w1.wsp[i];
    for (i = 0; i <= w2.st; ++i)
      buf[w1.st - w2.st + i] += w2.wsp[i];
  }
  else
  {
    for (i = 0; i <= stopien; ++i)
      buf[i] = w2.wsp[i];
    for (i = 0; i <= w1.st; i++)
      buf[w2.st - w1.st + i] += w1.wsp[i];
  }
  for (i = 0; i <= stopien; ++i)
  {
    if (buf[i] == zesp(0, 0))
      j++;
    else
      break;
  }
  stopien -= j;
  if (stopien < 0)
    stopien = 0;
  wielomian w(stopien, buf);
  delete[] buf;
  return w;
}
//-----------------------------------------------------------
wielomian operator-(const wielomian &w1, const wielomian &w2)
{ // ODEJMOWANIE
  int i = 0, j = 0;
  int stopien = (w1.st > w2.st) ? w1.st : w2.st;
  zesp *buf = new zesp[stopien + 1]; // bufor
  if (w1.st >= w2.st)
  {
    for (i = 0; i <= stopien; i++)
      buf[i] = w1.wsp[i];
    for (i = 0; i <= w2.st; ++i)
      buf[w1.st - w2.st + i] -= w2.wsp[i];
  }
  else
  {
    for (i = 0; i <= stopien; ++i)
      buf[i] = w2.wsp[i];
    for (i = 0; i <= w1.st; ++i)
      buf[w2.st - w1.st + i] -= w1.wsp[i];
  }
  for (i = 0; i <= stopien; i++)
  {
    if (buf[i] == zero)
      j++;
    else
      break;
  }
  stopien -= j;
  if (stopien < 0)
    stopien = 0;
  wielomian w(stopien, buf);
  delete[] buf;
  return w;
}
//-----------------------------------------------------------
wielomian operator*(const wielomian &w1, const wielomian &w2)
{ // MNOZENIE
  int stopien = w1.st + w2.st;
  zesp *buf = new zesp[stopien + 1]; // bufor
  for (int i = 0; i <= stopien; i++)
    buf[i] = zero; // zeruje
  for (int i = 0; i <= w1.st; ++i)
    for (int j = 0; j <= w2.st; j++)
      buf[i + j] += w1.wsp[i] * w2.wsp[j];
  wielomian w(stopien, buf);
  delete[] buf;
  return w;
}
//-----------------------------------------------------------
bool operator==(const wielomian &w1, const wielomian &w2)
{ // ROWNOSC
  if (w1.st != w2.st)
    return false;
  for (int i = 0; i <= w1.st; ++i)
    if (w1.wsp[i] != w2.wsp[i])
      return false;
  return true;
}
//-----------------------------------------------------------
bool operator!=(const wielomian &w1, const wielomian &w2)
{
  return !(w1 == w2);
} // NIEROWNOSC
