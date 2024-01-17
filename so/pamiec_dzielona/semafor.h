/*
PAWEL KWIECIEN
--------------
- SEMAFORY -
*/

#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

using namespace std;

union semun 
{
int val;
struct semid_ds *buf;
ushort *array;
};

int tworz(key_t key);
void inicjuj(int s_id,int val);
void info(int s_id);
void P(int s_id);
void V(int s_id);
void usun(int s_id);

#endif
