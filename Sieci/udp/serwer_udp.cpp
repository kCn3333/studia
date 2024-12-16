// SERWER UDP
// -----------
// autor:
// Pawel Kwiecien

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORT 4950
#define MAX 300

using namespace std;

char *strtolower(char *dest, const char *src, size_t n)
{
  if (!n)
  {
    return 0;
  }
  else
  {
    char *d = dest;
    while (*src && --n > 0)
      *d++ = tolower(*src++);
    *d = 0;
    return dest;
  }
}

int main()
{
  int sockfd;
  struct sockaddr_in my_addr;    // informacja o adresie serwera
  struct sockaddr_in their_addr; // informacja o adresie klienta
  int n;
  socklen_t addr_len;
  char buf[MAX], buf1[MAX];

  cout << "\n >> SERWER UDP <<" << endl;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
  {
    perror("socket");
    exit(1);
  }

  my_addr.sin_family = AF_INET;         // host byte order
  my_addr.sin_port = htons(PORT);       // short, network byte order
  my_addr.sin_addr.s_addr = INADDR_ANY; // uzupenia adresem IP
  memset(&(my_addr.sin_zero), '\0', 8); // zeruje reszte struktury

  if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
  {
    perror("bind");
    exit(1);
  }

  addr_len = sizeof(struct sockaddr);
  if ((n = recvfrom(sockfd, buf, MAX - 1, 0, (struct sockaddr *)&their_addr, &addr_len)) == -1)
  {
    perror("recvfrom");
    exit(1);
  }

  strtolower(buf1, buf, n + 1);

  if ((sendto(sockfd, buf1, MAX - 1, 0, (struct sockaddr *)&their_addr, addr_len)) == -1)
  {
    perror("sendto");
    exit(0);
  }

  cout << "\n wiadomosc od " << inet_ntoa(their_addr.sin_addr);
  buf[n] = '\0';
  cout << "\n " << buf1 << endl;

  close(sockfd);
  return 0;
}
