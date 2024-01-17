#include <string>
#include <iostream>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sys/time.h>
 
#define DLUGOSC 100
 
using namespace std;

typedef vector < vector <double> > matrix;

vector <double> LU(vector <double> a, vector <double> b, vector <double> c, vector <double> d, int n)
{
double l=0;
double y[n+1];
double u[n+1];
vector <double> x;
x.resize(n+1);

u[1]=b[1];
y[1]=d[1];
for(int i=2;i<=n;i++)
{
if(u[i-1]!=0) l=a[i]/u[i-1];
else  { cout <<"\n #blad obliczen u["<<i-1<<"] =0"; return x; }
u[i]=b[i]-l*c[i-1];
y[i]=d[i]-l*y[i-1];
}
if(u[n]!=0) x[n]=y[n]/u[n];
else  { cout <<"\n #blad obliczen u["<<n<<"] =0"; return x; }
for(int i=n-1; i>=1;i--)
{
if(u[i]!=0) { x[i]=((y[i]-c[i]*x[i+1])/u[i]);}
else { cout <<"\n #blad obliczen u["<<i<<"] =0"; return x; }
}
return x;
}

int main(int argc, char * argv[])
{
	string plik;
	int ile,n;
	matrix macierz;
	vector <double> a;
	vector <double> b;
	vector <double> c;
	vector <double> d;
	vector <double> rozwiazanie;
	
	cout <<"\n\t rozwiazywanie ukladu z macierza trojdiagonalna"<<endl;
	cout <<"\t\t przy pomocy rozkladu LU\n"<<endl;

	if (argc != 2) 
	{
		cout << "Podaj nazwe pliku wejsciowego" <<endl;
		cin >> plik;
	} 
	else plik = argv[1];
	  

	ifstream odczyt(plik.c_str());
	odczyt >> ile;
	macierz.resize(ile);
					      // wczytanie danych do macierzy rozszerzonej
	for (int i = 0; i < ile; i++) 
	{
		macierz[i].resize(ile + 1);
		for (int j = 0; j < (ile + 1); j++) 
		   odczyt >> macierz[i][j]; 
	}
	
	cout << " Macierz rozszerzona ukladu:"<<endl;
	
	for (unsigned int i = 0; i < macierz.size(); i++) 
	{
		for (unsigned int j = 0; j < (macierz[i].size()); j++) 
			cout << "\t" << macierz[i][j];
		cout<<endl;
	}
	a.resize(ile+1);
	b.resize(ile+1);
	c.resize(ile+1);
	d.resize(ile+1);
	rozwiazanie.resize(ile+1);
	
	n=ile;
	int k=2;
	for (int i=1;i<n;i++)
	for (int j=0;j<n;j++)
	if (i-1==j) { a[k]=macierz[i][j]; k++; }
	k=1;
	for (int i=0;i<n;i++)
	for (int j=0;j<n;j++)
	if (i==j) { b[k]=macierz[i][j]; k++; } 
	k=1;
	for (int i=0;i<n-1;i++)
	for (int j=1;j<n;j++)
	if (i+1==j) { c[k]=macierz[i][j]; k++; }
	k=1;
	for (int i=0;i<n;i++)
	for (int j=0;j<n+1;j++)
	if (j==n) { d[k]=macierz[i][j]; k++; }
	
	rozwiazanie = LU(a,b,c,d,ile);
	
	cout << endl << " Rozwiazanie:" << endl;
	for (int i=1; i<rozwiazanie.size(); i++) 
		cout << " x" << i <<"= "<< rozwiazanie[i] << endl;
	odczyt.close();

}