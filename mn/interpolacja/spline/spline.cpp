#include <stdio.h>
#include <math.h>
#include <iostream>

#define  NMAX  100
#define  krok  0.01

using namespace std;

  int    N;                       //Number of given points
  double X[NMAX],Y[NMAX];         //Coordinates of N points
  double B[NMAX],C[NMAX],D[NMAX]; //Coefficients of cubic spline
  double X1[6], Y1[6];
  double U,V;                     //Coordinates of interpolated point

  double SEVAL(int N, double U, double *X, double *Y, double *B, double *C, double *D)  
{

//  Labels: e10, e20, e30
    double DX; int I,J,K;
      I=1;
//    BINARY SEARCH
      if (I >= N)  I = 1;
      if (U < X[I]) goto e10;
      if( U <= X[I+1]) goto e30;
e10:  I = 1;
      J = N+1;
e20:  K = (I+J) / 2;
      if (U < X[K])  J = K;
      if (U >= X[K]) I = K;
      if (J > I+1) goto e20;
//    SPLINE EVALUATION
e30:  DX = U-X[I];
      return (Y[I]+DX*(B[I]+DX*(C[I]+DX*D[I])));
  }

    void SPLINE (int N, double *X, double *Y, double *B, double *C, double *D)  
{

//  Labels:  e15, e50
      int I, L, NM1;
      double T;

      NM1 = N - 1;

      if (N < 2) return;;
      if (N < 3) goto e50;

//    BUILD THE TRIDIAGONAL SYSTEM
//    B (DIAGONAL), D (UPPERDIAGONAL) , C (SECOND MEMBER)

      D[1] = X[2]-X[1];
      C[2] = (Y[2]-Y[1])/D[1];
      for (I = 2; I<N; I++) 
      {
        D[I] = X[I+1]-X[I];
        B[I] = 2.0*(D[I-1]+D[I]);
        C[I+1] = (Y[I+1]-Y[I])/D[I];
        C[I] = C[I+1]-C[I];
      }

//    CONDITIONS AT LIMITS
//    THIRD DERIVATIVES OBTAINED BY DIVIDED DIFFERENCES

      B[1] = -D[1];
      B[N] = -D[N-1];
      C[1] = 0.0;
      C[N] = 0.0;
      if (N == 3) goto e15;
      C[1] = C[3]/(X[4]-X[2])-C[2]/(X[3]-X[1]);
      C[N] = C[N-1]/(X[N]-X[N-2])-C[N-2]/(X[N-1]-X[N-3]);
      C[1] = C[1]*D[1]*D[1]/(X[4]-X[1]);
      C[N] = -C[N]*D[N-1]*D[N-1]/(X[N]-X[N-3]);

//    FORWARD ELIMINATION

e15:  for (I = 2; I<=N; I++) 
      {
        T = D[I-1]/B[I-1];
        B[I] = B[I]-T*D[I-1];
        C[I] = C[I]-T*C[I-1];
      }

//    BACK SUBSTITUTION

      C[N] = C[N]/B[N];
      for  (L = 1; L<N; L++) 
      {
        I = N-L;
        C[I] = (C[I]-D[I]*C[I+1])/B[I];
      }

//    COEFFICIENTS OF 3RD DEGREE POLYNOMIAL

      B[N] = (Y[N]-Y[NM1])/D[NM1]+D[NM1]*(C[NM1]+2.0*C[N]);
      for (I = 1; I<N; I++) 
      {
        B[I] = (Y[I+1]-Y[I])/D[I]-D[I]*(C[I+1]+2.0*C[I]);
        D[I] = (C[I+1]-C[I])/D[I];
        C[I] = 3.0*C[I];
      } 
      C[N] = 3.0*C[N];
      D[N] = D[NM1];
      return;

//    CASE N = 2

e50:  B[1] = (Y[2]-Y[1])/(X[2]-X[1]);
      C[1] = 0.0;
      D[1] = 0.0;
      B[2] = B[1];
      C[2] = 0.0;
      D[2] = 0.0;
}

int main()  
{
 int n=1;

for (double k=-1.0; k<=1.0; n++)
{
  X[n]=k; Y[n]=1.0/(1.0+5*k*k); k+=1.0/32.0; 
}
n=n-1;
  
  N=n;

  SPLINE (N,X,Y,B,C,D);

cout <<"\n interpolacja splajnem kubicznym (krok="<<krok<<") \n"<<endl;
cout <<"\tX\t    Y";
for(U=X[1]+krok; U<=X[n]; U+=krok)
{
V=SEVAL(N,U,X,Y,B,C,D);  
cout <<fixed<<"\n "<<U<<" \t"<<V;
}
cout <<endl<<endl;
}



