// KLIENT UDP
// -----------
// autor:
// Pawel Kwiecien

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>

#define PORT 4950

using namespace std;

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in their_addr;
    struct hostent *h;
    int numbytes;
    char buf[300];

    if (argc != 2)
    {
        cout << "\nobsluga: " << argv[0] << " host port\n";
        exit(1);
    }
    if ((h = gethostbyname(argv[1])) == NULL) // pobiera info o hoscie
    {
        perror("gethostbyname");
        exit(1);
    }
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;   // host byte order
    their_addr.sin_port = htons(PORT); // short, network byte order
    their_addr.sin_addr = *((struct in_addr *)h->h_addr);
    memset(&(their_addr.sin_zero), '\0', 8); // zeruje reszte struktury

    cout << "\n podaj tekst do wyslania: ";
    cin.getline(buf, 300, '\n');

    if ((numbytes = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1)
    {
        perror("sendto");
        exit(1);
    }

    socklen_t addr_len = sizeof(struct sockaddr);
    socklen_t *l = &addr_len;

    if (recvfrom(sockfd, buf, 300, 0, (struct sockaddr *)&their_addr, l) == -1)
        perror("recv");
    cout << " SERWER: " << buf << endl;

    close(sockfd);
    return 0;
}
