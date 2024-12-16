//************ definicje funkcji z ls.h  *************

#include <iostream>
#include "ls.h"

using namespace std;

void Lista::AddToTail(int gr, string i, string n)
{
    if (tail != 0) // jesli lista nie pusta
    {
        tail->next = new Student(gr, i, n); // ogon wskazuje na el dodawany
        tail = tail->next;                  // el dodawany wskazuje na nowy ogon
    }
    else
        head = tail = new Student(gr, i, n); // gdy tylko head na liscie
}

bool Lista::IsInList(string n) const
{
    Student *tmp; // wskaznik do poruszania sie po liscie
    for (tmp = head; tmp != 0 && !(tmp->nazwisko == n); tmp = tmp->next)
        ;            // przesuwa wskaznik
    return tmp != 0; // zwraca 0 gdy przejdzie do konca i nie znajdzie (tmp==0)
}

void Lista::Print() const
{
    cout << "\n |";
    for (Student *tmp = head; tmp != 0; tmp = tmp->next)
        cout << tmp->grupa << " " << tmp->imie << " " << tmp->nazwisko << "| -> |";
    cout << "NULL" << endl;
}
