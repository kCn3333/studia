/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|         program tworzy liste jednokierunkowa            |
|                                                         |
|                                                         |
|---------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ls.h"

using namespace std;

int main()
{
  Lista L;
  int gr;
  string imie, nazwisko;
  stringstream grupa;

  ifstream odczyt("lista.txt"); // otwiera plik lista.txt
  if (!odczyt.is_open())
    cout << "\n #blad otwarcia pliku lista.txt";
  string linia, linia2;
  string::size_type position;

  do
  {
    getline(odczyt, linia);
    position = linia.find(" ");
    grupa << linia.substr(0, position);
    grupa >> gr; // wczytuje dane z pliku
    linia2 = linia.erase(0, position + 1);
    position = linia2.find(" ");
    imie = linia2.substr(0, position);
    linia = linia2.erase(0, position + 1);
    position = linia.find(" ");
    nazwisko = linia.substr(0, position);
    L.AddToTail(gr, imie, nazwisko); // i dodaje je do listy
    linia.clear();
    linia2.clear();
    grupa.clear();
    position = 0;
  } while (!odczyt.eof());
  odczyt.close();

  cout << "\n -- lista jednokierunkowa -- \n\n";
  L.Print();
  cout << endl;

  int menu = 0;
  while (1)
  {
    cout << "\n\n _____________________"
         << "\n [1] sprawdz czy pusta"
         << "\n [2] dodaj na koncu"
         << "\n [3] przeszukaj liste"
         << "\n [4] pokaz liste"
         << "\n [0] wyjscie\n\n ";
    cin >> menu;

    switch (menu)
    {
    case 0:
      exit(1);
    case 1:
    {
      if (L.isEmpty())
        cout << "\n #lista jest pusta";
      else
        cout << "\n #lista nie jest pusta";
      break;
    }
    case 2:
    {
      cout << "\n podaj numer grupy: ";
      cin >> gr;
      cout << "\n podaj imie: ";
      cin >> imie;
      cout << "\n podaj nazwisko: ";
      cin >> nazwisko;
      L.AddToTail(gr, imie, nazwisko);
      break;
    }
    case 3:
    {
      cout << "\n przeszukiwanie listy "
           << "\n podaj nazwisko: ";
      cin >> nazwisko;
      if (L.IsInList(nazwisko))
        cout << "\n #" << nazwisko << " - znaleziono na liscie";
      else
        cout << "\n #" << nazwisko << " - nie znaleziono";
      break;
    }
    case 4:
    {
      L.Print();
      break;
    }
    }
  }
  return 0;
}
