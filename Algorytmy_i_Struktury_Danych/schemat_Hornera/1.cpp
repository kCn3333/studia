/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|            1.cpp program do liczenia wartosci           |
|                   wielomianu w punkcie                  |
|            (z wykorzystaniem schematu Hornera)          |
|                                                         |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>

using namespace std;

main()
{
    int n;   // stopien wielomianu
    float x; // argument x0
    cout << "podaj stopien wielomianu, ktorego chcesz obliczyc wartosc: ";
    cin >> n;
    float w[n]; // tablica czynnikow wielomianu
    cout << "-------------------------------------------------------------------------" << endl;
    cout << ">>podaj czynniki wielomianu, zaczynajac od tego przy najwyzszej potedze<<" << endl;

    for (int i = n; i >= 0; i--)
    {
        cout << "A" << i << " = "; // wczytanie czynnikow wielomianu
        cin >> w[i];
    }

    cout << " :: W(x) = ";

    for (int i = n; i >= 2; i--)
    {
        if (w[i] != 0)
            cout << w[i] << "x^" << i << " + "; // wypisanie wielomianu
        else
            continue;
    }
    if (w[1] != 0)
        cout << w[1] << "x + ";
    if (w[0] != 0)
        cout << w[0];

    cout << endl
         << "podaj x, dla ktorego policzyc wartosc W(x): ";
    cin >> x;

    for (n; n >= 1; n--)
    {
        w[n - 1] = ((w[n] * x) + w[n - 1]); // reurencja - schemat hornera
    }

    cout << " :: " << "W(" << x << ") = " << w[0] << endl;
}
