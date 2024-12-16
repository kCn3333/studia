/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|               program do kompresji danych               |
|                                                         |
|                                                         |
|--------------------------------------------------------*/

#include <sys/stat.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

const int ile_pozycji = 1024;
long pozycja[ile_pozycji];

int size(FILE *w)
{
  struct stat tmpStat;
  fstat(fileno(w), &tmpStat);
  return tmpStat.st_size;
}

int kompresuj(char *wejscie, char *wyjscie)
{
  FILE *wej, *wyj;

  if (!(wej = fopen(wejscie, "rb")))
  {
    cout << "\n #blad otwarcia pliku wejsciowego\n";
    return EXIT_FAILURE;
  }
  if (!(wyj = fopen(wyjscie, "wb")))
  {
    fclose(wej);
    cout << "\n #blad otwarcia pliku wyjsciowego\n";
    return EXIT_FAILURE;
  }

  unsigned int i = 0, nrpoz = 0, dl = 0; // dlugoc ciagu tych samych bajtow bez pierwszego
  int a = -1, b;
  long pozplik = 2; // ile juz zapisanych i nr od zera bajtu do odczytania

  fwrite(&i, 2, 1, wyj); // 2 bajty: ilosc spakowanych ciagow

  while ((b = getc(wej)) != EOF)
  {
    if (b != a)
    {
      a = b;
      putc(b, wyj);
      pozplik++;
    }
    else
    {
      dl = 1;
      while ((b = getc(wej)) == a)
        dl++; // czytaj powtarzajace sie bajty
      if (dl >= 7)
      {
        pozycja[nrpoz] = pozplik - 1;
        nrpoz++;
        fwrite(&dl, 2, 1, wyj);
        pozplik += 2;
      } // spakowanie ciagu
      else
      {
        for (i = 0; i < dl; i++)
          putc(a, wyj);
        pozplik += dl;
      } // nie warto pakowac
      if (b >= 0)
      {
        putc(b, wyj);
        pozplik++;
      }
      a = b;
    }
  }

  for (i = 0; i < nrpoz; i++)
    fwrite(&pozycja[i], 4, 1, wyj); // zapis info
  rewind(wyj);
  fwrite(&nrpoz, 2, 1, wyj);

  float stopien = (1 - ((float)size(wyj) / (float)size(wej))) * 100;

  if ((int)(stopien + 0.5) > (int)stopien)
    stopien = (int)stopien + 1;
  else
    stopien = (int)stopien;

  cout << "\n stopien kompresji " << stopien << "%";
  cout << "\n ilosc skompresowanych ciagow " << nrpoz + 1 << "\n\n";

  fclose(wyj);
  fclose(wej);
  return 0;
}

int main(int argc, char *argv[])
{

  if (argc < 1)
  {
    cout << "\n program do kompresji \nskladnia " << argv[0] << " [plik_wejsciowy] [plik_wyjscowy]\n";
    return 0;
  }

  else if (argc == 1)
  {
    argv[2] = "skompresowany.txt";
  }

  if (kompresuj(argv[1], argv[2]) == 0)
    cout << "\n #kompresja zakonczona pomyslnie\n";

  return 0;
}
