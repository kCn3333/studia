/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|     program wyznacza schemat autostrad w Polsce         |
|         laczacy siedziby miast wojewodzkich,            |
|        ktorego koszt budowy jest najmniejszy            |
|   minimalne drzewo rozpinajace - algorytm Kruskala      |
|   polaczenia z pliku polska.txt, miasta z miasta.txt    |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define MIAST 16 // ilosc miast

using namespace std;

class Graf
{
  unsigned V, E;      // ilosc wierzcholkow i krawedzi
  unsigned **GrafTab; // macierz polaczen
  unsigned **Tree;    // minimalne drzewo rozpinajace
  int sets[100][10];
  int top[100];

public:
  Graf(unsigned E1);
  bool Wstaw(unsigned i, unsigned v, unsigned u, unsigned waga);
  void Sortowanie();
  void Autostrady();
  int find(int n);
};

Graf::Graf(unsigned E1) : V(MIAST), E(E1) // konstruktor
{
  GrafTab = new unsigned *[E1 + 1]; // tworzy macierz polaczen
  Tree = new unsigned *[V + 1];     // i macierz sasiedztwa
                                    // minimalnego drzewa rozpinajacego
  for (int i = 1; i <= E; i++)      // i wypelnia je zerami
  {
    GrafTab[i] = new unsigned[4];
    Tree[i] = new unsigned[V + 1];
    for (int j = 1; j <= E; j++)
      GrafTab[i][j] = 0;
  }
  for (int i = 1; i <= V; i++)
  {
    top[i] = 1;
    sets[i][1] = i;
  }
}

bool Graf::Wstaw(unsigned i, unsigned v, unsigned u, unsigned waga)
{ // wstawia polaczenia do macierzy
  GrafTab[i][0] = i;
  GrafTab[i][1] = v;
  GrafTab[i][2] = u;
  GrafTab[i][3] = waga;
}

void Graf::Sortowanie()
{ // sortowanie babelkowe po wagach
  int p;
  for (int i = 1; i <= E - 1; i++)
    for (int j = 1; j <= E - i; j++)
      if (GrafTab[j][3] > GrafTab[j + 1][3])
      {
        p = GrafTab[j][1];
        GrafTab[j][1] = GrafTab[j + 1][1];
        GrafTab[j + 1][1] = p;
        p = GrafTab[j][2];
        GrafTab[j][2] = GrafTab[j + 1][2];
        GrafTab[j + 1][2] = p;
        p = GrafTab[j][3];
        GrafTab[j][3] = GrafTab[j + 1][3];
        GrafTab[j + 1][3] = p;
      }
}
string miasto(int); // zapowiedz funkcji miasto :D

void Graf::Autostrady()
{
  unsigned suma = 0; // suma dl autostrady
  cout << "\n\t POLACZENIA BEZPOSREDNIE" << endl;

  for (int i = 1; i <= E; i++) // Algorytm Kruskala
  {
    int p1 = find(GrafTab[i][1]);
    int p2 = find(GrafTab[i][2]);
    if (p1 != p2) // jesli nie cykl
    {
      cout << " | " << miasto(GrafTab[i][1])
           << "  \t<- " << GrafTab[i][3] << " km ->\t"
           << miasto(GrafTab[i][2]) << endl;

      suma = suma + GrafTab[i][3];
      Tree[GrafTab[i][1]][GrafTab[i][2]] = GrafTab[i][3]; // dodaje do drzewa
      Tree[GrafTab[i][2]][GrafTab[i][1]] = GrafTab[i][3];

      for (int j = 1; j <= top[p2]; j++)
      {
        top[p1]++;
        sets[p1][top[p1]] = sets[p2][j];
      }
      top[p2] = 0;
    }
  }
  cout << "\n\t\t---------------" << "\n\t\tSUMA DL. = " << suma << endl;
}

int Graf::find(int n)
{
  for (int i = 1; i <= E; i++) // szuka polaczen
    for (int j = 1; j <= top[i]; j++)
      if (n == sets[i][j])
        return i;
  return -1;
}

string miasto(int n)
{
  stringstream tmp;
  string linia;               // funkcjia zamienia nr na nazwe miasta
  string::size_type position; // z pliku miasta.txt
  char plik[80] = "miasta.txt";
  ifstream czytaj(plik);
  for (int i = 0; i < n; i++)
  {
    linia.clear();
    getline(czytaj, linia);
  }
  position = linia.find(" ");
  tmp << linia.substr(0, position);
  linia.clear();
  tmp >> linia;
  return linia;
}

unsigned ile_linii()
{ // zwraca ilosc linijek w polska.txt
  int n = 1;
  char tmp;
  FILE *plik;
  plik = fopen("polska.txt", "rt");
  while ((tmp = fgetc(plik)) != EOF)
    if (tmp == '\n')
      n++;
  fclose(plik);
  return n;
}

int main()
{
  unsigned ile = ile_linii();
  cout << endl;
  Graf A(ile + 1);
  char n_plik[80] = "polska.txt";
  ifstream czytaj(n_plik);
  if (!czytaj)
  {
    cout << " #blad otwarcia pliku " << n_plik << endl;
    return 0;
  }

  cout << "\n\t- POLSKA - SIEC AUTOSTRAD -\n"
       << " > Program wyznacza najtansza siec autostrad.\n"
       << " (polaczenia z pliku polska.txt,lista miast z pliku miasta.txt)\n"
       << " algorytm Kruskala O(E*logE) + sortowanie babelkowe O(E^2)\n"
       << endl;

  unsigned v1 = 0, v2 = 0, waga = 0, i = 1;
  stringstream tmp, tmp2, tmp3;
  string linia, linia2;
  string::size_type position;
  do
  {
    getline(czytaj, linia);
    position = linia.find(" ");
    tmp << linia.substr(0, position);
    tmp >> v1; // wczytuje dane z pliku
    linia2 = linia.erase(0, position + 1);
    position = linia2.find(" ");
    tmp2 << linia2.substr(0, position);
    tmp2 >> v2;
    linia = linia2.erase(0, position + 1);
    position = linia.find(" ");
    tmp3 << linia.substr(0, position);
    tmp3 >> waga;
    A.Wstaw(i, v1, v2, waga); // i dodaje je do grafu
    linia.clear();
    linia2.clear();
    tmp.clear();
    tmp2.clear();
    tmp3.clear();
    position = 0;
    i++;
  } while (!czytaj.eof());
  czytaj.close();

  A.Sortowanie();
  A.Autostrady();

  cout << endl
       << endl;
  return 0;
}
