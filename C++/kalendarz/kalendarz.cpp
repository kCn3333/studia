/*
[ ------- zestaw 3 / kalendarz ---------]
|---------------------------------------|
| g++ (GCC) 4.0.2     (Red Hat 4.0.2-8) |
| Pawel Kwiecien   gr.1 SRO 10:00-12:00 |
|---------------------------------------|
*/

#include "data.h"

int dod[2][13] =
    {
        {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365}, // lata zwykle
        {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}  // lata przestepne
};

//===================================== main =======================================
int main()
{
    time_t wsk_sekund;
    time(&wsk_sekund);
    struct tm *e;
    e = localtime(&wsk_sekund);

    data biezaca;

    biezaca.yy = e->tm_year + 1900; // rok
    biezaca.mm = e->tm_mon + 1;     // miesiac
    biezaca.d_t = e->tm_wday;       // dzien_tygodnia
    biezaca.dd = e->tm_mday;        // dzien_miesiaca
    biezaca.przestepny();           // p=1 dla lat przestepnych
    biezaca.IleDni(dod);
    biezaca.co_dzis();

    int i = 1, j = 1; // indeksy do wypisywania

    cout << "\n\t[==========================]";
    cout << "\n\t|\t" << ((biezaca.d_t == 0) ? "Niedziela" : (biezaca.d_t == 1) ? "Poniedzialek"
                                                         : (biezaca.d_t == 2)   ? "Wtorek"
                                                         : (biezaca.d_t == 3)   ? "Sroda"
                                                         : (biezaca.d_t == 4)   ? "Czwartek"
                                                         : (biezaca.d_t == 5)   ? "Piatek"
                                                                                : "Sobota");
    // 0 -niedziela 1 -poniedzialek
    cout << "\n\t|\t\t\t ____________";
    cout << "\n\t|\t" << biezaca.dd << ".";
    if (biezaca.mm < 10)
        cout << "0";
    cout << biezaca.mm;
    cout << "." << biezaca.yy << "\t[_z_e_g_a_r__]"
         << "\n\t|\t\t\t|  " << e->tm_hour
         << ":";
    if (e->tm_min < 10)
        cout << "0";
    cout << e->tm_min;
    cout << ":";
    if (e->tm_sec < 10)
        cout << "0";
    cout << e->tm_sec << " ||";
    cout << "\n\t| --------------------- | |_|_|_|_|_||"
         << "\n\t| to juz " << e->tm_yday << " dzien roku |"
         << " |_|_|_|_|_||"
         << "\n"
         << ((e->tm_isdst == 1) ? "\t|\t   'czas letni' |" : "\t|\t   'czas zimowy'|")
         << " |_|_|_|_|_||"
         << "\n\t|\t\t\t[____________]"
         << "\n\t[===========#kCn===========]\n"
         << "\n\timieniny: " << biezaca.imieniny << "\n"
         << "\n\t\t" << biezaca.swieto << "\n\n";

    cout << "\n\tND\tPN\tWT\tSR\tCZ\tPT\tSB\n";

    j = DzienTyg(1, biezaca.mm, biezaca.yy);

    if (biezaca.mm != 2)
    {
        wypis(j);
        while (j < 7) // 1-szy tydzien
        {
            if (biezaca.dd == i)
            {
                cout << "\t[" << i << "]";
                i++;
                j++;
            }
            cout << "\t" << i;
            i++;
            j++;
        }
        cout << endl;
        //=================================
        while (j < 14) // 2-gi tydzien
        {
            if (biezaca.dd == i)
            {
                cout << "\t[" << i << "]";
                i++;
                j++;
            }
            cout << "\t" << i;
            i++;
            j++;
        }
        cout << endl;
        //=================================
        while (j < 21) // 3-ci tydzien
        {
            if (biezaca.dd == i)
            {
                cout << "\t[" << i << "]";
                i++;
                j++;
            }
            cout << "\t" << i;
            i++;
            j++;
        }
        cout << endl;
        //=================================
        while (j < 28) // 4-ty tydzien
        {
            if (biezaca.dd == i)
            {
                cout << "\t[" << i << "]";
                i++;
                j++;
            }
            cout << "\t" << i;
            i++;
            j++;
        }
        cout << endl;
        //=================================
        while (i <= biezaca.d_m) // 5-ty tydzien
        {
            if ((biezaca.dd == i) && (biezaca.dd != biezaca.d_m))
            {
                cout << "\t[" << i << "]";
                i++;
            }
            if (biezaca.dd == biezaca.d_m) // jesli ostatni dzien miesiaca to koncz wypisywanie
            {
                while (i < biezaca.dd)
                {
                    cout << "\t" << i;
                    i++;
                }
                cout << "\t[" << i << "]";
                i++;
                break;
            }
            cout << "\t" << i;
            i++;
        }
        cout << endl;
    }
    cout << endl;

    int menu; // wybor menu
    cout << "\t------------m-e-n-u-------------\n";
    cout << "\t--> policz dzien tygodnia  1 <--\n";
    cout << "\t--> policz ile dni         2 <--\n";
    cout << "\t--> dodaj do daty          3 <--\n";
    cout << "\t--> sprawdz kiedy imieniny 4 <--\n";
    cout << "\t--> wyjscie                0 <--\n";
    cout << "\t--------------------------------";

    while (1)
    {
        cout << "\n\n wybierz: ";
        cin >> menu;

        int k; // zmienne pomocnicze
        string imie, kiedy, dat;
        data data1, data2;

        switch (menu)
        {
        case 0:
            exit(1);
            ////////////////////////////////////
        case 1:
            cout << " -----------------------------------------------\n";
            cout << " podaj date dla ktorej wyswietlic dzien tygodnia\n";
            cout << " dd.mm.yyyy: ";
            cin >> dat;
            data1.zapamietaj(dat);
            data1.przestepny();
            data1.DzienTyg();
            k = data1.d_t;
            cout << "\t :: " << ((k == 0) ? "Niedziela" : (k == 1) ? "Poniedzialek"
                                                      : (k == 2)   ? "Wtorek"
                                                      : (k == 3)   ? "Sroda"
                                                      : (k == 4)   ? "Czwartek"
                                                      : (k == 5)   ? "Piatek"
                                                                   : "Sobota")
                 << " :: ";
            break;
            ////////////////////////////////////
        case 2:
        {
            cout << " ---------------------------------------------------\n"
                 << " podaj daty dla ktorych dla ktorych policzyc roznice\n"
                 << " 1";
            cout << "\tdd.mm.yyyy: ";
            cin >> dat;
            data1.zapamietaj(dat);
            cout << " 2";
            cout << "\tdd.mm.yyyy: ";
            cin >> dat;
            data2.zapamietaj(dat);

            cout << "\n\n :: pomiedzy podanymi datami jest " << ile_dni(dod, data1.dd, data1.mm, data1.yy, data2.dd, data2.mm, data2.yy) << " dni ::";
            break;
        }
            ////////////////////////////////////
        case 3:
        {
            cout << " ---------------------------------------------------------\n";
            cout << " Dodawanie dni do podanej daty ";
            cout << "\n podaj date, dd.mm.yyyy: ";
            cin >> dat;
            data2.zapamietaj(dat);
            cout << " ile dni dodac: ";
            cin >> k;

            data2.przestepny();
            data2.IleDni(dod);
            data2.dodaj(k, dod);
            break;
        }
            ////////////////////////////////////
        case 4:
        {
            cout << " ---------------------------------------------------------\n";
            cout << " Wyszukiwanie dat imienin ";
            cout << "\n\timieniny: ";
            cin >> imie;

            cout << "\n :: imieniny " << imie << ":\n";
            kiedy = szukaj(imie);
            cout << kiedy;

            break;
        }
            ////////////////////////////////////
        default:
        {
            cout << ":: bledna wartosc\n";
            break;
        }
        }
    }
}
