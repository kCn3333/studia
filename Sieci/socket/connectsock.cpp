/* biblioteki niezbedne do prawidlowego funkcjonowania programu */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int Socket(int type, char *protocol, struct protoent *ppe)
{
      int S = socket(PF_INET, type, ppe->p_proto); // wywolanie funkcji socket
      if (S < 0)                                   // jezeli zwroci wartosc mniejsza od zera
      {
            fprintf(stderr, "nieznany protokol: %s\n", protocol); // zglaszamy blad
            return -1;
      }
      else
            return S; // gdy zakonczy sie sukcesem, zwracamy S
}

/*********************************************************/

int Connect(int s, char *host, char *service)
{
      struct sockaddr_in sin;                                   // struktura
      int C = connect(s, (struct sockaddr *)&sin, sizeof(sin)); // wywolanie funkcji connect
      if (C < 0)                                                // jezeli zwroci wartosc mniejsza od zera
      {
            fprintf(stderr, "nie moge ustanowic polaczenia z %s:%s %s\n", host, service, strerror(errno)); // blad
            return -1;
      }
      return C; // gdy zakonczy sie sukcesem, zwracamy C
}

/*********************************************************/

int connectsock(char *host, char *service, char *protocol)
{
      struct hostent *phe; // zadeklarowanie zmiennych
      struct servent *pse;
      struct protoent *ppe;
      struct sockaddr_in sin;
      int type, s;

      memset((char *)&sin, 0, sizeof(sin)); // wywolujemy funkcje umieszczajaca w calej strukturze zera

      sin.sin_family = AF_INET;                             // rodzinie adresow nadajemy wartosc AF_INET
      if ((pse = getservbyname(service, protocol)) != NULL) // wywolujemy funkcje konwertujaca usluge na numer portu
      {
            sin.sin_port = pse->s_port; // nadajemy strukturze numer portu
      }
      else if ((sin.sin_port = htons((u_short)atoi(service))) == 0) // wywolujemy funkcje przeksztalcajaca numer portu
      {
            fprintf(stderr, "nieznana usluga: %s\n", service); // wypisujemy blad
            return -1;
      }

      if ((phe = gethostbyname(host)) != NULL) // wywolujemy funkcje okreslajaca adres na podstawie nazwy stacji
      {
            bcopy(phe->h_addr, (char *)&sin.sin_addr, phe->h_length); // kopiujemy dane z jednej wartosci do drugiej
      }
      else if ((sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE) // wywolanie funkcji konwertujace adres IP
      {
            fprintf(stderr, "nieznany host: %s\n", host); // wypisaujemy blad
            return -1;
      }

      if ((ppe = getprotobyname(protocol)) == NULL) // wywolujemy funkcje sprawdzajaca protokol
      {
            fprintf(stderr, "nieznany protokol: %s\n", protocol); // wypisujemy blad
            return -1;
      }

      if (strcmp(protocol, "udp") == 0) // jezeli wybranym protokolem jest UDP
      {
            type = SOCK_DGRAM; // typ datagramowy
      }
      else // w przeciwnym wypadku
      {
            type = SOCK_STREAM; // typ strumieniowy
      }

      s = Socket(type, protocol, ppe); // wywolujemy funkcje tworzaca gniazdo
      s = Connect(s, host, service);
      return s;
}