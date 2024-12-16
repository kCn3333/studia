/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|                  5.cpp mnozenie macierzy                |
|                   algorytmem Strassena                  |
|                                                         |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>

using namespace std;

typedef float **matrix;

//-------------------------------------------------
void wypisz(int n, float **x) // wypisuje macierz
{
  cout << "\n --- macierz C = A * B ---\n\n ";
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cout << x[i][j] << "\t";
    }
    cout << "\n\n ";
  }
  cout << "\n";
}
//-------------------------------------------------
void dodaj(int n, float **a, float **b, float **c)
{ // dodaje macierze
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      c[i][j] = a[i][j] + b[i][j];
  }
}
//-------------------------------------------------
void odejmij(int n, float **a, float **b, float **c)
{ // odejmuje macierze
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      c[i][j] = a[i][j] - b[i][j];
  }
}

//-------------------------------------------------
//-------------------------------------------------
void strassen(int n, float **A, float **B, float **C)
{
  if (n == 1)
    C[0][0] = (A[0][0]) * (B[0][0]);
  else
  {
    int k = n / 2;

    matrix a11, a12, a21, a22, b11, b12, b21, b22, c11, c12, c21, c22; // wskazniki do wskaznikow
    matrix m1, m2, m3, m4, m5, m6, m7;
    matrix h1, h2;

    // alokacja tablic pomocniczych (podmacierze)

    a11 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      a11[i] = new float[k];
    }
    a12 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      a12[i] = new float[k];
    }
    a21 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      a21[i] = new float[k];
    }
    a22 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      a22[i] = new float[k];
    }
    b11 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      b11[i] = new float[k];
    }
    b12 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      b12[i] = new float[k];
    }
    b21 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      b21[i] = new float[k];
    }
    b22 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      b22[i] = new float[k];
    }
    c11 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      c11[i] = new float[k];
    }
    c12 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      c12[i] = new float[k];
    }
    c21 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      c21[i] = new float[k];
    }
    c22 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      c22[i] = new float[k];
    }

    m1 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      m1[i] = new float[k];
    }
    m2 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      m2[i] = new float[k];
    }
    m3 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      m3[i] = new float[k];
    }
    m4 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      m4[i] = new float[k];
    }
    m5 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      m5[i] = new float[k];
    }
    m6 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      m6[i] = new float[k];
    }
    m7 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      m7[i] = new float[k];
    }
    h1 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      h1[i] = new float[k];
    }
    h2 = new float *[k];
    for (int i = 0; i < k; i++)
    {
      h2[i] = new float[k];
    }

    for (int i = 0; i < k; i++)
    {
      for (int j = 0; j < k; j++) // rozdziela macierze A i B
      {                           // na 4 podmacierze
        a11[i][j] = A[i][j];
        a12[i][j] = A[i][j + k];
        a21[i][j] = A[i + k][j];
        a22[i][j] = A[i + k][j + k];
        b11[i][j] = B[i][j];
        b12[i][j] = B[i][j + k];
        b21[i][j] = B[i + k][j];
        b22[i][j] = B[i + k][j + k];
      }
    }

    //--------------------
    dodaj(k, a11, a22, h1); // M1
    dodaj(k, b11, b22, h2);
    strassen(k, h1, h2, m1);
    //--------------------
    dodaj(k, a21, a22, h1); // M2
    strassen(k, h1, b11, m2);
    //--------------------
    odejmij(k, b12, b22, h1); // M3
    strassen(k, a11, h1, m3);
    //--------------------
    odejmij(k, b21, b11, h1); // M4
    strassen(k, a22, h1, m4);
    //--------------------
    dodaj(k, a11, a12, h1); // M5
    strassen(k, h1, b22, m5);
    //--------------------
    odejmij(k, a11, a21, h1); // M6
    dodaj(k, b11, b12, h2);
    strassen(k, h1, h2, m6);
    //--------------------
    odejmij(k, a12, a22, h1); // M7
    dodaj(k, b21, b22, h2);
    strassen(k, h1, h2, m7);
    //--------------------
    //--------------------
    //--------------------
    dodaj(k, m1, m4, h1); // C11
    odejmij(k, h1, m5, h2);
    dodaj(k, h2, m7, c11);
    //--------------------
    dodaj(k, m3, m5, c12); // C12
    //--------------------
    dodaj(k, m2, m4, c21); // C21
    //--------------------
    dodaj(k, m1, m3, h1); // C22
    odejmij(k, h1, m2, h2);
    dodaj(k, h2, m6, c22);
    //--------------------

    for (int i = 0; i < k; i++)
    {
      for (int j = 0; j < k; j++) // scalanaie podmacierzy
      {                           // w jedna macierz C
        C[i][j] = c11[i][j];
        C[i][j + k] = c12[i][j];
        C[i + k][j] = c21[i][j];
        C[i + k][j + k] = c22[i][j];
      }
    }
    delete a11, a12, a21, a22, b11, b12, b21, b22, c11, c12, c21, c22;
    delete m1, m2, m3, m4, m5, m6, m7, h1, h2; // usuwanie tablic pomocniczych
  }
}
//-------------------------------------------------

main()
{
  matrix A, B, C; // **A, **B, **C
  int m = 0;      // rozmiar wczytany
  int n;          // rozmiar zaalokowany

  cout << "\n\t::::::   mnozenie maciezy  ::::::\n"
       << "\t::::::  algorytm Strassena  ::::::\n";
  do
  {
    cout << "\n  podaj rozmiar macierzy do pomnozenia (max 16) : ";
    cin >> m;
  } while ((m <= 1) || (m > 16));

  if ((m == 2) || (m == 4) || (m == 8) || (m == 16)) // dobieranie
    n = m;                                           // wielkosci tablic
  else if (m == 3)                                   // do zaalokowania
    n = 4;
  else if ((m < 8) && (m > 4))
    n = 8;
  else
    n = 16;

  // alokacja tablic odpowiadajacych rozszerzonym macierzom A,B,C

  A = new float *[n];
  for (int i = 0; i < n; i++)
  {
    A[i] = new float[n];
  }
  B = new float *[n];
  for (int i = 0; i < n; i++)
  {
    B[i] = new float[n];
  }
  C = new float *[n];
  for (int i = 0; i < n; i++)
  {
    C[i] = new float[n];
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++) // wypelnianie tablic zerami
      A[i][j] = 0;
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      B[i][j] = 0;
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      C[i][j] = 0;
  }

  cout << "\n --- macierz A ---\n";
  for (int i = 0; i < m; i++) // wczytanie elementow macierzy A
  {
    for (int j = 0; j < m; j++)
    {
      cout << " podaj element A[" << i + 1 << "," << j + 1 << "] macierzy  ";
      cin >> A[i][j];
    }
  }
  cout << "\n --- macierz B ---\n";
  for (int i = 0; i < m; i++) // wczytanie elementow macierzy B
  {
    for (int j = 0; j < m; j++)
    {
      cout << " podaj element B[" << i + 1 << "," << j + 1 << "] macierzy  ";
      cin >> B[i][j];
    }
  }

  strassen(n, A, B, C); // mnozenie macierzy
  wypisz(m, C);         // wypis macierzy wynikowej C

  delete A; // usuwa zaalokowane tablice
  delete B;
  delete C;
}
