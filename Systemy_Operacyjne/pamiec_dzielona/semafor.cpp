/*
PAWEL KWIECIEN
--------------
- SEMAFORY -
*/

#include "semafor.h"

using namespace std;

// -------------------- tworzenie semafora --------------------
int tworz(key_t key)
{
int s_id=semget(key,1,IPC_CREAT|0777);
if(s_id==-1)
  { 
    perror("\n#blad tworzenia semafora");
    exit(EXIT_FAILURE);
  }
return s_id;
}
// -------------------- inicjalizacja semafora --------------------
void inicjuj(int s_id,int val)
{
union semun arg;
arg.val=val;
if(semctl(s_id,0,SETVAL,arg)==-1)
  {
    perror("\n#blad inicjalizacji semafora");
    exit(EXIT_FAILURE);
  }
}
// -------------------- INFO --------------------
void info(int s_id)
{
int s_val, s_czekaj;
s_val=semctl(s_id,0,GETVAL,0);
if(s_val==-1)
  {
    perror("\n#blad funkcji info\n");
    exit(EXIT_FAILURE);
  }
cout <<"\t***\tSEMAFOR "<<s_id<<"\t***";
cout <<"\n\t***\tO WARTOSCI "<<s_val<<"\t***"; 
s_czekaj=semctl(s_id,0,GETNCNT);
if(s_czekaj==-1)
  {
    perror("\n#blad funkcji info 2\n");
    exit(EXIT_FAILURE);
  }
cout <<"\n\t"<<s_czekaj<<" procesow czekajacych na semafor";
}
// -------------------- P --------------------
void P(int s_id)
{
struct sembuf buf[1];
buf[0].sem_num=0;
buf[0].sem_op=-1;
buf[0].sem_flg=0;
if(semop(s_id,buf,1)==-1)
  {
    perror("\n#blad operacji P");
    exit(EXIT_FAILURE);
  }
}
// -------------------- V --------------------
void V(int s_id)
{
struct sembuf buf[1];
buf[0].sem_num=0;
buf[0].sem_op=1;
buf[0].sem_flg=0;
if(semop(s_id,buf,1)==-1)
  {
    perror("\n#blad operacji V");
    exit(EXIT_FAILURE);
  }
}
// -------------------- usuwanie --------------------
void usun(int s_id)
{
if(semctl(s_id,0,IPC_RMID)==-1)
  {
    perror("\n#blad usuwania semafora");
    exit(EXIT_FAILURE);
  }
}
