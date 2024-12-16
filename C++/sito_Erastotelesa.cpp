/*
   sito Eratostelesa

   --------------------------
   Pawel Kwiecien

   */

#include <iostream>

using namespace std;

main()
{
    const unsigned MAX = 1000000;
    bool t[MAX + 1];
    unsigned i, w, g;
    char s[1];

    cout << "Wyszukiwanie liczb pierwszych sitem Eratostenesa\n"
            "------------------------------------------------\n"
            " :: Podaj granice = ";
    cin >> g;
    cout << endl;
    if (g > MAX)
        cout << "Granica zbyt wielka\n";
    else
    {
        for (i = 2; i <= g; i++)
            t[i] = true;
        for (i = 2; i <= g; i++)
        {
            w = i + i;
            while (w <= g)
            {
                t[w] = false;
                w += i;
            }
        }
        for (i = 2; i <= g; i++)
            if (t[i])
                cout << " " << i;
        cout << endl;
    }
}
