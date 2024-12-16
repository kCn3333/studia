// KLIENT TCP
// -----------
// autor:
// Pawel Kwiecien

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 3490 // port z ktorym bedzie sie laczyl
#define M 100     // max danych

using namespace std;

int main(int argc, char *argv[])
{
    int sock_fd, size, n;
    char buf[M];
    struct hostent *h;
    struct sockaddr_in addr;

    if (argc != 2)
    {
        cout << "\n skladnia " << argv[0] << " host\n";
        exit(0);
    }
    if ((h = gethostbyname(argv[1])) == NULL) // pobiera info o hoscie
    {
        perror("gethostbyname");
        exit(0);
    }
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(0);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr = *((struct in_addr *)h->h_addr);
    memset(&(addr.sin_zero), '\0', 8); // zeruje reszte struktury

    cout << "\n >proba polaczenia z " << argv[1] << ":" << PORT << endl;
    if (connect(sock_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(0);
    }

    if ((n = read(sock_fd, buf, M - 1)) == -1)
    {
        perror("recv");
        exit(0);
    }
    buf[n] = '\0';
    cout << buf << endl;
    cout << " wysylanie danych do serwera: \n";
    for (int i = 0; i < 2; i++)
    {
        cout << i + 1 << " liczba: ";
        cin >> buf;
        if (write(sock_fd, buf, M - 1) == -1)
        {
            perror("send");
            exit(0);
        }
    }
    n = read(sock_fd, buf, M - 1);
    buf[n] = '\0';
    cout << "\n SERWER: " << buf << endl;
    close(sock_fd);
    return 0;
}
