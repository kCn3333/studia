/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|                10.cpp wyszukiwanie wzorca               |
|                algorytmy: KMP, brut force,              |
|             Booyera i Moore'a, Rabina i Karpa           |
|                                                         |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

//-------------------------------------------------------
// 						      KMP
// funkcja generujaca tablice przesuniec dla kmp
void next_kmp(string wzor, int *next)
{
  int size_w = strlen(wzor.c_str()); // dlugosc wzoru
  int i, j;

  next[0] = -1;

  for (i = 0, j = -1; i < (size_w - 1); i++, j++, next[i] = j)
  {
    while ((j >= 0) && (wzor[i] != wzor[j]))
      j = next[j];
  }
}

int kmp(string wzor, string dane)
{
  int counter = 0; // licznik porownan

  int size_d = strlen(dane.c_str()); // dlugosc danych
  int size_w = strlen(wzor.c_str()); // dlugosc wzorca
  int i, j;

  int *next = new int[size_w]; // tablica przesuniec
  next_kmp(wzor, next);

  for (i = 0, j = 0; (i < size_d) && (j < size_w); i++, j++)
  {
    while ((j >= 0) && (dane[i] != wzor[j]))
    {
      counter++;
      j = next[j];
    }
  }

  delete next; // usuwa tablice przesuniec

  if (j == size_w)
  {
    cout << "\n kmp# znaleziono na pozycji " << i - size_w << "\n";
    return counter;
  }
  else
  {
    cout << "\n kmp# nie znaleziono\n";
    return counter;
  }
}

//-------------------------------------------------------
//					      BRUTE FORCE
int brute_force(string wzor, string dane)
{
  int counter = 0; // licznik porownan

  int i, j;
  int size_w = strlen(wzor.c_str()); // dlugosc wzorca
  int size_d = strlen(dane.c_str()); // dlugosc danych

  for (i = 0; i <= size_d - size_w; i++)
  {
    for (j = 0; j < size_w; ++j)
    {
      if (wzor[j] != dane[i + j])
      {
        counter++;
        break;
      }
    }
    if (j > size_w - 1)
    {
      cout << "\n brute_force# znaleziono na pozycji " << i << "\n";
      return counter;
    }
  }

  cout << "\n brute_force# nie znaleziono\n";
  return counter;
}

//-------------------------------------------------------
//					      BOYER MOORE
// zwraca kod ascii znaku
int index(char znak)
{
  int numer = (int)znak;
  return numer;
}

int boyer_moore(string wzor, string dane)
{
  int counter = 0; // licznik porownan

  int shift[256], i, j, s;           // tablica przesuniec shift
  int size_w = strlen(wzor.c_str()); // dlugosc wzorca
  int size_d = strlen(dane.c_str()); // dlugosc danych

  for (int x = 0; x < 256; x++)
    shift[x] = size_w;
  for (int y = 0; y < size_w; y++)
    shift[index(wzor[y])] = size_w - (y + 1);

  for (i = size_w - 1, j = size_w - 1; j >= 0; i--, j--)
  {
    while (wzor[j] != dane[i])
    {
      counter++;
      s = shift[index(dane[i])];

      if ((size_w - j) > s)
        i += size_w - j;
      else
        i += s;
      if (i >= size_d) // = ?
      {
        cout << "\n boyer_moore# nie znaleziono\n";
        return counter;
      }
      j = size_w - 1;
    }
  }
  cout << "\n boyer_moore# znaleziono na pozycji " << i + 1 << "\n";
  return counter;
}

//-------------------------------------------------------
//					       RABIN KARP
int rabin_karp(string wzor, string dane)
{
  int counter = 0; // licznik porownan

  int h = 1, p = 0, t = 0, c;
  int i, j;
  const int q = 127;
  const int d = 256;

  int size_d = strlen(dane.c_str());
  int size_w = strlen(wzor.c_str());
  p = t = 0;

  for (i = 1; i < size_w; i++)
    h = (h * d) % q;
  for (i = 0; i < size_w; i++)
  {
    p = (d * p + wzor[i]) % q;
    t = (d * t + dane[i]) % q;
  }
  for (i = 0; i < size_d - size_w; i++)
  {
    if (p == t)
    {
      for (j = 0; j < size_w; j++)
        if (wzor[j] != dane[i + j])
        {
          counter++;
          break;
        }
      if (j == size_w)
      {
        cout << "\n rabin_karp# znaleziono na pozycji " << i << "\n";
        return counter;
      }
    }
    t = ((d * (t - dane[i] * h) + dane[i + size_w]) % q + q) % q;
  }

  cout << "\n rabin_karp# nie znaleziono\n";
  return counter;
}

