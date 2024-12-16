/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|        program wyznacza najkrotsze drogi z Krakowa      |
|             do poszczegolnych miast wojewodzkich        |
|           wykorzystujac algorytm Floyda-Warshalla       |
|                                                         |
|---------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define N 999999 // "nieskonczonosc"
#define MIAST 16 // ilosc miast

using namespace std;

class Graf
{
  unsigned V, E;            // ilosc wierzcholkow i krawedzi
  unsigned **GrafTab;       // macierz polaczen
  unsigned **RoutingMatrix; // macierz kierowania ruchem

public:
  Graf(unsigned V1);
  bool Wstaw(unsigned v, unsigned u, unsigned waga);
  void Droga();
  void Wypisz(unsigned v1, unsigned v2);
};

Graf::Graf(unsigned V1) : V(V1) // konstruktor
{
  GrafTab = new unsigned *[V + 1];       // tworzy macierz VxV
  RoutingMatrix = new unsigned *[V + 1]; // i macierz routingu
  for (int i = 0; i <= V; i++)           // i wypelnia je zerami
  {
    GrafTab[i] = new unsigned[V + 1];
    RoutingMatrix[i] = new unsigned[V + 1];
    for (int j = 0; j <= V; j++)
    {
      GrafTab[i][j] = 0;
      RoutingMatrix[i][j] = 0;
    }
  }
}

bool Graf::Wstaw(unsigned v, unsigned u, unsigned waga)
{
  if (GrafTab[v][u] > 0)
    return false; // już jest!
  GrafTab[v][u] = waga;
  RoutingMatrix[v][u] = u;
  GrafTab[u][v] = waga;
  RoutingMatrix[u][v] = v; // krawedz symetryczna
}

void Graf::Droga()
{
  for (int i = 1; i <= V; i++)
    for (int j = 1; j <= V; j++)
      if (GrafTab[i][j] == 0 && i != j)
        GrafTab[i][j] = N; // gdy nie ma drogi bezposdredniej wstawiamy N

  for (int x = 1; x <= V; x++)
    for (int y = 1; y <= V; y++) // algorytm Floyda-Warshalla
      for (int z = 1; z <= V; z++)
        if ((GrafTab[y][x] + GrafTab[x][z]) < GrafTab[y][z])
        {
          GrafTab[y][z] = GrafTab[y][x] + GrafTab[x][z];
          RoutingMatrix[y][z] = x;
        }
}

string miasto(int); // zapowiedz funkcji miasto()

void Graf::Wypisz(unsigned v1, unsigned v2)
{
  unsigned tmp, tmp2;
  tmp = RoutingMatrix[v1][v2];
  cout << " |" << miasto(v1) << " - " << miasto(v2) << " " << GrafTab[v1][v2] << " km\n";
  cout << "\n\t" << miasto(v2);
  if (tmp != v2)
    cout << " -" << GrafTab[tmp][v2] << "-> " << miasto(tmp);
  while (RoutingMatrix[v1][tmp] != tmp)
  {
    tmp2 = RoutingMatrix[v1][tmp]; // wypisuje trase z V1 do V2
    cout << " -" << GrafTab[tmp2][tmp] << "-> " << miasto(tmp2);
    tmp = tmp2;
  }
  cout << " -" << GrafTab[tmp][v1] << "-> " << miasto(v1);
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

int main()
{
  unsigned V = MIAST;
  Graf G(V);

  char n_plik[80] = "polska.txt";
  ifstream czytaj(n_plik);
  if (!czytaj)
  {
    cout << " #blad otwarcia pliku " << n_plik << endl;
    return 0;
  }
  cout << "\n\t- POLSKA SIEC SWIATLOWODOWA -";
  cout << "\n Program podaje najkrotsze polaczenia Krakowa z pozostalymi miastami wojewodzkimi.";
  cout << "\n (polaczenia z pliku polska.txt,lista miast z pliku miasta.txt)\n";

  unsigned v1 = 0, v2 = 0, waga = 0;
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
    G.Wstaw(v1, v2, waga); // i dodaje je do grafu
    linia.clear();
    linia2.clear();
    tmp.clear();
    tmp2.clear();
    tmp3.clear();
    position = 0;
  } while (!czytaj.eof());
  czytaj.close();

  G.Droga();

  for (int i = 1; i <= V; i++)
    if (i != 6)
    {
      cout << "\n _________\n";
      G.Wypisz(6, i); // wypisuje polaczenia Krakowa z pozostalymi miastami
    }
  cout << endl
       << endl;
  return 0;
}
