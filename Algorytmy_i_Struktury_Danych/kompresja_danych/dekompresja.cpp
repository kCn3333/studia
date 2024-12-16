/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|               program do dekompresji danych             |
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

int dekompresuj(char *wejscie, char *wyjscie)
{
    FILE *wej, *wyj;

    if (!(wej = fopen(wejscie, "rb")))
    {
        cout << "\n #blad otwarcia pliku wejsciowego\n";
        return EXIT_FAILURE;
    }
    if (!(wyj = fopen(wyjscie, "wb")))
    {
        cout << "\n #blad otwarcia pliku wyjsciowego";
        return EXIT_FAILURE;
    }

    unsigned int nrpoz, i, j, a, dl;

    fread(&nrpoz, 2, 1, wej);
    fseek(wej, -nrpoz * 4, SEEK_END); // ustaw na poczatek info
    for (i = 0; i < nrpoz; i++)
    {
        fread(&(pozycja[i]), 4, 1, wej);
    } // wczytaj info

    fseek(wej, 2, SEEK_SET);
    long pozplik = 2, rozmiar_pliku = size(wej);
    j = 0;

    while (pozplik < rozmiar_pliku - nrpoz * 4)
    {
        putc(a = getc(wej), wyj);
        if (pozplik == pozycja[j])
        {
            j++;
            fread(&dl, 2, 1, wej);
            pozplik += 2;
            for (i = 0; i < dl; i++)
                putc(a, wyj);
        }
        pozplik++;
    }

    fclose(wyj);
    fclose(wej);
    return 0;
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cout << "\n program do dekompresji \nskladnia " << argv[0] << " [plik_wejsciowy] [plik_wyjscowy]\n";
        return 0;
    }

    else if (argc == 1)
    {
        argv[2] = "zdekompresowany.txt";
    }

    if (dekompresuj(argv[1], argv[2]) == 0)
        cout << "\n #dekompresja zakonczona pomyslnie\n";

    return 0;
}
