/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|		                  - DRZEWO AVL -   		            	  |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>

using namespace std;

struct W // Wezel
{
  long int wartosc;
  W *lewy;      // wskaznik do lewego poddrzewa
  W *prawy;     // wskaznik do lewego poddrzewa
  int wysokosc; // wysokosc drzewa
};

typedef struct W *ww;

class AVL
{
public:
  // ww root;
  void wstaw(int, ww &); // wstawianie do drzewa
  void czysc(ww &);      // czysci drzewo
  void inorder(ww);      // wypisuje wartosci rosnaco
  int wysokosc(ww);      // zwraca wysokosc drzewa

  ww rot1L(ww &); // rotacja pojedyncza w lewo
  ww rot2L(ww &); // rotacja podwojna w lewo
  ww rot1P(ww &); // rotacja pojedyncza w prawo
  ww rot2P(ww &); // rotacja podwojna w prawo
};
int max(int, int);

//--------------------------------------------------------------
void AVL::wstaw(int x, ww &p)
{
  if (p == NULL) // jesli drzewo jest puste
  {
    p = new W;      // tworzy nowy wezel
    p->wartosc = x; // i nadaje mu wartosc
    p->lewy = NULL;
    p->prawy = NULL;
    p->wysokosc = 0;
  }
  else
  {
    if (x < p->wartosc)
    {
      wstaw(x, p->lewy); // do lewego poddrzewa
      if ((wysokosc(p->lewy) - wysokosc(p->prawy)) == 2)
      { // rownowazenie
        if (x < p->lewy->wartosc)
          p = rot1L(p);
        else
          p = rot2L(p);
      }
    }
    else if (x > p->wartosc)
    {
      wstaw(x, p->prawy); // do prawego poddrzewa
      if ((wysokosc(p->prawy) - wysokosc(p->lewy)) == 2)
      { // rownowazenie
        if (x > p->prawy->wartosc)
          p = rot1P(p);
        else
          p = rot2P(p);
      }
    }
    else
      cout << "\n wartosc " << x << " juz jest w drzewie" << endl;
  }
  p->wysokosc = max(wysokosc(p->lewy), wysokosc(p->prawy)) + 1;
}
//--------------------------------------------------------------
void AVL::czysc(ww &p)
{
  ww k;
  if (p != NULL)
  {
    czysc(p->lewy);
    czysc(p->prawy);
    k = p;
    free(k);
    p = NULL;
  }
}
//--------------------------------------------------------------
void AVL::inorder(ww p)
{
  if (p != NULL)
  {
    inorder(p->lewy);
    cout << p->wartosc << "-->";
    inorder(p->prawy);
  }
}
//--------------------------------------------------------------
int max(int x1, int x2) { return ((x1 > x2) ? x1 : x2); } // zwraca wieksza z liczb
//--------------------------------------------------------------
int AVL::wysokosc(ww p)
{
  int h;
  if (p == NULL)
    return -1;
  else
  {
    h = p->wysokosc;
    return h;
  }
}
//--------------------------------------------------------------
ww AVL::rot1L(ww &p1) // pojedyncza rotecja w lewo
{
  ww p2;
  p2 = p1->lewy;
  p1->lewy = p2->prawy;
  p2->prawy = p1;
  p1->wysokosc = max(wysokosc(p1->lewy), wysokosc(p1->prawy)) + 1;
  p2->wysokosc = max(wysokosc(p2->lewy), p1->wysokosc) + 1;
  return p2;
}
//--------------------------------------------------------------
ww AVL::rot1P(ww &p1) // pojedyncza rotacja w prawo
{
  ww p2;
  p2 = p1->prawy;
  p1->prawy = p2->lewy;
  p2->lewy = p1;
  p1->wysokosc = max(wysokosc(p1->lewy), wysokosc(p1->prawy)) + 1;
  p2->wysokosc = max(p1->wysokosc, wysokosc(p2->prawy)) + 1;
  return p2;
}
//--------------------------------------------------------------
ww AVL::rot2L(ww &p1) // podwojna rotacja w lewo
{
  p1->lewy = rot1P(p1->lewy); // pojedyncza w prawo
  return rot1L(p1);           // pojedyncza w lewo
}
//--------------------------------------------------------------
ww AVL::rot2P(ww &p1) // podwojna rotacja w prawo
{
  p1->prawy = rot1L(p1->prawy); // pojedyncza w lewo
  return rot1P(p1);             // pojedyncza w prawo
}
//--------------------------------------------------------------
int main()
{
  ww root = NULL;
  AVL tree;
  int menu, n;

  cout << "\n\t >> DRZEWO AVL <<\n"
       << endl;
  cout << "\t--------------------------------------------\n";
  cout << "\t--> dodaj element do drzewa            1 <--\n";
  cout << "\t--> wyswietl elementy drzewa (rosnaco) 2 <--\n";
  cout << "\t--> wyjscie                            0 <--\n";
  cout << "\t--------------------------------------------\n";
  while (1)
  {
    cout << ">";
    cin >> menu;
    switch (menu)
    {
    case 0:
      exit(1);
    case 1:
    {
      cout << " podaj wartosc jaka dodac do drzewa: ";
      cin >> n;
      tree.wstaw(n, root);
      break;
    }
    case 2:
    {
      tree.inorder(root);
      cout << endl;
      break;
    }
    default:
      cout << "\n :: bledna wartosc ::\n";
      break;
    }
  }
  tree.czysc(root);
  return 0;
}
