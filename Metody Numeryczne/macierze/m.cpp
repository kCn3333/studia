#include <iostream>

using namespace std;

class macierz {
 public:
   float l11, l12; /* pierwszy wiersz */
   float l21, l22; /* drugi wiersz */

   macierz();
   macierz(float a, float b, float c, float d);

   macierz odwrotna();

   friend ostream& operator << (ostream& stream, const macierz& matrix);
   friend istream& operator >> (istream& stream, macierz& matrix);
};

// macierz jednostkowa
macierz::macierz()
{
 macierz::l11=1;
 macierz::l12=0;
 macierz::l21=0;
 macierz::l22=1;
}

macierz::macierz(float a, float b, float c, float d)
{
 macierz::l11=a;
 macierz::l12=b;
 macierz::l21=c;
 macierz::l22=d;
}

macierz macierz::odwrotna()
{
 float wyznacznik;
 wyznacznik=(l11*l22 - l12*l21);

 macierz macierz_dopelnien; // macierz odpowiednich minorow przetransponowana
 macierz_dopelnien.l11=l22;
 macierz_dopelnien.l12=-1*l12;
 macierz_dopelnien.l21=-1*l21;
 macierz_dopelnien.l22=l11;

 macierz macierz_odwrotna; // macierz dopelnien pomnozona przez odwrotnosc wyznacznika
 macierz_odwrotna.l11=macierz_dopelnien.l11/wyznacznik;
 macierz_odwrotna.l12=macierz_dopelnien.l12/wyznacznik;
 macierz_odwrotna.l21=macierz_dopelnien.l21/wyznacznik;
 macierz_odwrotna.l22=macierz_dopelnien.l22/wyznacznik;

 return macierz_odwrotna;
}

ostream& operator << (ostream& stream, const macierz& matrix)
{
 stream << "[ " << matrix.l11 << "," << matrix.l12 << " ]" << endl;
 stream << "[ " << matrix.l21 << "," << matrix.l22 << " ]" << endl;
 return stream;
}

istream& operator >> (istream& stream, macierz& matrix)
{
 char linia[1000];
 float a,b,c,d;
 stream >>linia;
 scanf(linia, "%f,%f;%f,%f", &a, &b, &c, &d);

 matrix.l11=a;
 matrix.l12=b;
 matrix.l21=c;
 matrix.l22=d;

 return stream; 
}

// dodawanie macierzy - przeciazenie operatora
macierz operator+(const macierz& m1, const macierz& m2)
{
 macierz wynik;
 wynik.l11=(m1.l11+m2.l11);
 wynik.l12=(m1.l12+m2.l12);
 wynik.l21=(m1.l21+m2.l21);
 wynik.l22=(m1.l22+m2.l22);

 return wynik;
}

// odejmowanie macierzy - przeciazenie operatora
macierz operator-(const macierz& m1, const macierz& m2)
{
 macierz wynik;

 wynik.l11=(m1.l11-m2.l11);
 wynik.l12=(m1.l12-m2.l12);
 wynik.l21=(m1.l21-m2.l21);
 wynik.l22=(m1.l22-m2.l22);

 return wynik;
}

// mnozenie macierzy przez liczbe - przeciazenie operatora
macierz operator*(const macierz& m1, const int& liczba)
{
 macierz wynik;

 wynik.l11=(m1.l11*liczba);
 wynik.l12=(m1.l12*liczba);
 wynik.l21=(m1.l21*liczba);
 wynik.l22=(m1.l22*liczba);
 
 return wynik;
}

// mnozenie macierzy przez macierz - przeciazenie operatora
macierz operator*(const macierz& m1, const macierz& m2)
{
 macierz wynik;
 
 wynik.l11=( m2.l11*m1.l11 + m2.l21*m1.l12);
 wynik.l12=( m2.l12*m1.l11 + m2.l22*m1.l12);
 wynik.l21=( m2.l11*m1.l21 + m2.l21*m1.l22);
 wynik.l22=( m2.l12*m1.l21 + m2.l22*m1.l22);

 return wynik;
}




int main()
{
 cout << "MACIERZE" << endl;

 cout << "macierz jednostkowa (konstruktor)" << endl;
 macierz m1;
 cout << m1 << endl << endl;

 cout << "Teraz wpisz macierz w formacie: l11,l12;l21,l22" << endl;
 cout << " , oznacza nastepna liczbe" << endl;
 cout << " ; oznacza nastepny wiersz" << endl;

 macierz m2;
 cin >> m2;

 cout << "Wpisz jeszcze jedna macierz tak samo" << endl;

 macierz m3;
 cin >> m3;

 cout << "DODAWANIE MACIERZY" << endl;
 cout << endl << m1 << "   + " << endl <<  m2 << "   = " << endl << m1+m2 << endl;

 cout << "ODEJMOWANIE MACIERZY" << endl;
 cout << endl << m1 << "   - " << endl <<  m2 << "   = " << endl << m1-m2 << endl;

 cout << "MNOZENIE MACIERZY PRZEZ LICZBE" << endl;
 cout << endl << m2 << "   * " << endl << "   3 " << endl << "   = " << endl << m2*3 << endl;

 cout << "MNOZENIE MACIERZY PRZEZ SIEBIE" << endl;
 cout << endl << m1 << "   * " << endl <<  m2 << "   = " << endl << m1*m2 << endl;

 cout << "MACIERZ ODWROTNA" << endl;
 cout << "macierz odwrotna do " << endl << m2 << "  to " << endl << m2.odwrotna() << endl;

 cout << "MNOZENIE MACIERZY PRZEZ SIEBIE - nie  przez jednostkowa" << endl;
 cout << endl << m2 << "   * " << endl << m3  << "   = " << endl << m2*m3 << endl;
 return 0;
}
