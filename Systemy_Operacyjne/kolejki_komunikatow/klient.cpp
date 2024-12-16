#include "msg.h"

using namespace std;

void czysc(char *w)
{
    for (int i = 0; i < m_size; i++)
    {
        w[i] = '\0';
    }
}

int main()
{
    int k_id = 4751370; // kolejkaID

    cout << "\n --------------------------------------";
    cout << "\n KLIENT: Podlaczony [kolejkaID " << k_id << "]\n";
    cout << " --------------------------------------\n";

    class wiadomosc kolejka; // bufor
    pid_t pid = getpid();    // nr procesu

    cout << "\n [" << pid << "] klient: ";
    cin.getline(kolejka.msg, m_size, '\n');

    kolejka.odbiorca = 123;
    kolejka.nadawca = pid;
    wyslij(k_id, &kolejka); // wysylanie

    while (1)
    {
        czysc(kolejka.msg); // czyszczenie bufora

        kolejka.odbiorca = pid;
        odbierz(k_id, &kolejka); // odbieranie
        cout << " [*****] serwer: " << kolejka.msg;
        czysc(kolejka.msg); // czysczenie bufora

        kolejka.odbiorca = kolejka.nadawca;
        kolejka.nadawca = pid;
        cout << "\n [" << pid << "] klient: ";
        cin.getline(kolejka.msg, m_size, '\n');
        wyslij(k_id, &kolejka); // wysylanie
    }
}
