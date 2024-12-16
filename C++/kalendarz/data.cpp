#include "data.h"

using namespace std;

int Przestepny(int rok)
{
    if (((rok % 4) == 0) && ((rok % 100) != 0) || ((rok % 400) == 0))
        return 1;
    else
        return 0;
}
//==============================================================================
// d-day, m-month, y-year
int DzienTyg(int d, int m, int y)
{
    int i;
    int x = 0;
    // liczy dni w latach od 1 roku do roku y-1
    // i bierze reszte z dzielenia przez 7
    for (i = 1; i < y; i++)
        x += (7 * 31 + 4 * 30 + 28 + Przestepny(i)) % 7;
    // zlicza dni w miesiacach w roku y, od stycznia do miecica m-1
    for (i = 1; i < m; i++)
    {
        // jesli luty to licz 28 dni, jesli rok przestepny to dodaj 1
        if (i == 2)
            x += 28 + Przestepny(y);
        else
            // 7 i 8 miesiac maja po 31 dni
            // wiec trzeba bylo zrobic dpowiednie zalozenia
            if (i <= 7)
                x += 30 + (i % 2);
            else
                x += 31 - (i % 2);
    }
    // do uzyskanej wartosci dodaje dni d i daje modulo 7
    return (x + d) % 7;
}
//=============================================================================
void wypis(int i)
{
    if (i == 1)
    {
        cout << "\t";
    }
    else if (i == 2)
    {
        cout << "\t\t";
    }
    else if (i == 3)
    {
        cout << "\t\t\t";
    }
    else if (i == 4)
    {
        cout << "\t\t\t\t";
    }
    else if (i == 5)
    {
        cout << "\t\t\t\t\t";
    }
    else if (i == 6)
    {
        cout << "\t\t\t\t\t\t";
    }
}
//=============================================================================
int ile_dni(int dod[2][13], int d1, int m1, int y1, int d2, int m2, int y2)
{
    int ile = 0, s = 0;
    if (y1 > y2)
    {
        s = (y1 - y2);
        if (s)
        { // doddaje roznice w latach jesli wieksza niz 1
            for (int i = 0; i <= s; i++)
            {
                if (Przestepny(y2 + i))
                {
                    ile += 366;
                    i++;
                }
                else
                {
                    ile += 365;
                    i++;
                }
            }
        }
        ////////////////////////////
        if (m1 > m2)
        { // dodaj caly rok
            if (Przestepny(y2))
            {
                ile += 366;
            }
            else
                ile += 365;
            ///////////////////////////
            if (Przestepny(y2))
            {
                s = ((dod[1][m2]) - (dod[1][m2 - 1]));
            }
            else
                s = ((dod[0][m2]) - (dod[0][m2 - 1]));
            ile += (s - d2);                        // dni do konca m2
            ile += d1;                              // dni w m1
            for (int i = 1; i < (m1 - m2 - 1); i++) // dni pomiedzy m1 a m2
            {
                if (Przestepny(y2))
                {
                    s = ((dod[1][m2 + i]) - (dod[1][m2 + i - 1]));
                }
                else
                    s = ((dod[0][m2 + i]) - (dod[0][m2 + i - 1]));
                ile += s;
            }
            return ile;
        }
        ////////////////////////////
        if (m2 == m1)
        {
            ile += (d1 - d2);
            return ile;
        }
        ////////////////////////////
        else
        {
            if (Przestepny(y2))
            {
                s = ((dod[1][m2]) - (dod[1][m2 - 1]));
            }
            else
                s = ((dod[0][m2]) - (dod[0][m2 - 1]));
            ile += (s - d2);
            ile += d1;
            for (int i = 1; m2 <= 12; i++)
            {
                if (Przestepny(y2))
                {
                    s = ((dod[1][m2 + i]) - (dod[1][m2 + i - 1]));
                }
                else
                    s = ((dod[0][m2 + i]) - (dod[0][m2 + i - 1]));
                ile += s;
            }
            for (int i = 1; i < m1; i++)
            {
                if (Przestepny(y2))
                {
                    s = ((dod[1][m1 + i]) - (dod[1][m1 + i - 1]));
                }
                else
                    s = ((dod[0][m1 + i]) - (dod[0][m1 + i - 1]));
                ile += s;
            }
            return ile;
        }
    }
    if (y1 == y2)
    {
        if (m1 > m2)
        {
            if (Przestepny(y2))
            {
                s = ((dod[1][m2]) - (dod[1][m2 - 1]));
            }
            else
                s = ((dod[0][m2]) - (dod[0][m2 - 1]));
            ile += (s - d2);                        // dni do konca m2
            ile += d1;                              // ile dni w m1
            for (int i = 1; i < (m1 - m2 - 1); i++) // dni pomiedzy m1 a m2
            {
                if (Przestepny(y2))
                {
                    s = ((dod[1][m2 + i]) - (dod[1][m2 + i - 1]));
                }
                else
                    s = ((dod[0][m2 + i]) - (dod[0][m2 + i - 1]));
                ile += s;
            }
            return ile;
        }
        if (m1 == m2)
        {
            if (d1 > d2)
                return d1 - d2;
            if (d2 == d1)
                return 0;
            else
                return d2 - d1;
        }
        else
        {
            if (Przestepny(y2))
            {
                s = ((dod[1][m1]) - (dod[1][m1 - 1]));
            }
            else
                s = ((dod[0][m1]) - (dod[0][m1 - 1]));
            ile += (s - d1);
            ile += d2;
            for (int i = 1; i < (m2 - m1 - 1); i++)
            {
                if (Przestepny(y2))
                {
                    s = ((dod[1][m1 + i]) - (dod[1][m1 + i - 1]));
                }
                else
                    s = ((dod[0][m1 + i]) - (dod[0][m1 + i - 1]));
                ile += s;
            }
            return ile;
        }
    }
    else
        return ile_dni(dod, d2, m2, y2, d1, m1, y1);
}

//=============================================================================
void dodaj(int k, int d1, int m1, int rok, int dod[2][13])
{
    int pom1 = d1;
    int j;
    if (Przestepny(rok))
        j = 1;
    else
        j = 0;

    int dkm = dod[j][m1] - dod[j][m1 - 1] - d1; // dni do konca miesiaca
    int dkr = dkm + (dod[j][12] - dod[j][m1]);  // dni do konca roku

    if (k > dkr)
    {
        k -= dkr;
        rok++;
        d1 = 1;
        m1 = 1;
    }
    if (Przestepny(rok))
        j = 1;
    else
        j = 0;

    while (k > dod[j][12])
    {
        k -= dod[j][12];
        rok++;
        if (Przestepny(rok))
            j = 1;
        else
            j = 0;
    }

    if (k == dkm)
    {
        m1++;
        d1 = 1;
    }
    if (k > dkm)
    {
        m1++;
        k -= dkm;
        while (k > (dod[j][m1] - dod[j][m1 - 1]))
        {
            k -= (dod[j][m1] - dod[j][m1 - 1]);
            m1++;
        }
        d1 = k;
    }
    else

        d1 = pom1 + k;

    cout << "\n\t" << d1 << "." << m1 << "." << rok;
}

string szukaj(string imie)
{
    string kiedy;

    ifstream odczyt("im.txt");
    if (!odczyt.is_open())
        throw -1;

    string linia, linia2;

    for (int i = 0; i <= 730; i++)
    {
        getline(odczyt, linia);
        linia.erase(5);
        getline(odczyt, linia2);
        if (linia2.find(imie, 0) != (string::npos))
            kiedy += linia + " ";
    }
    return kiedy;
}
