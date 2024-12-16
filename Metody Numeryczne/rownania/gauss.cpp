#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef vector < vector <double> > matrix;

matrix trojkatnagorna(matrix array)	// przeksztalca macierz rozszerzona w macierz górną trójkatną 
{
	unsigned int s, i, n, j, c;

	n = array.size() - 1;

	for (s=0; s<=n-1; s++) 
	{
	  for (i=s+ 1; i<= n; i++) 
	      for (j=s+1; j<=n+1; j++) 
		  array[i][j] = array[i][j] - array[i][s] * array[s][j] / array[s][s];
	   
	 	//zapewnia ze kazde kolejne równanie ma mniej zmiennych (jest nizszego stopnia)
	      for (c=s+1; c<=n; c++) 
		  array[c][s] = 0.0;	//zeruje "wczesniejsze" pola w wierszu
	}
	return array;
}


// na podstawie pobieranej macierzy górnotrójkatnej, oblicza rozwiazanie
vector <double> rozwiaz(matrix array)
{
	vector <double>x;

	unsigned int n, s;
	int i;			//!!!
	double sum;
	unsigned int size = array.size();	//rozmiar pionowy (ilosc wierszy/zmiennych)
	
	x.resize(size);
	n = size-1;		//aby przejsc na notacje od 0

	x[n] = array[n][n+1]/array[n][n];

	//obliczam wyniki - A*x=B
	for (i=n-1; i>=0; i--) 
	{
		sum=0.0;
		for (s=i+1; s<=n; s++) 
			sum = sum + (array[i][s] * x[s]);
		x[i] = (array[i][n+1] - sum)/array[i][i];	
	}
	return x;
}

int main(int argc, char * argv[])
{
	string plik;
	int ile;
	matrix macierz;
	vector <double> rozwiazanie;
	
	cout <<"\n\t rozwiazywanie ukladu rownan"<<endl;
	cout <<"\t przy pomocy Eliminacji Gaussa\n"<<endl;

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
	
	cout << "Macierz rozszerzona ukladu:"<<endl;
	
	for (unsigned int i = 0; i < macierz.size(); i++) 
	{
		for (unsigned int j = 0; j < (macierz[i].size()); j++) 
			cout << "\t" << macierz[i][j];
		cout<<endl;
	}

	macierz = trojkatnagorna(macierz);	// macierz gorna trojkatna
	
	rozwiazanie = rozwiaz(macierz);
	
	cout << endl << "Rozwiazanie:" << endl;
	for (int i=0; i<rozwiazanie.size(); i++) 
		cout << "x" << i+1 <<"= "<< rozwiazanie[i] << endl;
	odczyt.close();

}
	


