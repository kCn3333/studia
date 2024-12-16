// KLIENT FTP
// -----------
// autor:
// Pawel Kwiecien

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "connectsock.cpp"

#define LINELEN 100
using namespace std;
int port;
ofstream plik;

int send(int sock, char *line)
{
    cout << "=======================" << endl;
    cout << "LINE: " << line;
    cout << "LINE(int):";
    for (int i = 0; i < strlen(line); i++)
    {
        cout << (int)(line[i]);
    }
    cout << endl;
    write(sock, line, strlen(line));
    cout << "KONIEC WYSYLANIA" << endl;
    cout << "=======================" << endl;
}

int recive(int sock)
{
    int n;
    char buf[LINELEN + 1] = " ";
    cout << "***********************" << endl;
    cout << "POBIERAM" << endl;
    plik.open("index.html");
    while ((n = read(sock, buf, LINELEN)) > 0)
    {
        buf[n] = '\0';
        cout << buf;
        plik << buf;
    }
    cout << "***********************" << endl;
}

int send_recive(int sock, char *line)
{
    int n1, n2, a, b;
    char buf[LINELEN + 1];
    cout << "=======================" << endl;
    cout << "LINE: " << line;
    cout << "LINE(int):";
    for (int i = 0; i < strlen(line); i++)
    {
        cout << (int)(line[i]);
    }
    cout << endl;
    n1 = write(sock, line, strlen(line));
    cout << "KONIEC WYSYLANIA" << endl;
    cout << "=======================" << endl;
    cout << "***********************" << endl;
    cout << "POBIERAM" << endl;
    while (n1 > 0 && (n2 = read(sock, buf, LINELEN)) > 0)
    {
        buf[n2] = '\0';
        n1 -= n2;
        cout << buf;
    }
    cout << endl;
    if (line == "PASV\r\n")
    {
        cout << "Nowy Port!" << endl;
        sscanf(buf, "%*d%*s%*s%*s%*c%*c%*d%*c%*d%*c%*d%*c%*d%*c%d%*c%d", &a, &b);
        port = (a * 256) + b;
        cout << "Port: " << port << endl;
    }
    cout << "***********************" << endl;
}

int main(int argc, char **argv)
{
    int s, r, n;
    char buf[LINELEN + 1];
    char user[50];
    char pass[15];
    char sport[25];
    sprintf(user, "USER %s\r\n", argv[2]);
    sprintf(pass, "PASS %s\r\n", argv[3]);
    if (argc < 4)
    {
        cout << "sposob uzycia: ftp [serwer] [user] [password]" << endl;
        return 0;
    }
    cout << "Klient - FTP" << endl;
    cout << "============================================" << endl;
    cout << "login: " << user << " Haslo: " << pass << endl;
    s = connectsock(argv[1], "ftp", "tcp");
    if (s < 0)
        return 0;
    send_recive(s, user);
    send_recive(s, pass);
    send_recive(s, "SYST\r\n");
    send_recive(s, "PASV\r\n");
    // nowe gniazdo
    sprintf(sport, "%d", port);
    r = connectsock(argv[1], sport, "tcp");
    // polecenie LIST
    send_recive(s, "LIST\r\n");
    recive(r);
    // polecenie RETR
    send(s, "RETR /index.html\r\n");
    recive(r);
    // polecenie QUIT
    send(s, "QUIT\r\n");
    recive(r);
    // koniec
    if (shutdown(s, SHUT_RDWR) < 0)
    {
        cout << "Problem z zamknieciem polaczenia" << endl;
        return 0;
    }
    return 1;
}