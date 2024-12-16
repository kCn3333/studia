/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|   reprezentacja grafu za pomoca macierzy sasiedztwa     |
|                                                         |
|                                                         |
|---------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Graf
{
  unsigned V, E;      // ilosc wierzcholkow i krawedzi
  unsigned **GrafTab; // macierz

public:
  Graf(unsigned V1);
  bool Wstaw(unsigned v, unsigned u);
  bool Wypisz();
};

Graf::Graf(unsigned V1) : V(V1) // konstruktor
{
  GrafTab = new unsigned *[V]; // tworzy macierz VxV
  for (int i = 0; i < V; ++i)  // i wypelnia ja zerami
  {
    GrafTab[i] = new unsigned[V];
    for (int j = 0; j < V; ++j)
      GrafTab[i][j] = 0;
  }
}

bool Graf::Wstaw(unsigned v, unsigned u)
{
  if (GrafTab[v][u] > 0)
    return false; // już jest!
  ++GrafTab[v][u];
  ++GrafTab[u][v]; // krawędź symetryczna
}

bool Graf::Wypisz()
{
  if (V == 0)
    return false;
  cout << "\n\t -macierz sasiedztwa-\n";
  for (int i = 0; i < V; i++)
  {
    {
      for (int j = 0; j < V; j++)
        cout << "\t" << GrafTab[i][j];
    }
    cout << endl;
  }
}

int main()
{
  unsigned V = 5;
  cout << "\n\t --- reprezenatcja grafow poprzez macierz sasiedztwa ---\n\n";
  cout << "\t podaj ilosc wierzcholkow grafu (max 10) V=";
  cin >> V;
  Graf G(V);

  char n_plik[80] = "1.txt";
  cout << "\t podaj nazwe pliku do wczytania: ";
  cin >> n_plik;
  ifstream czytaj(n_plik);
  if (!czytaj)
  {
    cout << " #blad otwarcia pliku " << n_plik << endl;
    return 0;
  }

  int i = 0;
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
    G.Wstaw(v1, v2); // i dodaje je do macierzy
    linia.clear();
    linia2.clear();
    tmp.clear();
    position = 0;
  } while (!czytaj.eof());
  czytaj.close();

  G.Wypisz();

  cout << endl;
  return 0;
}
