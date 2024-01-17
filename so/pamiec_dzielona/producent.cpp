#include "semafor.h"
#include "pd.h"

char tab[SIZE];

void czysc(char * tab, int size)
{
for (int i=0;i<size;i++)
tab[i]=0;
}

using namespace std;

int main ()
{
char *wsk;

int p,k,i;
key_t key_p;
key_t key_k;

if((key_p=ftok(".",'P'))==-1)		
{ perror("\n #blad funkcji ftok\n");
exit(EXIT_FAILURE); }
if((key_k=ftok(".",'K'))==-1)
{ perror("\n #blad funkcji ftok\n");
exit(EXIT_FAILURE); }

p=tworz(key_p);
k=tworz(key_k);

inicjuj(p,1); 		// tworzenie semaforow
inicjuj(k,1); 

wsk=pd(ftok(".",'M'));

cout <<"\n ========================="
     <<"\n ====P=R=O=D=U=C=E=N=T===="
     <<"\n =========================\n";


cout <<endl;

for (i=1;;i++)
{
P(k);
czysc(tab,SIZE);
cout <<" dane do wyslania : ";
cin >> tab;
strcpy(wsk,tab);
czysc(tab,SIZE);

V(p);
}

}
