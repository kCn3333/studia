#include <string>
#include <iostream>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sys/time.h>
 
#define N 128
#define BLAD 0.0000000001
 
using namespace std;

int GaussSeidel(double A[N][N], double b[N], double x1[N])
{
	    double tmp1;
            double tmp2;
            double x[N];
            double sumx, sumx1;
            int k = 0;
            for (int i = 0; i < N; i++)
            {
                x1[i] = b[i] / A[i][i];
            }

            do
            {
                for (int i = 0; i < N; i++)
                {
                    x[i] = x1[i];
                }

                for (int i = 0; i < N; i++)
                {
                    tmp1 = 0;
                    tmp2 = 0;
                    for (int j = 0; j < i; j++)
                    {
                        tmp1 += A[i][j] * x1[j];
                    }
                    for (int j = i + 1; j < N; j++)
                    {
                        tmp2 += A[i][j] * x[j];
                    }
                    x1[i] = (1.0 / A[i][i]) * (b[i] - tmp1 - tmp2);
                }

                sumx = 0;
                sumx1 = 0;
                for (int i = 0; i < N; i++)
                {
                    sumx += x[i]*x[i];
                    sumx1 += x1[i]*x1[i];
                }

                ++k;
            } while (abs(sqrt(sumx) - sqrt(sumx1)) > BLAD);

            return k;
}
        
int ConjugateGradient(double A[N][N], double b[N], double x[N])
{
    double r[N];
    double p[N];
    double x1[N];
    double alfa,beta,sumx,sumx1;
    double licznik, mianownik, tmp1, tmp2, tmp3;
    double Ap[N];
    int k=0;
    double norma=0; 
      
      for(int i=0; i<N;i++)
	{ 
	  tmp1=b[i];
	  r[i]=-tmp1; 
	  p[i]=tmp1; 
	  x[i]=0.0;
	}
      do
	{
	  licznik=0; mianownik=0;
	   
	  for(int i=0; i<N;i++)
	      x1[i]=x[i];
	  
	  for (int i=N-1; i>=0; i--)
	    {
		licznik += p[i]*r[i]; tmp1=0;
		    for (int j=0; j<i; j++)
		tmp1 += A[j][i]*p[j];
		for (int j=i; j<N; j++)
		    tmp1 += A[i][j]*p[j];
		Ap[i] = tmp1;
		mianownik += p[i]*tmp1;
	    }
	  if (mianownik==0) { cout <<"# blad, mianownik =0"<<endl; return 0; }
	  alfa= -licznik/mianownik;
  
	  norma=0; tmp3=0;
	  for(int i=N-1; i>=0; i--)
	    {  
		tmp1= x[i];
		norma +=tmp1*tmp1;
		tmp2= alfa*p[i];
		tmp3 += tmp2*tmp2;
		x[i]= tmp1+tmp2;
	     }
  	  sumx = 0;
          sumx1 = 0;
          
	  for (int i = 0; i < N; i++)
          {
                sumx += x[i]*x[i];
                sumx1 += x1[i]*x1[i];
          }
  	  
  	  for(int i=N-1; i>=0; i--)
	      r[i] += alfa*Ap[i]; 
  
	  licznik=0;
	  for (int i=N-1; i>=0; i--)
	      licznik += r[i]*Ap[i];
	  beta= licznik/mianownik;
  
	  for(int i=N-1; i>=0; i--)
	      p[i] = -r[i]+beta*p[i];
  
      ++k;
    } while ((abs(sqrt(sumx) - sqrt(sumx1)) > BLAD) && (k<N)); //while ((tmp3 > BLAD*norma) && (k < N));

  return k;
}
      
void Cholesky(double A[N][N], double e[N], double x[N]) 
{
    double a, b, c;
    double L[N][N];
    double y[N];
    
    for(int i=0;i<N;i++) 
        for(int j=0;j<N;j++)
            L[i][j]=0;

    for(int i=0;i<N;i++) 
       for(int k=0;k<=i;k++) 
	{
	  if (i==0 && k==0) L[0][0] = sqrt(A[0][0]);
	  
	  else if(i==k) 
	    {
	      a = A[k][k];
              b = 0.0;
              for(int j=0;j<k;j++)
                 b += L[k][j]*L[k][j];
              L[k][k]=sqrt(a-b);
	    }
          else if(i!=k)
	    {
              a = A[i][k];
              b = 0.0;
	      for(int j=0;j<k;j++)
                 b += (L[i][j]*L[k][j]);
              c=0.0;
              c=(a-b);
              L[i][k] = c/L[k][k];
	    }
          }
    for (int i=0; i<N; i++)
    {
      a=0.0;
      for (int j=0; j<i;j++)
	a+=L[i][j]*y[j];
      y[i]=(e[i]-a)/L[i][i];
    }
    
    for (int i=N-1; i>=0; i--)
    {
      a=0.0;
      for (int j=i+1; j<N; j++)
	a+=L[j][i]*x[j];
      x[i]=(y[i]-a)/L[i][i];
    }
}
	      
int main(int argc, char* argv[]) 
{
    double A[N][N];
    double b[N];
    double e[N];
    double e2[N];
    double e1[N];
    double t1,t2;
    string plik;
    int k;
    timeval tim;
    
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
  
  for (int i=0; i<N; i++)
    b[i]=1;
  
cout.precision(10);	    	
cout <<"\n rozwiazanie ukladu Ax=b, macierz A z pliku "<<argv[1]<<" ..."<<endl<<endl;
cout <<"\n dopuszczalny blad < "<<fixed<<BLAD <<endl;
cout <<"\n [ rozklad Cholesky'ego ]"<<endl;
    gettimeofday(&tim, NULL);
    t1=tim.tv_sec+(tim.tv_usec/1000000.0);
    Cholesky(A,b,e); 
    gettimeofday(&tim, NULL);
    t2=tim.tv_sec+(tim.tv_usec/1000000.0);
cout <<" w czasie: "<<fixed<<t2-t1<<" sekund"<<endl;

cout <<"\n ---- metody iteracyjne ----"<<endl;
cout <<"\n [ metoda Gaussa-Seidela ]"<<endl;
    gettimeofday(&tim, NULL);
    t1=tim.tv_sec+(tim.tv_usec/1000000.0);
    k=GaussSeidel(A,b,e1); 
    gettimeofday(&tim, NULL);
    t2=tim.tv_sec+(tim.tv_usec/1000000.0);
cout <<" zakonczono po "<<k<<" iteracjach"<<endl;
cout <<" w czasie: "<<fixed<<t2-t1<<" sekund"<<endl;
      
cout <<"\n [ metoda gradientow sprzezonych ]"<<endl;
    gettimeofday(&tim, NULL);
    t1=tim.tv_sec+(tim.tv_usec/1000000.0);
    k=ConjugateGradient(A,b,e2); 
    gettimeofday(&tim, NULL);
    t2=tim.tv_sec+(tim.tv_usec/1000000.0);
cout <<" zakonczono po "<<k<<" iteracjach"<<endl;
cout <<" w czasie: "<<fixed<<t2-t1<<" sekund"<<endl<<endl;

return 0;
}
 

