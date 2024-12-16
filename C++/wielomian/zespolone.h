/*
	[ ------- wielomian  zespolony ---------]
	|---------------------------------------|
	| g++ (GCC) 4.0.2     (Red Hat 4.0.2-8) |
	| Pawel Kwiecien   gr.1 SRO 10:00-12:00 |
	|---------------------------------------|

	- biblioteka liczb zespolonych -
*/

#ifndef zespoloneH
#define zespoloneH

#include <iostream>
#include <cmath>

using namespace std;

class zesp
{
private:
	int re;						  // czesc rzeczywista
	int im;						  // czesc urojona
	zesp *This() { return this; } // wskaznik

public:
	zesp() : re(0), im(0) {}							 // konstruktor 1
	zesp(const int Re) : re(Re), im(0) {}				 // konstruktor 2
	zesp(const int Re, const int Im) : re(Re), im(Im) {} // konstruktor 3
	~zesp() {}											 // destruktor

	zesp sprzezona() { return zesp(re, -im); } // sprzezenie
	int get_re() { return re; }				   // czesc rzeczywista
	int get_im() { return im; }				   // czesc urojona

	zesp *operator&(zesp &z1) { return z1.This(); }
	zesp &operator=(const zesp &z1); // operator przypisania
	zesp &operator-=(const zesp &z1);
	zesp &operator+=(const zesp &z1);

	friend int modul(const zesp &z);						 // modul
	friend ostream &operator<<(ostream &out, const zesp z1); // wypisuje
	friend zesp &operator>>(istream &in, zesp &z1);			 // wczytywanie
	friend zesp operator+(const zesp &z1, const zesp &z2);	 // dodawanie
	friend zesp operator*(const zesp &z1, const zesp &z2);	 // mnozenie
	friend zesp operator-(const zesp &z1, const zesp &z2);	 // odejmowanie
	friend zesp operator/(const zesp &z1, const zesp &z2);	 // dzielenie
	friend bool operator==(const zesp &z1, const zesp &z2);	 // rownosc 1
	friend bool operator!=(const zesp &z1, const zesp &z2);	 // rownosc 2
};

#endif
