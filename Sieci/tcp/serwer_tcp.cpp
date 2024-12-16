// Serwer TCP
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
#include <sys/wait.h>
#include <signal.h>

#define MYPORT 3490 // port, z ktorym beda sie laczyli uzytkownicy
#define M 100       // pojemnosc bufora
#define BACKLOG 10  // jak duzo moze byc oczekujacych polaczen w kolejce

using namespace std;

void sigchld_handler(int s)
{
    while (wait(NULL) > 0)
        ;
}

int main()
{
    char buf[100];                 // bufor
    int n, a, b = 0;               // zmienne pomocnicze
    int sockfd, new_fd;            // nasluchuje na sock_fd, nowe polaczenia na new_fd
    struct sockaddr_in my_addr;    // adres serwera
    struct sockaddr_in their_addr; // informacja o adresie klienta
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;

    cout << "\n     __________";
    cout << "\n  >> serwer tcp <<\n"
         << endl;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }

    my_addr.sin_family = AF_INET;         // host - byte order
    my_addr.sin_port = htons(MYPORT);     // network byte order
    my_addr.sin_addr.s_addr = INADDR_ANY; // uzupelnia adres IP
    memset(&(my_addr.sin_zero), '\0', 8); // zeruje reszte struktury

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // zbiera martwe procesy
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    cout << " adres serwera: " << inet_ntoa(my_addr.sin_addr) << "\n"
         << endl;
    while (1)
    { // glowna petla accept()
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
        {
            perror("accept");
            continue;
        }
        cout << " SERWER: poloczenie z " << inet_ntoa(their_addr.sin_addr) << endl;
        if (!fork())
        {                  // to jest proces potomny
            close(sockfd); // nie potrzebuje gniazda nasluchujacego
            if (write(new_fd, " SERWER: polaczony...\n", 23) < 0)
                perror("write");
            for (int i = 0; i < 2; i++)
            {
                if ((n = read(new_fd, buf, M - 1)) < 0)
                    perror("read");
                buf[n] = '\0';
                sscanf(buf, "%d", &a);
                b = b + a;
                for (int i = 0; i < M; i++)
                    buf[i] = 0;
            }
            sprintf(buf, "suma = %d", b);
            if (write(new_fd, &buf, M) < 0)
                perror("write");

            close(new_fd);
            exit(0);
        }
        close(new_fd);
    }
    return 0;
}
