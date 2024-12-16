/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|          koder.cpp program do dekodowania RSA           |
|            wymaga podania klucza prywatnego             |
|                                                         |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>
#include <fstream>

using namespace std;

int d, n; // klucz prywatny

// algorytm Russian Peasant, do potegowania w celach RSA
// kod oparty jest o http://www.math.umbc.edu/~campbell/Math413Fall98/7-FermatThm.html
int powmod(int d, int e, int n)
{
    int accum = 1, i = 0, basepow2 = d;
    // Look at each bit of exp, low to high
    while ((e >> i) > 0)
    {
        // If the exponent bit of exp is 1 multiply by base^(2^i)
        if (((e >> i) & 1) == 1)
        {
            accum = (accum * basepow2) % n;
        }
        // In any event compute base^(2^i) for next i value
        basepow2 = (basepow2 * basepow2) % n;
        i = i + 1;
    }
    return accum;
}
//-----------------------------------

main()
{
    cout << "\n";
    cout << " **************************\n"
         << " ** Program deszyfrujacy **\n"
         << " **************************\n";

    char tab[200] = {""}; // tablica znakow
    int tab2[200];

    for (int i = 0; i < 200; i++)
    {
        tab2[i] = 0;
    }

    ifstream f("zaszyfrowane.txt"); // otwarcie pliku
    int i = 0;
    while (f >> tab2[i]) // wczytanie z pliku do tablicy
        i++;
    f.close(); // zamkniecie pliku

    cout << "\n\t:: zakodowany tekst:\n\t";
    for (int j = 0; j < i; j++)
    {
        cout << tab2[j] << " ";
    }

    cout << "\n\n";
    cout << ":: podaj klucz prywatny:\n"
         << " modul n: ";
    cin >> n;
    cout << " wykladnik d: ";
    cin >> d;
    cout << "\n";

    cout << "\n\t:: rozkodowany tekst:\n\t";
    // dekryptacja zgodnie ze wzorem M = X^D (mod N)
    for (int i = 0; i < 200; i++)
    {
        tab[i] = powmod(tab2[i], d, n);
    }

    for (int i = 0; i < 100; i++)
    {
        cout << tab[i];
    }

    cout << "\n\n";
}
