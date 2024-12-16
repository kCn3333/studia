//---------------
// -KLIENT SMTP-
//---------------
// autor:
// Pawel Kwiecien

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include "base64.h"

#define smtp 25 // port smtp
#define DATA "DATA\n"
#define QUIT "QUIT\n"
#define SIZE 800 // rozmiar bufora

using namespace std;

int sock, len;			   // gniazdo
struct sockaddr_in server; // adres serwera
struct hostent *h;
char buf[SIZE + 1];
char tab[SIZE + 1];
string pass, login;
bool yes = 0;
FILE *plik;

void clear(char tab[])
{ // czyszenie bufora
	for (int i = 0; i <= SIZE; i++)
		tab[i] = 0;
}

void send_socket(const char *s)
{
	write(sock, s, strlen(s));
}

void read_socket()
{
	len = read(sock, buf, SIZE);
	buf[len] = '\0';
	cout << buf;
	if (buf[0] != '2')
		yes = 1; // jesli smtp zwroci blad
	else
		yes = 0;
	clear(buf);
}

int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		cout << " obsluga: " << argv[0] << " <host> <plik.txt>\n\n";
		exit(1);
	}

	cout << "\n -------------------"
		 << "\n -][ KLIENT SMTP ][-"
		 << "\n -------------------\n"
		 << endl;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	} // utworzenie gnizda

	server.sin_family = AF_INET;
	if ((h = gethostbyname(argv[1])) == NULL) // pobiera informacje o hoscie
	{
		perror("gethostbyname");
		exit(2);
	}

	memcpy((char *)&server.sin_addr, (char *)h->h_addr, h->h_length);
	server.sin_port = htons(smtp); // port smtp

	if (connect(sock, (struct sockaddr *)&server, sizeof server) == -1)
	{
		perror("connect");
		exit(1);
	} // laczy sie z serwerem

	read_socket();				// server odpowiada
	send_socket("HELO USER\n"); // przedstawia sie
	read(sock, buf, SIZE);		// odpowiedz serwera

	do
	{
		cout << "\n\t LOGIN: ";
		cin >> login;
		send_socket("AUTH LOGIN\n"); // logowanie do serwera
		read(sock, buf, SIZE);
		pass = base64_encode(reinterpret_cast<const unsigned char *>(login.c_str()), login.length());
		send_socket(reinterpret_cast<const char *>(pass.c_str()));
		send_socket("\n");
		read(sock, buf, SIZE);

		login = getpass("\t HASLO: "); // haslo i login zakodowane base64
		cout << "\t\t*****\n\n";
		pass = base64_encode(reinterpret_cast<const unsigned char *>(login.c_str()), login.length());
		send_socket(reinterpret_cast<const char *>(pass.c_str()));
		send_socket("\n");
		read_socket();
		pass.clear(); // czysci login i haslo
		login.clear();
	} while (yes);

	cout << "\n ---------------------------------------"
		 << "\n twoj adres e-mail: ";
	cin >> tab;
	send_socket("mail from:<"); // mail from
	send_socket(tab);
	send_socket(">\n");
	read(sock, buf, SIZE); // sender OK

	cout << " adres odbiorcy: ";
	cin >> tab;
	send_socket("rcpt to:<"); // mail to
	send_socket(tab);
	send_socket(">\n");
	read(sock, buf, SIZE); // recipient OK

	send_socket(DATA);
	read(sock, buf, SIZE); // ok to send
	cout << " ---------------------------------------";

	cout << "\n tresc wiadomosci (z pliku " << argv[2] << "):\n\n";
	if ((plik = fopen(argv[2], "r")) == NULL) // otwiera plik
	{
		cout << "\n#blad otwarcia pliku " << argv[2] << endl;
		exit(3);
	}
	while (1)
	{
		if (fgets(tab, SIZE, plik) == NULL)
			break;		  // wysyla zawartosc pliku
		send_socket(tab); // jako tresc e-maila
		cout << tab;
	}
	fclose(plik);
	cout << "\n ---------------------------------------" << endl;

	send_socket("\n.\n");
	read(sock, buf, SIZE);
	if (buf[1] == '5') // jesli smtp nie zwroci bledu
		cout << " wiadomosc wyslana...\n"
			 << endl;
	else
	{
		cout << "#blad wysylania wiadomosci (prawdopodobnie podano zly adres)" << endl;
		exit(4);
	}
	send_socket(QUIT); // quit
	read_socket();
	close(sock); // zamyka gniazdo
	exit(0);
}
