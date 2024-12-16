#include <iostream>
#include <string>

using namespace std;

int nwd(int a, int b)
{
    int t;
    while (b != 0)
    {
        t = b; // NWD dwoch liczb
        b = a % b;
        a = t;
    }
    return a;
}

int odwr_mod(int a, int n)
{
    int a0, n0, p0, p1, q, r, t;
    p0 = 0;
    p1 = 1;
    a0 = a;
    n0 = n;
    q = n0 / a0;
    r = n0 % a0;
    while (r > 0)
    {
        t = p0 - q * p1; // odwrotnosc modulo
        if (t >= 0)
            t = t % n;
        else
            t = n - ((-t) % n);
        p0 = p1;
        p1 = t;
        n0 = a0;
        a0 = r;
        q = n0 / a0;
        r = n0 % a0;
    }
    return p1;
}

int p, q, n, e, d;
// Procedura generowania kluczy RSA
//---------------------------------
void klucze_RSA()
{
    const int tp[10] = {3, 11, 13, 17, 19, 23, 29, 31, 37, 41}; // tablica z liczbami pierwszymi
    int phi;
    cout << "Generowanie kluczy RSA\n"
            "----------------------\n\n";
    do // generujemy dwie różne, losowe liczby pierwsze
    {
        p = tp[rand() % 10];
        q = tp[rand() % 10];
    } while (p == q);
    phi = (p - 1) * (q - 1);
    n = p * q;
    // wykładniki e i d
    for (e = 3; nwd(e, phi) != 1; e += 2)
        ;
    d = odwr_mod(e, phi);
    //  wypisanie kluczy
    cout << "KLUCZ PUBLICZNY\n"
            "wykladnik e = "
         << e
         << "\n    modul n = " << n
         << "\n\nKLUCZ PRYWATNY\n"
            "wykladnik d = "
         << d << endl;
}
// przy potegowaniu w celach RSA uzywa sie tzw. algorytmu Russian Peasant
// opierajacego sie na bitowych operacjach i dzieki temu - duplikacji zamiast mnozenia
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

// ********************
// ** Program glowny **
// ********************
main()
{

    cout << "----------------------\n";
    klucze_RSA();
    cout << "\n";

    char tab[200] = {""}; // tablica znakow
    int tab1[200];
    int tab2[200];

    for (int i = 0; i < 200; i++)
    {
        tab2[i] = 0;
    }

    cout << "\t-----------------------------------------------\n";
    cout << "\t:: podaj tekst do zakodowania (max 200 znakow) _\n\t";
    string s1;
    getline(cin, s1); // wczytanie tekstu do stringa
    cout << "\n";

    int i = 0;
    cout << "\n\t:: zakodowany tekst:\n\t";
    while (s1[i] != '\0') // do puki string sie nie skonczy
    {
        // kazda liczbe kodujemy uzywajac formuly RSA dla kazdego znaku: blok^E mod N
        tab2[i] = powmod(int(s1[i]), e, n); // przypisanie do tablicy intow
        cout << " " << tab2[i];
        i++;
    }

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

    cout << endl;
}
