#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <fstream>

using namespace std;

class data
{
public:
    int dd;  // dzien
    int mm;  // miesiac
    int yy;  // rok
    int d_y; // dzien roku
    int d_m; // dni w danym miesiacu
    int d_t; // dzien tygodnia
    int p;   // czy rok przestepny

    string dzien;
    string imieniny;
    string swieto;

    int co_dzis()
    {
        // kiedy wielkanoc
        int d, f, year, p1, p2;
        int a = yy % 19;
        int b = yy % 4;
        int c = yy % 7;
        int m = 0, n = 0;

        year = (yy - (yy % 100)) / 100;
        if (year == 17)
        {
            m = 23;
            n = 3;
        }
        else if (year == 18)
        {
            m = 23;
            n = 4;
        }
        else if (year == 19)
        {
            m = 24;
            n = 5;
        }
        else if (year == 20)
        {
            m = 24;
            n = 5;
        }
        else if (year == 21)
        {
            m = 24;
            n = 6;
        }

        d = (19 * a + m) % 30;
        f = (2 * b + 4 * c + 6 * d + n) % 7; // kiedy wielkanoc m.n
        p1 = d + f + 22;
        p2 = d + f - 9;
        if (p1 <= 31)
        {
            p1 = n;
            m = 3;
        }
        else if ((a <= 11) && ((p2 == 25) || (p2 == 26)))
        {
            n = 19;
            m = 4;
        }
        else
        {
            n = p2;
            m = 4;
        }

        ifstream plik("im.txt");
        if (!plik.is_open())
            throw -1;

        if (dd == 29 && mm == 2)
        {
            imieniny = "Lecha, Lutomira";
            return 0;
        }

        for (int i = 0; i < d_y; i++)
        {
            getline(plik, swieto);
            swieto.erase(0, 5);
            getline(plik, imieniny);
        }

        if (mm == m && dd == n)
        {
            swieto = "Wielkanoc";
        }

        return 0;
    }

    void zapamietaj(string data)
    {
        string::size_type position = 0;
        position = data.find(".");
        stringstream d;
        d << data.substr(0, position);
        stringstream m;
        m << data.substr(position + 1, position + 3);
        stringstream y;
        y << data.substr(position + 5);

        d >> dd;
        m >> mm;
        y >> yy;
    }

    void przestepny()
    {
        if (((yy % 4) == 0) && ((yy % 100) != 0) || ((yy % 400) == 0))
            p = 1;
        else
            p = 0;
    }

    void DzienTyg()
    {
        int i;
        int x = 0;
        // liczy dni w latach od 1 roku do roku y-1
        // i bierze reszte z dzielenia przez 7
        for (i = 1; i < yy; i++)
            x += (7 * 31 + 4 * 30 + 28 + Przestepny(i)) % 7;
        // zlicza dni w miesiacach w roku y, od stycznia do miecica m-1
        for (i = 1; i < mm; i++)
        {
            // jesli luty to licz 28 dni, jesli rok przestepny to dodaj 1
            if (i == 2)
                x += 28 + p;
            else
                // 7 i 8 miesiac maja po 31 dni
                // wiec trzeba bylo zrobic dpowiednie zalozenia
                if (i <= 7)
                    x += 30 + (i % 2);
                else
                    x += 31 - (i % 2);
        }
        // do uzyskanej wartosci dodaje dni d i daje modulo 7
        d_t = (x + dd) % 7;
    }

    void IleDni(int dod[2][13])
    {

        if (p)
        {
            d_m = ((dod[1][mm]) - (dod[1][mm - 1]));
        }
        else
            d_m = ((dod[0][mm]) - (dod[0][mm - 1]));

        if (p)
        {
            d_y = (dod[1][mm - 1] + dd);
        }
        else
            d_y = (dod[0][mm - 1] + dd);
    }

    void dodaj(int ile, int dod[2][13])
    {
        int pom1 = dd;

        int dkm = d_m - dd;         // dni do konca miesiaca
        int dkr = dod[p][12] - d_y; // dni do konca roku

        if (ile > dkr)
        {
            ile -= dkr;
            yy++;
            dd = 1;
            mm = 1;
        }

        while (ile > dod[p][12])
        {
            ile -= dod[p][12];
            yy++;
        }

        if (ile == dkm)
        {
            mm++;
            dd = 1;
        }
        if (ile > dkm)
        {
            mm++;
            ile -= dkm;
            while (ile > (dod[p][mm] - dod[p][mm - 1]))
            {
                ile -= (dod[p][mm] - dod[p][mm - 1]);
                mm++;
            }
            dd = ile;
        }
        else
            dd = pom1 + ile;
        cout << "\n\t" << dd << ".";
        if (mm < 10)
            cout << "0";
        cout << mm << "." << "200" << yy;
    }

    friend int Przestepny(int rok);
};

int Przestepny(int rok);
int DzienTyg(int d, int m, int y);
void wypis(int i);
int ile_dni(int dod[2][13], int d1, int m1, int y1, int d2, int m2, int y2);
void dodaj(int k, int d1, int m1, int rok, int dod[2][13]);
string szukaj(string imie);

#endif
