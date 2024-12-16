/*
PAWEL KWIECIEN
--------------
- POTOKI -
- KONSUMENT -
*/

#include <stdio.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>

using namespace std;

main()
{

     int filedes = 0; // deskryptor

     cout << "\n\t*** KONSUMENT ***"
          << "\n\t*****************\n";

     FILE *fp; // wskaznik plikowy
     if ((fp = fopen("dane2.txt", "w")) == 0)
     {
          cout << "\n#otwarcie pliku data2.txt nie powiodlo sie...\n";
          exit(EXIT_FAILURE);
     }
     else
          cout << "\n #plik dane2.txt gotowy do zapisu\n";

     if ((filedes = open("./fifo", O_RDONLY, 0777)) == -1) // otwarcie fifo
     {
          cout << "\n#otwarcie potoku FIFO nie powiodlo sie...\n";
          exit(EXIT_FAILURE);
     }
     else
          cout << "\n #potok FIFO zostal otwarty\n\n";

     char bufor = 0;
     char *w_bufor = &bufor;

     // sleep(2);	// SLEEP

     cout << "\n   [-----------tekst-przesylany-z-potoku-----------]\n\n";
     // sleep(2);
     while (read(filedes, w_bufor, sizeof(bufor)))
     {
          cout << w_bufor;
          fwrite(w_bufor, sizeof(bufor), 1, fp);
     }
     cout << "\n   [-----------------------------------------------]\n\n";

     if (fclose(fp) == 0)
          cout << "\n #plik dane2.txt zamkniety\n";
     else
          cout << "\n#blad zamkniecia pliku dane2.txt\n";
     cout << "\n";
     return 0;
}
