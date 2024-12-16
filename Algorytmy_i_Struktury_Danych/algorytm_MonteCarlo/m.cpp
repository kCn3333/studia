/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|     	program wyznacza skojarzenie doskonale            |
|	          metoda MonteCarlo dla grafu Kn,n 		          |
|	           dwudzielnego (z pliku graf.txt)	            |
|						                                          	  |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>

#define V 50 // max wierzcholkow

using namespace std;

int tab[V][V], dane[V][V], pom[V][V];
int ilosc, usuniete = 0; // zmienne pomocnicze

int wczytaj_dane()
{
  srand(time(NULL));
  int wartosc;
  ifstream plik("graf.txt"); // otwiera plik
  if (!plik.is_open())
    return (0);
  plik >> ilosc; // czyta liczbe wierzcholkow
  if (ilosc > V)
  {
    cout << "\n #zyt duzo wierzcholkow, max " << V << ".\n";
    return (0);
  }

  for (int i = 0; i < ilosc; i++)
    for (int j = 0; j < ilosc; j++)
    {
      dane[i][j] = 0;
      pom[i][j] = 0;
    } // zeruje tablice danych

  for (int i = 0; i < ilosc; i++)
    for (int j = 0; j < ilosc; j++)
    {
      plik >> wartosc;
      if (wartosc == 1) // jesli jest polaczenie
      {
        tab[i][j] = rand();
        pom[i][j] = tab[i][j];
      } // to przypisuje mu wartosc losowa
      else
        tab[i][j] = wartosc; // jesli nie to zostaw 0
    }
}

long double wyznacznik(int det[][V], int n)
{
  long double wyzn = 0.0;
  int temp[V][V], znak, dzielnik, i, j, k;
  if (n == 1) // jesli macierz 1x1
    wyzn = det[0][0];
  else
  { // przechodzi pierwsza kolumne [i][0]
    for (i = 0; i < n; i++)
    { // tworzym temp z wykreslona pierwsza kolumna
      for (k = 0; k < i; k++)
      { // i wykreslonym i-tym wierszem
        for (j = 1; j < n; j++)
          temp[k][j - 1] = det[k][j];
      }
      for (k = i + 1; k < n; k++)
      {
        for (j = 1; j < n; j++)
          temp[k - 1][j - 1] = det[k][j];
      }
      if ((i + 1 + 1) % 2 == 0)
        znak = 1;
      else
        znak = -1;
      wyzn += znak * det[i][0] * wyznacznik(temp, n - 1);
    }
  }
  return wyzn;
}

void usun_przepisz(int row_vector, int column)
{
  int i, j, k = 0, l = 0;     // przepisuje dane do nowej tablicy
  for (i = 0; i < ilosc; i++) // z usunietym wierszem i kolumna
  {
    if (i != row_vector)
    {
      for (j = 0; j < ilosc; j++)
      {
        if (j != column)
          dane[i - k][j - l] = tab[i][j]; // tablica po zmianach
        else
          l = 1;
      }
      l = 0;
    }
    else
      k = 1;
  }
}

void przepisz_tablice(int a1[V][V], int a2[V][V])
{
  for (int i = 0; i < ilosc; i++)
  {
    for (int j = 0; j < ilosc; j++)
      a1[i][j] = a2[i][j];
  }
  usuniete++;
}

void szukaj(int value) // szuka polaczen
{
  for (int i = 0; i < ilosc; i++)
  {
    for (int j = 0; j < ilosc; j++)
      if (pom[i][j] == value) // jesli znajdzie polaczenie wypisuje je
        cout << " " << i + 1 << " - " << (char)(0101 + j) << endl;
  }
}

void skojarz()
{ // wyznacza skojarzenie doskonale
  long double wyz;
  if (wyznacznik(tab, ilosc) != 0) // jesli wyznacznik=0 brak skojarzenia
  {
    for (int i = 0; i < ilosc; i++)
      for (int j = 0; j < ilosc; j++)
        if (tab[i][j] != 0 && usuniete != ilosc - 1)
        {
          usun_przepisz(i, j);                          // usuwa krawedz
          wyz = wyznacznik(dane, ilosc - 1 - usuniete); // i liczy ponownie wyznacznik
          if (wyz != 0)
          {
            szukaj(tab[i][j]);
            przepisz_tablice(tab, dane);
            i = 0;
            j = 0;
          }
        }
    szukaj(tab[0][0]);
  }
  else
    cout << "\n #podany graf nie posiada skojarzenia doskonalego\n";
}

int main()
{
  cout << "\n >program wyznacza skojarzenie doskonale dla\n"
       << " grafu Kn,n dwudzielnego metoda MonteCarlo"
       << "\n dane z pliku graf.txt\n"
       << endl;

  if (wczytaj_dane() == 0)
    return (0);

  skojarz();
  cout << endl;
  return (0);
}
