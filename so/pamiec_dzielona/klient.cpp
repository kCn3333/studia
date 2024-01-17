#include "semafor.h"
#include "pd.h"

char tab[SIZE];

using namespace std;

int main ()
{
char *wsk;

int p,k,;
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
     <<"\n ====K=O=N=S=U=M=E=N=T===="
     <<"\n =========================\n";

while (1)
{
V(k);
P(p);
cout <<"\n odebrane dane : "<<wsk;
}

}
