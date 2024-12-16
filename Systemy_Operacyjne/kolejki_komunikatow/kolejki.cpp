#include "msg.h"

int utworz(key_t key)
{
  int msg_id;
  if ((msg_id = msgget(key, IPC_CREAT | 0666)) == -1)
  {
    perror("\n #blad funkcji msgget\n");
    exit(EXIT_FAILURE);
  }
  return msg_id;
}

void usun(int msg_id)
{
  if (msgctl(msg_id, IPC_RMID, 0))
  {
    perror("\n #blad funkcji msgctl\n");
    exit(EXIT_FAILURE);
  }
}

void wyslij(int msg_id, class wiadomosc *msg)
{
  if (msgsnd(msg_id, msg, sizeof(*msg), 0))
  {
    perror("\n #blad funkcji msgsnd\n");
    exit(EXIT_FAILURE);
  }
}

void odbierz(int msg_id, class wiadomosc *msg)
{
  if (msgrcv(msg_id, msg, sizeof(*msg), msg->odbiorca, 0) == -1)
  {
    perror("\n #blad funkcji msgrcv\n");
    exit(EXIT_FAILURE);
  }
}
