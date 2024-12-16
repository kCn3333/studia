/*

Wartosci wlasne i wektory wlasne macierzy A
z wykorzystaniem Hausholdera i metody QL.

*/

#include <string>
#include <iostream>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <fstream>

#define N 10
#define kwadrat(X) ((X) * (X))

using namespace std;

double Znak(double a, double b) 
{
   if (b <0.0) return (- fabs(a));
   else return (fabs(a));
}

void QLMethod(int n, double *D, double *E, double Z[N+1][N+1], int *zbieznosc)  
{
//  Labels: e10,e12,e18,e20,e26,e30,e34,e36
      double B,C,F,G,H,P,R,S,EPS,EPS1;
      int  I,J,K,L,M,JM;

      EPS=0.0; JM=30;
      *zbieznosc = 0;
      if (N == 1)  return;

//    MACHINE EPSILON

      if (EPS != 0.0) goto e12;
      EPS = 1.0;
e10:  EPS = EPS/2.0;
      EPS1 = 1.0 + EPS;
      if (EPS1 > 1.0) goto e10;

e12:  for (I=2; I<=N; I++)  E[I-1] = E[I];
      E[N] = 0.0;
      F = 0.0;
      B = 0.0;

      for (L=1; L<=N; L++) {
        J = 0;
        H = EPS*(fabs(D[L])+fabs(E[L]));
        if (B < H)  B = H;

//      SEEK SMALLEST ELEMENT OF SUBDIAGONAL

        for (M=L; M<=N; M++)
          if (fabs(E[M]) <= B) goto e18;

e18:    if (M == L)  goto e26;

//      START ITERATION

e20:    if (J == JM) goto e36;
        J = J+1;

//      SHIFT

        G = D[L];
        P = (D[L+1]-G)/(2.0*E[L]);
        R = kwadrat(P*P+1.0);
        D[L] = E[L]/(P + Znak(R,P));
        H = G-D[L];
        for (I=L+1; I<=N; I++)  D[I] = D[I] - H;
        F = F + H;

//      QL TRANSFORMATION

        P = D[M];
        C = 1.0;
        S = 0.0;
        for (I=M-1; I>=L; I--) {
          G = C*E[I];
          H = C*P;
          if (fabs(P) >= fabs(E[I])) {
            C = E[I]/P;
            R = kwadrat(C*C+1.0);
            E[I+1] = S*P*R;
            S = C/R;
            C = 1.0/R;
          }
          else {
            C = P/E[I];
            R = kwadrat(C*C+1.0);
            E[I+1] = S*E[I]*R;
            S = 1.0/R;
            C = C*S;
          }
          P = C*D[I]-S*G;
          D[I+1] = H+S*(C*G+S*D[I]);

//      ELEMENTS OF EIGENVECTORS

          for (K=1; K<=N; K++) {
            H = Z[K][I+1];
            Z[K][I+1] = S*Z[K][I]+C*H;
            Z[K][I] = Z[K][I]*C-S*H;
          }
        }
        E[L] = S*P;
        D[L] = C*P;
        if (fabs(E[L]) > B) goto e20;

//      CONVERGENCE

e26:    D[L] = D[L] + F;
      }

//      SORT EIGENVALUES AND EIGENVECTORS
//      IN ASVENDING ORDER

      for (L=2; L<=N; L++) {
        I = L-1;
        K = I;
        P = D[I];
        for (J=L; J<=N; J++) {
          if (D[J] >= P) goto e30;
          K = J;
          P = D[J];
e30:   ;}
        if (K == I)  goto e34;
        D[K] = D[I];
        D[I] = P;
        for (J=1; J<=N; J++) {
          P = Z[J][I];
          Z[J][I] = Z[J][K];
          Z[J][K] = P;
        }
e34: ;}
      return;

//    NO CONVERGENCE

e36:  *zbieznosc = L;
   } //TQL2

