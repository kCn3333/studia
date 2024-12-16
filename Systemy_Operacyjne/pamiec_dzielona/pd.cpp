#include "pd.h"

using namespace std;

char* pd(key_t key) 
{
int pd_id;
char* r;
if((pd_id=shmget(key,0,IPC_CREAT|0666))==-1)
{ perror("\n #blad funkcji shmget\n");
exit(EXIT_FAILURE); }
r=static_cast<char*>(shmat(pd_id,0,0));
return r;
}
