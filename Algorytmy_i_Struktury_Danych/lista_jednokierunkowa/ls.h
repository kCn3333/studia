//***************** ls.h *****************

#ifndef LS_H
#define LS_H

#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
    int grupa;
    string imie;
    string nazwisko;
    class Student *next; // wskaznik do nastepnego
    Student(int g, string i, string n)
    {
        grupa = g;
        imie = i;
        nazwisko = n;
    } // konstruktor
};

class Lista
{
public:
    Lista() { head = tail = 0; }         // konstruktor
    int isEmpty() { return head == 0; }  // zwraca 0 jesli pusta
    void AddToTail(int, string, string); // dodaje na koniec listy
    bool IsInList(string) const;         // przeszukuje liste
    void Print() const;                  // wyswietla liste
private:
    Student *head, *tail; // wskazniki do poczatku i konca listy
};

#endif
