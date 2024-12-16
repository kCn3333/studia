/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|            7.cpp program do liczenia wartosci           |
|                       funkcji Eulera                    |
|       (wypisuje rowniez liczby wzglednie pierwsze)      |
|                                                         |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>

using namespace std;

unsigned long nwd(unsigned long a, unsigned long b)
{
    while (a != b)
    {
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}

unsigned long euler(unsigned long n, unsigned long tab[])
{
    int p = 0;
    for (int i = 1; i < n; i++)
    {
        if (nwd(i, n) == 1)
        {
            tab[p] = i;
            p++;
        }
    }
    return p;
}

main()
{
    unsigned long n;
    unsigned long *tab;

    cout << "\n\t-F-U-N-K-C-J-A--E-U-L-E-R-A-" << endl;

    cout << "\n\t--> podaj argument: ";
    cin >> n;

    tab = new unsigned long[n];

    cout << "\n\t--> wartosc funkcji dla " << n << " wynosi " << euler(n, tab) << endl
         << endl;

    cout << "--> liczby wzglednie pierwsze, mniejsze od " << n << endl
         << endl;
    for (int i = 0; i < n; i++)
    {
        if (tab[i])
            cout << tab[i] << "\t";
    }

    cout << endl
         << endl;
}
