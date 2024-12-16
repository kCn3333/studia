#include "connectsock.cpp"

#define LINELEN 100 // definiujemy maksymalny rozmiar bufora

int main(int argc, char **argv)
{
    int s, i, n1, n2, k;
    char *buf[LINELEN + 1];                            // wskaznik do tablicy char o wielkosci LINELEN+1
    if ((s = connectsock(argv[1], "echo", "tcp")) < 0) // wywolanie funkcji connectsock z pliku connectsock.c
                                                       // z usluga echo dla protokolu tcp
        return 0; // w razie niepowodzenia (funkcja zwraca -1)

    for (i = 2; i < argc; i++)
    {
        n1 = write(s, argv[i], strlen(argv[i])); // funkcja write przepisuje do zmiennej s
                                                 // zawartosc zmiennej argv[i] o takiej samej dlugosci
        while (n1 > 0 && (n2 = read(s, buf, LINELEN)) > 0) // gdy powyzsza funkcja i funkcja czytajaca
                                                           // z deskryptora s do buf zakoncza sie powodzeniem
        {
            buf[n2] = '\0';             // napis zakonczony znakiem pustym
            n1 -= n2;                   // od n1 odejmujemy n2
            for (k = 0; k <= argc; k++) // wypisanie na ekran bufora z
                fputs(buf[k], stdout);  // trescia podana przez uzytkownika
        }
        fputs("\n", stdout); // nowa linia
    }
    if (shutdown(s, SHUT_RDWR) < 0) // zamkniecie gniazda s
        return 0;                   // jezeli polaczenie zakonczy sie bledem (funkja zwroci -1)
    return 1;
}