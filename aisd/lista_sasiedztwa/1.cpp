#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include "ls.h"

using namespace std;

int Liczba_wierzcholkow=0;
int start=0;	//indeks na liscie
int n=0; 	
int time1=0;
int prize=0;
int meta=0; 
typ type=1;							// wybor typu polaczenia
//miasta meta;
string plik[4];
string plik[1]="nazwa_pliku1.txt";
string plik[2]="nazwa_pliku2.txt";
string plik[3]="nazwa_pliku3.txt";

main()
{

ifstream odczyt[4];
int i=1;

for (int i;i<5;i++)
ifstream odczyt[i](plik[i].c_str());

Liczba_wierzcholkow=XXX;
Lista *L=new Lista[Liczba_wierzcholkow];			// lista sasiedztwa

for (int i=1;i<5;i++)
{
do
{
odczyt[i] >> start;
odczyt[i] >> meta;
odczyt[i] >> time1;
odczyt[i] >> prize;
L[start].AddtoTail(start, meta, time1, prize, type);			// dodaje do listy sasiedztwa
L[meta].AddtoTail(meta, start, time1, prize, type);			// dodaje do listy sasiedztwa
type++;
}	
while (!odczyt[i].eof());		
odczyt[i].close();
}


}1