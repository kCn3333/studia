/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|        4.cpp program sprawdzajacy czy dany punkt        |
|                   nalezy do wielokata                   |
|                                                         |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>

using namespace std;

main()
{
    int n = 0;  // liczba wierzcholkow
    float x, y; // wspolrzedne punktu do sprawdzenia
    while (n < 3)
    {
        cout << "====================================" << endl;
        cout << "Podaj liczbe wierzcholkow wielokata: ";
        cin >> n;
        if (n < 3)
        {
            cout << "wielokat musi posiadac przynajmniej 3 wierzcholki" << endl;
        }
    }
    float X[n - 1], Y[n - 1]; // tablice wspolrzednych wierzcholkow
    cout << " -> podaj wspolrzedne wierzcholkow\n"
         << "			| zaczynajac od tego najwyzej polozonego na osi OY\n"
         << "			| i dalej zgodnie z ruchem wskazowek zegara" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "wierzcholek " << i + 1 << "  x=";
        cin >> X[i];
        cout << "               y=";
        cin >> Y[i];
    }
    while (1)
    {
        cout << "podaj wspolrzedne punktu do sprawdzenia: x=";
        cin >> x;
        cout << "                                         y=";
        cin >> y;

        bool check = false; // check - nieparzysta liczba przeciec
        int j = 0;
        for (int i = 0; i < n; i++)
        {
            j++;
            if (j == n)
                j = 0;
            if (Y[j] >= y && Y[i] < y || Y[j] < y && Y[i] >= y)              // jezeli polprosta wychodzaca z punktu do sprawdzenia
            {                                                                // przecina boki wielokata nieparzysta ilosc razy to punkt ten
                if ((X[i] + (y - Y[i]) / (Y[j] - Y[i]) * (X[j] - X[i])) < x) // lezy wewnatrz wielokata
                    check = true;
            }
        }
        if (check)
            cout << " :: punkt (" << x << "," << y << ")" << " nalezy do tego wielokata" << endl;
        else
            cout << " :: punkt (" << x << "," << y << ")" << " nie nalezy do tego wielokata" << endl;
    }
}
