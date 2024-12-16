/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|     reprezentacja grafu za pomoca listy sasiedztwa      |
|                                                         |
|                                                         |
|---------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class wierzcholek
{
public:
  unsigned v; // nr wierzcholka
  class wierzcholek *next;
  wierzcholek(unsigned V1) { v = V1; }
};

class Lista
{
  wierzcholek *head, *tail;

public:
  Lista() { head = tail = 0; }
  void Dodaj(unsigned);
  void Wypisz() const;
};

void Lista::Dodaj(unsigned v)
{
  if (tail != 0) // jesli lista nie pusta
  {
    tail->next = new wierzcholek(v);
    tail = tail->next;
  }
  else
    head = tail = new wierzcholek(v);
}

void Lista::Wypisz() const
{
  cout << " | ";
  for (wierzcholek *tmp = head; tmp != 0; tmp = tmp->next)
    cout << tmp->v << " ";
  cout << endl;
}

int main()
{
  unsigned V = 5;
  cout << "\n\t --- reprezenatcja grafow poprzez liste sasiedztwa ---\n\n";
  cout << "\t podaj ilosc wierzcholkow grafu (max 10) V=";
  cin >> V;
  Lista *L = new Lista[V];

  char n_plik[80] = "1.txt";
  cout << "\t podaj nazwe pliku do wczytania: ";
  cin >> n_plik;
  ifstream czytaj(n_plik);
  if (!czytaj)
  {
    cout << " #blad otwarcia pliku " << n_plik << endl;
    return 0;
  }

  unsigned v1 = 0, v2 = 0;
  stringstream tmp;
  string linia, linia2;
  string::size_type position;
  do
  {
    getline(czytaj, linia);
    position = linia.find(" ");
    tmp << linia.substr(0, position);
    tmp >> v1; // wczytuje dane z pliku
    linia2 = linia.erase(0, position + 3);
    v2 = atoi(&linia[0]);
    L[v1].Dodaj(v2);
    L[v2].Dodaj(v1); // i dodaje je do listy
    linia.clear();
    linia2.clear();
    tmp.clear();
    position = 0;
  } while (!czytaj.eof());
  czytaj.close();

  cout << "\n\n";
  for (int i = 0; i < V; i++)
  {
    cout << "\t" << i;
    L[i].Wypisz();
  }

  return 0;
}
