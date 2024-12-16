/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|            koder.cpp program do kodowania RSA           |
|             wymaga podania klucza publicznego           |
|                                                         |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>
#include <fstream>

using namespace std;

int e, n; // klucz publiczny

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

    ofstream f;
    f.open("zaszyfrowane.txt"); // otwarcie pliku
    if (!f)
    {
        cout << "Nie udalo sie otworzyc pliku 'zaszyfrowane.txt' do zapisu" << endl;
        return 1;
    }

    int tab[200];
    string s1;

    for (int i = 0; i < 200; i++) // czyszczenie tablicy
    {
        tab[i] = 0;
    }

    cout << "\n";
    cout << " ************************\n"
         << " ** Program szyfrujacy **\n"
         << " ************************\n";

    cout << "\n\t-----------------------------------------------\n";
    cout << "\t:: podaj tekst do zakodowania (max 200 znakow) _\n\t";

    getline(cin, s1); // wczytanie tekstu do stringa
    cout << "\n";
    cout << ":: podaj klucz publiczny:\n"
         << " modul n: ";
    cin >> n; // wczytanie klucza publicznego
    cout << " wykladnik e: ";
    cin >> e;
    cout << "\n";

    int i = 0;
    cout << "\n\t:: zakodowany tekst:\n\t";

    while (s1[i] != '\0') // do puki string sie nie skonczy
    {
        // kodowanie RSA dla kazdego znaku: znak^e mod n
        tab[i] = powmod(int(s1[i]), e, n); // przypisanie do tablicy intow
        cout << " " << tab[i];
        f << tab[i] << " "; // zapis do pliku
        i++;
    }

    f.close(); // zamkniecie pliku
    cout << "\n\n:: zakodowany tekst znajduje sie w pliku 'zakodowane.txt' w biezacym katalogu\n\n";
}
