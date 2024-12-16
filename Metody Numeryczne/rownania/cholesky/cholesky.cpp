#include <string>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sys/time.h>
 
#define N 100
 
using namespace std;
typedef vector < vector <double> > matrix;
 
void choleski(double L[N][N],
              double A[N][N]);
 
void pokaz(double L[N][N])
{
for (int i = 0; i<N; i++) 
{
  for (int j =0; j<N; j++) 
    cout << L[i][j]<<" ";
  cout <<endl;
}
}
	      
	      
int main(int argc, char* argv[]) 
{
    double A[N][N];
    double L[N][N];
    string plik;

  if (argc != 2) 
  {
      cout << "Podaj nazwe pliku wejsciowego" <<endl;
      cin >> plik;
   } 
  else plik = argv[1];
	
  ifstream odczyt(plik.c_str());
	
  for (int i = 0; i < N; i++)	
    for (int j = 0; j < N; j++) 
	odczyt >> A[i][j]; 

	    	
	cout <<"\n licze rozklad Cholesky'ego macierzy A z pliku "<<argv[1]<<" ..."<<endl;
    
             timeval tim;
             gettimeofday(&tim, NULL);
             double t1=tim.tv_sec+(tim.tv_usec/1000000.0);
        //for (int i=0;i<10000; i++) 
	  choleski(L,A);
             gettimeofday(&tim, NULL);
             double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
    cout <<"\n czas: "<<fixed<<t2-t1<<" sekund"<<endl;
    cout <<"\n macierz L zapisana do pliku rozklad.txt"<<endl<<endl;
    fstream zapis("rozklad.txt",fstream::out);
    for (int i = 0; i<N; i++) 
      {
	for (int j =0; j<N; j++) 
	  zapis << L[i][j]<<" ";
	zapis <<endl;
      }
    zapis.close();
    odczyt.close();
    return 0;
}
 
void choleski(double L[N][N], double A[N][N]) 
{
    double a, b, c;
 
    for(int i=0;i<N;i++) 
        for(int j=0;j<N;j++)
            L[i][j]=0;

    L[0][0] = sqrt(A[0][0]);
    for(int i=0;i<N;i++) 
       for(int j=0;j<=i;j++) 
	{
	  if(i==j) 
	    {
	      a = A[j][j];
              b = 0.0;
              for(int k=0;k<j;k++)
                 b = b + L[j][k]*L[j][k];
              L[j][j]=sqrt(a-b);
	    }
          else 
	    {
              a = A[i][j];
              b = 0.0;
	      for(int k=0;k<=(j-1);k++)
                 b = b + (L[i][k]*L[j][k]);
              c=0.0;
              c=(a-b);
              L[i][j] = c/L[j][j];
	    }
           
        }
 
}