void TRED2(double a[N+1][N+1], int n, double *d, double *e)  
{
int    l, k, j, i;
double scale, hh, h, g, f;

for (i = n; i >= 2; i--)  {

  l = i - 1;
    h = scale = 0.0;
    if (l > 1)  {
       for (k = 1; k <= l; k++)
           scale += fabs(a[i][k]);
       if (scale == 0.0)
          e[i] = a[i][l];
       else  {
          for (k = 1; k <= l; k++) {
            a[i][k] /= scale;
            h += a[i][k] * a[i][k];
          }
          f = a[i][l];
          g = (f>0 ? -sqrt(h) : sqrt(h));
          e[i] = scale * g;
          h -= f * g;
          a[i][l] = f - g;
          f = 0.0;
          for (j = 1; j <= l; j++) {
            a[j][i] = a[i][j]/h;
            g = 0.0;
            for (k = 1; k <= j; k++)
              g += a[j][k] * a[i][k];
            for (k = j+1; k <= l; k++)
              g += a[k][j] * a[i][k];
            e[j] = g / h;
            f += e[j] * a[i][j];
          }
          hh = f / (h + h);
          for (j = 1; j <= l; j++) {
            f = a[i][j];
            e[j] = g = e[j] - hh * f;
            for (k = 1; k <= j; k++)
              a[j][k] -= (f * e[k] + g * a[i][k]);
          }
       }
    }
    else
        e[i] = a[i][l];
    d[i] = h;
}
d[1] = 0.0;
e[1] = 0.0;

for (i = 1; i <= n; i++)
    {
    l = i - 1;
    if (d[i])
       {
       for (j = 1; j <= l; j++)
           {
           g = 0.0;
           for (k = 1; k <= l; k++)
               g += a[i][k] * a[k][j];
           for (k = 1; k <= l; k++)
               a[k][j] -= g * a[k][i];
           }
       }
       d[i] = a[i][i];
       a[i][i] = 1.0;
       for (j = 1; j <= l; j++)
           a[j][i] = a[i][j] = 0.0;
    }
} //tred2()

int main(int argc, char* argv[]) 
{
double D[N+1], E[N+1];		// index od 1
double Z[N+1][N+1];		// macierz A
double zmax;
int  i,j,zbieznoscR,n=N;

string plik;
  if (argc != 2) 
  {
      cout << "Podaj nazwe pliku wejsciowego" <<endl;
      cin >> plik;
   } 
  else plik = argv[1];
	
ifstream odczyt(plik.c_str());
	
  for (int i = 1; i <=n; i++)	
    for (int j = 1; j <=n; j++) 
	odczyt >> Z[i][j]; 

    cout <<"\n Wartosci wlasne i wektory wlasne macierzy A\n";
    cout <<" z wykorzystaniem Hausholdera i metody QL.\n\n";
    cout <<" macierz A: \n";
    for (int i=1; i<=n; i++) 
    {
      for (j=1; j<=n; j++)
	cout<<" "<<Z[i][j]<<"  ";
      cout <<endl;
    }

    TRED2(Z,N,D,E);
    QLMethod(N,D,E,Z,&zbieznoscR);

    if(zbieznoscR) cout<<"\n nie osiagnieto zbieznosci po "<<zbieznoscR<<" iteracjach"<<endl;
                                                 
    cout<<"\n --- wartosci wlasne ---"<<endl;
    for (int i=1; i<=n; i++)
    {
      cout<<"("<<i<<") "<<fixed<<D[i]<<"\t";
    }
    cout<<"\n\n --- wektory wlasne ---\n";
    for (j=1; j<=n; j++) 
    {
      zmax=Z[1][j];
      for (i=2; i<=n; i++)
	    if (fabs(Z[i][j]) > fabs(zmax))   zmax=Z[i][j];
      for (i=1; i<=n; i++)
		  Z[i][j]/=zmax;
    }
  
      for (j=1; j<=n; j++) 
    {
      for (i=1; i<=n; i++)
		  cout<<"  "<<fixed<<Z[j][i]<<"\t";
      cout<<endl;
    }
 cout<<endl;
}

