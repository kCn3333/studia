/*
    [ ------- wielomian  zespolony ---------]
    |---------------------------------------|
    | g++ (GCC) 4.0.2     (Red Hat 4.0.2-8) |
    | Pawel Kwiecien   gr.1 SRO 10:00-12:00 |
    |---------------------------------------|

    - biblioteka wielomianow -
*/

#ifndef wielomianH
#define wielomianH

#include <iostream>
#include <cmath>
#include "zespolone.h"

using namespace std;

class wielomian
{
private:
    int st;    // stopien wielomianu
    zesp *wsp; // tablica wspolczynnikow zespolonych

public:
    explicit wielomian(const int stopien);              // konstruktor 1
    wielomian(const int stopien, const zesp wspolcz[]); // konstruktor 2
    wielomian(const zesp &z);                           // jednomian
    wielomian(const wielomian &w1);                     // konstruktor kopiujacy
    ~wielomian() { delete[] wsp; }                      // destruktor
    int stopien() { return st; }                        // zwraca stopien wielomianu
    wielomian &operator=(const wielomian &w1);          // przypisanie
    zesp &operator[](const int n);                      // zwraca odpowiedni wspolczynnik
    zesp operator()(const zesp z);                      // zwraca wart wiel w punkcie z

    friend ostream &operator<<(ostream &wypisz, const wielomian w1);      // wypisawnie
    friend wielomian &operator>>(istream &wpisz, wielomian &w1);          // wczytywanie
    friend wielomian operator+(const wielomian &w1, const wielomian &w2); // dodawania
    friend wielomian operator-(const wielomian &w1, const wielomian &w2); // odejmowanie
    friend wielomian operator*(const wielomian &w1, const wielomian &w2); // mnozenie
    friend bool operator==(const wielomian &w1, const wielomian &w2);     // rownosc
    friend bool operator!=(const wielomian &w1, const wielomian &w2);     // nierownosc
};

#endif
