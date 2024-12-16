#include "msg.h"

using namespace std;

void czysc(char *w)
{
	for (int i = 0; i < m_size; i++)
	{
		w[i] = '\0';
	}
}

void duze_litery(char *w)
{
	char z;
	for (int i = 0; i < m_size; i++)
	{
		z = toupper(w[i]);
		w[i] = z;
	}
}

int main()
{
	string exit = "exit";
	key_t key = ftok(".", 'm'); // klucz
	int pid = 123;				// nr procesu
	int k_id = utworz(key);		// kolejkaID utworzonej
								// kolejki komunikatow

	cout << "\n -----------------------------------------------";
	cout << "\n SERWER: Kolejki Komunikatow [kolejkaID " << k_id << "]\n";
	cout << " -----------------------------------------------\n";

	class wiadomosc kolejka; // bufor
	kolejka.odbiorca = 123;
	odbierz(k_id, &kolejka); // odbiera

	while (1)
	{
		kolejka.odbiorca = kolejka.nadawca;
		cout << "\n [" << kolejka.nadawca << "] klient: " << kolejka.msg;
		sleep(1);
		duze_litery(kolejka.msg);

		kolejka.nadawca = pid;
		wyslij(k_id, &kolejka); // wysylanie

		czysc(kolejka.msg); // czyszczenie bufora
		kolejka.odbiorca = pid;
		odbierz(k_id, &kolejka); // odbieranie
		cout << "\n [" << kolejka.nadawca << "] klient: " << kolejka.msg;
	}
}
