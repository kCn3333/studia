/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|         program porownuje przeszukiwanie liniowe        |
|               i przeszukiwanie drzewa BST               |
|                                                         |
|                                                         |
|---------------------------------------------------------*/

#include <sys/timeb.h>
#include <iostream>
#include <time.h>
#include <cstdlib>

#define DANE 1000000 // ilosc danych
#define ITER 1000    // ilosc przeszukiwan

using namespace std;

class BinarySearchTree
{
private:
  struct tree_node
  {
    tree_node *left;  // lewy potomek
    tree_node *right; // prawy potomek
    int data;         // wartosc
  };
  tree_node *root; // korzen
public:
  BinarySearchTree() { root = NULL; }
  bool isEmpty() const { return root == NULL; }
  void insert(int);
  int search(int);
};
//-----------------------------------------------------------
void BinarySearchTree::insert(int d)
{
  tree_node *t = new tree_node;
  tree_node *parent;
  t->data = d;
  t->left = NULL;
  t->right = NULL;
  parent = NULL;
  if (isEmpty())
    root = t; // czy nie puste drzewo
  else
  {
    tree_node *curr;
    curr = root; // znajduje rodzica elementu wstawianego
    while (curr)
    {
      parent = curr;
      if (t->data > curr->data)
        curr = curr->right;
      else
        curr = curr->left;
    }
    if (t->data < parent->data)
      parent->left = t;
    else
      parent->right = t;
  }
}
//-----------------------------------------------------------
int BinarySearchTree::search(int d)
{
  int k = 0; // licznik porownan
  tree_node *curr;
  tree_node *parent;
  curr = root;
  while (curr != NULL)
  {
    k++;
    if (curr->data == d)
      return k;
    else
    {
      parent = curr;
      if (d > curr->data)
      {
        curr = curr->right;
        k++;
      }
      else
      {
        curr = curr->left;
        k++;
      }
    }
  }
  // cout<<"\n BST - nie znaleziono "<<endl;
  return k;
}
//-----------------------------------------------------------
double pomiar_czasu() // funkcja mierzaca czas
{
  struct timeb czas;
  double wynik;
  // wypelnia strukture 'czas' biezacym czasem
  ftime(&czas);
  // teraz mamy:
  // * czas.time - liczba sekund, ktore uplynely od godziny
  //   00:00 czasu GMT dnia 1.01.1970
  // * czas.millitm - offset w milisekundach
  // - skonwertuj czas do typu double
  wynik = (double)czas.time;
  wynik += (double)czas.millitm / 1000.0;
  return wynik;
}
//-----------------------------------------------------------

int main()
{
  srand(time(0));
  int tmp, n = 0;
  double czas_start, czas_stop, czasT = 0, czasBST = 0, czasG = 0;
  unsigned long a = 0, b = 0;
  // int TMP[DANE];
  int *TMP = new int[DANE];
  BinarySearchTree T;

  cout << "\n ----------------------------------------------------\n"
       << " - porownanie przeszukiwania liniowego i drzewa BST -\n"
       << " - 1 000 razy losowa liczbe sposrod 1 000 000 liczb -\n"
       << " ----------------------------------------------------" << endl;

  cout << "\n #generowanie danych..." << endl;
  czas_start = pomiar_czasu();
  for (int i = 0; i < DANE; i++)
  {
    tmp = rand();
    TMP[i] = tmp;
    T.insert(tmp);
  }
  czas_stop = pomiar_czasu();
  czasG = czas_stop - czas_start;
  cout << "\tdane wygenerowane w czasie " << czasG << " sek.\n"
       << endl;

  cout << endl
       << " #szukanie w tablicy..." << endl;
  czas_start = pomiar_czasu();
  for (int i = 0; i < ITER; i++)
  {
    tmp = rand();
    for (int i = 0; i < DANE; i++)
    {
      if (TMP[i] == tmp)
        break;
      a++;
    }
  }
  czas_stop = pomiar_czasu();
  czasT = czas_stop - czas_start;
  cout << "\n\tczas: " << czasT << " sek.\n\t\t srednio porownan: " << a / 1000;

  cout << endl
       << "\n #szukanie w BST..." << endl;
  czas_start = pomiar_czasu();
  for (int i = 0; i < ITER; i++)
  {
    tmp = rand();
    n += T.search(rand());
  }
  czas_stop = pomiar_czasu();
  czasBST = czas_stop - czas_start;
  cout << "\n\tczas: " << czasBST << " sek. \n\t\t srednio porownan: " << n / 1000 << endl
       << endl;

  delete TMP;
  return 0;
}