//-------------------------------------------------------

int main(int argc, char *argv[])
{
  string wzor, linia, tekst;
  double czas[4] = {0, 0, 0, 0};  // wyniki pomiaru czasu
  int porownan[4] = {0, 0, 0, 0}; // wyniki pomiaru liczby porownan
  clock_t start, stop;            // poczatek, koniec pomiaru czasu
  int menu;

  if (argc < 2)
  {
    cout << "\n skladnia " << argv[0] << " [plik_wejsciowy]\n";
    cout << "\n nie podano nazwy pliku wejsciowego\n"
         << " - zostanie uzyty plik dane.txt\n";

    argv[1] = "dane.txt";
  }

  ifstream plik(argv[1]);
  // otwarcie pliku
  if (!plik.is_open())
  {
    cout << "\n #blad otwarcia pliku " << argv[1] << "\n";
    return EXIT_FAILURE;
  }
  else
    cout << "\n [ wyszukiwanie wzorca w pliku " << argv[1] << " ]\n\n";

  while (!plik.eof())
  {
    getline(plik, linia, '\0');
    tekst += linia; // wczytanie danych z pliku do stringa
  }
  plik.close(); // zamkniecie pliku

  int size = strlen(tekst.c_str());

  cout << "  podaj wzorzec ktory wyszukac: ";
  cin >> wzor;

  cout << "\n __________________________________________\n"
       << " 1 <-- algorytm Knutha-Morrisa-Pratta (KMP)\n"
       << " 2 <-- algorytm Boyer'a Moore'a\n"
       << " 3 <-- algorytm Rabina Karpa\n"
       << " 4 <-- algorytm brute force\n"
       << " 5 <-- porownanie\n"
       << " 0 <-- wyjscie\n";

  while (1)
  {
    cout << "\n wybor: ";
    cin >> menu;

    switch (menu)
    {
    case 0:
    { // WYJSCIE
      cout << "\n\t ::KONIEC::\n\n";
      return 0;
    }
    case 1:
    { // KMP
      start = clock();
      porownan[0] = kmp(wzor, tekst);
      stop = clock();
      czas[0] = ((double)(stop - start) / CLOCKS_PER_SEC);
      break;
    }
    case 2:
    { // BOYER MOORE
      start = clock();
      porownan[1] = boyer_moore(wzor, tekst);
      stop = clock();
      czas[1] = ((double)(stop - start) / CLOCKS_PER_SEC);
      break;
    }
    case 3:
    { // RABIN KARP
      start = clock();
      porownan[2] = rabin_karp(wzor, tekst);
      stop = clock();
      czas[2] = ((double)(stop - start) / CLOCKS_PER_SEC);
      break;
    }
    case 4:
    { // BRUTE FORCE
      start = clock();
      porownan[3] = brute_force(wzor, tekst);
      stop = clock();
      czas[3] = ((double)(stop - start) / CLOCKS_PER_SEC);
      break;
    }
    case 5:
    {
      cout << "\n wyszukiwanie wzoru '" << wzor << "'"
           << "\n w tekscie z pliku " << argv[1] << " (" << size << " znakow)";
      cout << "\n ---------------------------------------";
      cout << "\n  - algorytm -\t - czas -  - porownan -";
      cout << "\n kmp\t\t| " << czas[0] << " \t  | " << porownan[0];
      cout << "\n boyer_moore\t| " << czas[1] << " \t  | " << porownan[1];
      cout << "\n rabin_karp\t| " << czas[2] << " \t  | " << porownan[2];
      cout << "\n brute_force\t| " << czas[3] << " \t  | " << porownan[3];
      cout << "\n ---------------------------------------\n";
      break;
    }
    }
  }
}
