/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|        program wylicza liczbe skladowych spojnosci      |
|                         grafu                           |
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
public:
  wierzcholek *head, *tail;
  Lista() { head = tail = 0; }
  void Dodaj(unsigned);
  void Wypisz() const;
  friend int DFS(unsigned);
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

bool visited[1000]; // tablica odwiedzin wierzcholkow
unsigned c[1000], cmax = 0;

int DFS(Lista li[], unsigned vi)
{
  wierzcholek *w;
  visited[vi] = true;
  c[vi] = cmax;
  w = li[vi].head;
  while (w)
  {
    if (!visited[w->v])
      DFS(li, w->v); // przeszukiwanie w glab
    w = w->next;
  }
  return 1;
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
  unsigned V;
  int i = 0, s = 1;
  cout << "\n\t --- reprezenatcja grafow poprzez liste sasiedztwa ---\n\n";
  cout << "\t podaj ilosc wierzcholkow grafu V=";
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
  for (i = 0; i < V; i++)
  {
    cout << "\t" << i;
    L[i].Wypisz();
  }

  for (i = 0; i < 1000; i++)
  {
    visited[i] = false;
  }

  for (i = 0; i < V; i++)
  {
    if (!visited[i])
    {
      cmax = i;
      DFS(L, i);
    }
  }
  if (cmax == 0)
    cout << "\n\t>> Graf spojny" << endl;
  else
  {
    cout << "\n\t>> Graf niespojny" << endl;
    for (i = 0; i < V - 1; i++)
      if (c[i] != c[i + 1])
        s++;
    cout << "\n\tliczba skladowych spojnosci grafu: " << s << endl;
  }

  cout << endl;
  return 0;
}
