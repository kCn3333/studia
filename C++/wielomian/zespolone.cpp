#include "zespolone.h"

//-----------------------------------------------------------
int wb(const int x)
{
  if (x < 0)
  {
    return -x;
  }
  else
    return x;
}
//-----------------------------------------------------------
int modul(const zesp &z)
{
  return (int)(sqrt(z.re * z.re + z.im * z.im) + 0.5);
}
//-----------------------------------------------------------
zesp &zesp::operator=(const zesp &z1)
{
  re = z1.re;
  im = z1.im;
  return *this;
}
//-----------------------------------------------------------
zesp &zesp::operator-=(const zesp &z1)
{
  re -= z1.re;
  im -= z1.im;
  return *this;
}
//-----------------------------------------------------------
zesp &zesp::operator+=(const zesp &z1)
{
  re += z1.re;
  im += z1.im;
  return *this;
}
//-----------------------------------------------------------
ostream &operator<<(ostream &wypisz, const zesp z1)
{
  if (z1.im == 0)
  {
    wypisz << "(" << z1.re << ")";
  }
  else if (z1.im < 0)
  {
    wypisz << "(" << z1.re << " - " << wb(z1.im) << "i)";
  }
  else
  {
    wypisz << "(" << z1.re << " + " << wb(z1.im) << "i)";
  }
  return wypisz;
}
//-----------------------------------------------------------
zesp &operator>>(istream &wpisz, zesp &z1)
{
  char tmp;
  wpisz >> z1.re;
  if (wpisz.peek() == '+' || wpisz.peek() == ',')
  {
    wpisz >> tmp;
  }
  wpisz >> z1.im;
  return z1;
}
//-----------------------------------------------------------
zesp operator+(const zesp &z1, const zesp &z2)
{
  return zesp(z1.re + z2.re, z1.im + z2.im);
}
//-----------------------------------------------------------
zesp operator-(const zesp &z1, const zesp &z2)
{
  return zesp(z1.re - z2.re, z1.im - z2.im);
}
//-----------------------------------------------------------
zesp operator/(const zesp &z1, const zesp &z2)
{
  if (!modul(z2))
  {
    cout << " #nie dzielimy przez 0, zwracam 0\n";
    return zesp(0);
  }
  else
    return zesp((z1.re * z2.re + z1.im * z2.im) / (modul(z1) * modul(z1)), (z1.im * z2.re - z1.re * z2.im) / (modul(z2) * modul(z2)));
}
//-----------------------------------------------------------
zesp operator*(const zesp &z1, const zesp &z2)
{
  return zesp(z1.re * z2.re - z1.im * z2.im, z1.re * z2.im + z1.im * z2.re);
}
//-----------------------------------------------------------
bool operator!=(const zesp &z1, const zesp &z2)
{
  return !(z1 == z2);
}
//-----------------------------------------------------------
bool operator==(const zesp &z1, const zesp &z2)
{
  if (z1.re == z2.re && z1.im == z2.im)
  {
    return 1;
  }
  else
    return 0;
}
