#ifndef MSG_H
#define MSG_H

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define m_size 100

class wiadomosc
{
public:
    long odbiorca;
    long nadawca;
    char msg[m_size];
};

int utworz(key_t key);
void usun(int msg_id);
void wyslij(int msg_id, class wiadomosc *msg);
void odbierz(int msg_id, class wiadomosc *msg);

#endif
