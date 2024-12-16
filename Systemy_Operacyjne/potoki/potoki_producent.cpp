/*
PAWEL KWIECIEN
--------------
- POTOKI -
- PRODUCENT -
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

     cout << "\n\t*** PRODUCENT ***"
          << "\n\t*****************\n";

     if (mkfifo("./fifo", 0777)) // tworzenie fifo
     {
          cout << "\n#tworzenie potoku FIFO nie powiodlo sie...\n";
          exit(EXIT_FAILURE);
     }
     else
          cout << "\n #potok FIFO zostal utworzony\n";

     FILE *fp; // wskaznik plikowy
     if ((fp = fopen("dane.txt", "r")) == 0)
     {
          cout << "\n#otwarcie pliku data.txt nie powiodlo sie...\n";
          exit(EXIT_FAILURE);
     }
     else
          cout << "\n #plik dane.txt otwarty\n";

     if ((filedes = open("./fifo", O_WRONLY, 0777)) == -1) // otwarcie fifo
     {
          cout << "\n#otwarcie potoku FIFO nie powiodlo sie...\n";
          exit(EXIT_FAILURE);
     }
     else
          cout << "\n #potok FIFO zostal otwarty\n\n";

     char bufor;
     char *w_bufor = &bufor;

     cout << "\n   [-----------tekst-przesylany-do-potoku-----------]\n\n";
     do
     {
          if (sizeof(bufor) != fread(&bufor, 1, sizeof(bufor), fp))
               bufor = 0;
          cout << bufor;
          if (write(filedes, w_bufor, sizeof(bufor)) == -1)
               cout << "\n #blad zapisu do potoku FIFO\n";
     } while (!feof(fp));
     cout << "\n   [------------------------------------------------]\n";

     // sleep(3);	// SLEEP

     if (close(filedes) == -1)
     {
          cout << "\n#zamkniecie FIFO nie powiodlo sie...\n";
          exit(EXIT_FAILURE);
     }
     else
          cout << "\n #potok FIFO zastal zamkniety\n";

     if (fclose(fp) == 0)
          ;
     cout << "\n #plik dane.txt zamkniety\n";

     if (unlink("./fifo") == 0)
          cout << "\n #plik ./fifo zostal usuniety\n";

     cout << "\n";
     return 0;
}
