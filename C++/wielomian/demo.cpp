/*
    [ ------- wielomian  zespolony ---------]
    |---------------------------------------|
    | g++ (GCC) 4.0.2     (Red Hat 4.0.2-8) |
    | Pawel Kwiecien   gr.1 SRO 10:00-12:00 |
    |---------------------------------------|

    program testuje klase 'wielomian zespolony'
*/

#include "wielomian.h"

int main()
{
     int n;
     zesp z;
     wielomian w1(0), w2(0);
     cout << "\n --------------------------------------------"
          << "\n ----W-I-E-L-O-M-I-A-N--Z-E-S-P-O-L-O-N-Y----"
          << "\n --------------------------------------------\n\n";
     cin >> w1;                // wczytuje wielomian 1
     cout << "\n W(x)= " << w1 // wypisuje wielomian 1
          << "\n ---------------------------";
     cin >> w2;                                                                    // wczytuje wielomian 2
     cout << "\n V(x)= " << w2                                                     // wypisuje wielomian 2
          << "\n ---------------------------";                                     // dzialania na wielomianach:
     cout << "\n W(x) + V(x) = ( " << w1 << " ) + ( " << w2 << " ) = " << w1 + w2  // dodawanie
          << "\n W(x) - V(x) = ( " << w1 << " ) - ( " << w2 << " ) = " << w1 - w2  // odejmowanie
          << "\n W(x) * V(x) = ( " << w1 << " ) * ( " << w2 << " ) = " << w1 * w2; // mnozenie
     if (w1 == w2)
          cout << "\n W(x) = V(x)"; // porownanie wielomianow
     else
          cout << "\n W(x) != V(x)";
     cout << "\n\n numer wspolczynnika ktory pokazac: ";
     cin >> n;
     cout << " " << n << " wspolczynnik W(x) wynosi: " << w1[n]    // pokazuje n-ty
          << "\n " << n << " wspolczynnik V(x) wynosi: " << w2[n]; // wspolczynnik wielomianu
     cout << "\n\n argument dla ktorego policzyc wartosc: ";
     cin >> z;
     cout << " W" << z << " = " << w1(z) << "    V" << z << " = " << w2(z); // wartosc wielomianu w punkcie
     cout << "\n\n W(x) * z = " << z << " * " << w1 << " = " << w1 * z;     // mnozenie wielomianu przez liczbe
     cout << "\n --------------------------------------------\n";

     return 0;
}
