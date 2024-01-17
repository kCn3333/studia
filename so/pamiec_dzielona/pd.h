#ifndef PD_H
#define PD_H

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 1024 

using namespace std;

char* pd(key_t key);

#endif
 
