/*
Pawel Kwiecien
program wymaga zlinkowania biblioteki conio2 '-lconio'
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>

unsigned int euklid(unsigned int a, unsigned int b) // NWD
{
     unsigned int t;
     while (t = a % b)
     {
          a = b;
          b = t;
     }
     return b;
}

void czekaj(int milisecs)
{
     unsigned long int t = GetTickCount() + milisecs;
     while (GetTickCount() < t)
     {
     }
}

double sec(double x) { return 1.0 / cos(x); } // Deklaracje funkcji trygonometrycznych niezawartych w cmath
double csc(double x) { return 1.0 / sin(x); }
double cot(double x) { return 1.0 / tan(x); }

int silnia(int x)
{
     int g;
     g = 0;
     int w;
     w = 1;
     while (g < x)
     {
          g++;
          w = w * g;
     }
     return w;
}

int main(int argc, char *argv[])
{
     int ster = 'n';
     int opcja = 4;
     int opcja3 = 0;
     int help[10];
     int pomoc[11];
     float unit[9];
     int kolor = BLACK;
     int kolor2 = BLUE;
     int kolor3 = GREEN;

     textcolor(kolor);
     textbackground(WHITE);
     clrscr(); // odswierzenie ekranu i czyszczenie bufora
     textcolor(kolor);
     printf("\n\n <---------------------------Pawel-Kwiecien-(c)-2007--------------------------->\n");
     printf(" |X| |X|   |X|   |X|    |X| |X| |X|  |X| |X|      |X|  |XXXXX|  |XXXX|  |XXXX|\n");
     textcolor(kolor);
     czekaj(300);
     printf(" |X||X|  |X| |X| |X|    |X||X|  |X|  |X| |X|    |X| |X|  |X|   |X|  |X| |X| |X|\n");
     textcolor(kolor);
     czekaj(300);
     printf(" |XXX|   |XXXXX| |X|    |XXX|   |X|  |X| |X|    |XXXXX|  |X|   |X|  |X| |XXXX|\n");
     textcolor(kolor);
     czekaj(300);
     printf(" |X||X|  |X| |X| |X|    |X||X|  |X|  |X| |X|    |X| |X|  |X|   |X|  |X| |X| |X|\n");
     textcolor(kolor);
     czekaj(300);
     printf(" |X| |X| |X| |X| |XXXX| |X| |X|  |XXXX|  |XXXX| |X| |X|  |X|    |XXXX|  |X|  |X|\n");
     textcolor(kolor);
     czekaj(300);
     printf(" <----------------------------------------------------------------------------->\n\n\n");

     while (ster == 'n' || ster == 'N')
     {
          textcolor(GREEN);
          textbackground(WHITE);
          printf("\n\tPodstawowe dzialania       -> 1\n");
          textcolor(BLUE);
          textbackground(WHITE);
          printf("\tFunkcje trygonometryczne   -> 2\n");
          textcolor(GREEN);
          textbackground(WHITE);
          printf("\tObliczenia dodatkowe       -> 3\n");
          textcolor(GREEN);
          textbackground(WHITE);
          printf("\t-------------------------------\n");
          textcolor(BLUE);
          textbackground(WHITE);
          printf("\n\tPomoc  -> 4\n");
          textcolor(GREEN);
          textbackground(WHITE);
          printf("\tInfo   -> 5\n");
          scanf("%d", &opcja);

          if (opcja == 1)
          {
               clrscr();
               int opcja2;
               float liczba[3];
               int liczba2;
               textcolor(GREEN);
               textbackground(WHITE);
               printf("\n\tDodawanie         -> 1\n");
               textcolor(BLUE);
               textbackground(WHITE);
               printf("\tOdejmowanie       -> 2\n");
               textcolor(GREEN);
               textbackground(WHITE);
               printf("\tMnozenie          -> 3\n");
               textcolor(BLUE);
               textbackground(WHITE);
               printf("\tDzielenie         -> 4\n");
               textcolor(GREEN);
               textbackground(WHITE);
               printf("\tPotegowanie       -> 5\n");
               textcolor(BLUE);
               textbackground(WHITE);
               printf("\tPierwiastkowanie  -> 6\n");
               printf("\t----------------------\n");
               scanf("%d", &opcja2);
               clrscr();

               if (opcja2 == 1)
               {
                    printf("\n");
                    textcolor(kolor);
                    printf("\twybrales dodawanie (A+B), A=");
                    scanf("%f", &liczba[0]);
                    printf("\t                          B=");
                    scanf("%f", &liczba[1]);
                    liczba[3] = liczba[0] + liczba[1];
                    printf("\tsuma A+B = %f", liczba[3]);
                    goto exit2;
               }
               if (opcja2 == 2)
               {
                    printf("\n");
                    textcolor(kolor);
                    printf("\twybrales odejmowanie (A-B), A=");
                    scanf("%f", &liczba[0]);
                    printf("\t                            B=");
                    scanf("%f", &liczba[1]);
                    liczba[3] = liczba[0] - liczba[1];
                    printf("\troznica A-B = %f", liczba[3]);
                    goto exit2;
               }
               if (opcja2 == 3)
               {
                    printf("\n");
                    textcolor(kolor);
                    printf("\twybrales mnozenie (A*B), A=");
                    scanf("%f", &liczba[0]);
                    printf("\t                         B=");
                    scanf("%f", &liczba[1]);
                    liczba[3] = liczba[0] * liczba[1];
                    printf("\tiloczyn A*B = %f", liczba[3]);
                    goto exit2;
               }
               if (opcja2 == 4)
               {
                    printf("\n");
                    textcolor(kolor);
                    printf("\twybrales dzielenie (A/B), A=");
                    scanf("%f", &liczba[0]);
                    printf("\t                          B=");
                    scanf("%f", &liczba[1]);
                    liczba[3] = liczba[0] / liczba[1];
                    printf("\tiloraz A/B = %f", liczba[3]);
                    goto exit2;
               }
               if (opcja2 == 5)
               {
                    printf("\n");
                    textcolor(kolor);
                    printf("\twybrales potegowanie (A^B), A=");
                    scanf("%f", &liczba[1]);
                    printf("\t                            B=");
                    scanf("%f", &liczba[0]);
                    liczba[3] = pow(liczba[1], liczba[0]);
                    printf("\tpotega A^B = %f", liczba[3]);
                    goto exit2;
               }
               if (opcja2 == 6)
               {
                    printf("\n");
                    textcolor(kolor);
                    printf("\twybrales pierwiastkowanie, A=");
                    scanf("%f", &liczba[2]);
                    printf("\t                   wykladnik=");
                    scanf("%f", &liczba[1]);
                    liczba[3] = pow(liczba[2], (1.0 / liczba[0]));
                    printf("\tpierwiastek z A stopnia B = %f", liczba[3]);
                    goto exit;
               }
          exit2:

               printf("\n");
               printf("\n aby kontynuowac nacisnij ENTER");
               getchar();
               while (opcja3 = !0)
               {
                    clrscr();
                    textcolor(kolor);
                    printf("\n\n\n\t\t\twynik wynosi %f", liczba[3]);
                    textcolor(GREEN);
                    textbackground(WHITE);
                    printf("\n\n\n");
                    printf("\tdodaj do wyniku       -> 1\n");
                    textcolor(BLUE);
                    textbackground(WHITE);
                    printf("\todejmij od wyniku     -> 2\n");
                    textcolor(GREEN);
                    textbackground(WHITE);
                    printf("\tpomnoz wynik          -> 3\n");
                    textcolor(BLUE);
                    textbackground(WHITE);
                    printf("\tpodziel wynik         -> 4\n");
                    textcolor(GREEN);
                    textbackground(WHITE);
                    printf("\tspoteguj wynik        -> 5\n");
                    textcolor(BLUE);
                    textbackground(WHITE);
                    printf("\tspierwiastkuj wynik   -> 6\n");
                    printf("\t----------------------\n");
                    textcolor(RED);
                    textbackground(WHITE);
                    printf("\tzakoncz  -> 0\n");
                    scanf("%d", &opcja3);

                    switch (opcja3)
                    {
                    case 0:
                         goto exit;
                         break;
                    case 1:
                         textcolor(kolor);
                         printf("\n\n\tpodaj liczbe ktora dodac ");
                         scanf("%f", &liczba[2]);
                         liczba[3] = liczba[3] + liczba[2];
                         printf("\n %f", liczba[3]);
                         break;
                    case 2:
                         textcolor(kolor);
                         printf("\n\n\tpodaj liczbe ktora odjac ");
                         scanf("%f", &liczba[2]);
                         liczba[3] = liczba[3] - liczba[2];
                         printf("\n %f", liczba[3]);
                         break;
                    case 3:
                         textcolor(kolor);
                         printf("\n\n\tpodaj drugi czynnik ");
                         scanf("%f", &liczba[2]);
                         liczba[3] = liczba[3] * liczba[2];
                         printf("\n %f", liczba[3]);
                         break;
                    case 4:
                         textcolor(kolor);
                         printf("\n\n\tpodaj dzielnik ");
                         scanf("%f", &liczba[2]);
                         liczba[3] = liczba[3] / liczba[2];
                         printf("\n %f", liczba[3]);
                         break;
                    case 5:
                         textcolor(kolor);
                         printf("\n\n\tpodaj wykladnik potegi ");
                         scanf("%f", &liczba[2]);
                         liczba[3] = pow(liczba[3], liczba[2]);
                         printf("\n %f", liczba[3]);
                         break;
                    case 6:
                         textcolor(kolor);
                         printf("\n\n\tpodaj wykladnik pierwiastka ");
                         scanf("%f", &liczba[2]);
                         liczba[3] = pow(liczba[3], 1.0 / liczba[2]);
                         printf("\n %f", liczba[3]);
                         system("pause");
                         break;
                    default:
                         goto exit;
                    }
               }
          }
          if (opcja == 2)
          {
               clrscr();
               textcolor(GREEN);
               printf("\n\twybrales funkcje trygonometryczne kata plaskiego.\n\n\tPodaj jednostke: \n\t radiany -> 1\n\t stopnie -> 2\n\n");
               scanf("%d", &help[0]);
               clrscr();
               if (help[0] == 2)
               {
                    printf("\tWybrales stopnie. Wybierz funkcje\n\n");
                    unit[0] = 180 / M_PI;
               }
               if (help[0] == 1)
               {
                    printf("\tWybrales Radiany. Wybierz funkcje\n\n");
                    unit[0] = 1.0;
               }
               textcolor(RED);
               printf("\tsinus    -> 1\n");
               textcolor(BLUE);
               printf("\tcosinus  -> 2\n");
               textcolor(RED);
               printf("\ttanges   -> 3\n");
               textcolor(BLUE);
               printf("\tcotanges -> 4\n");
               textcolor(RED);
               printf("\tsecant   -> 5\n");
               textcolor(BLUE);
               printf("\tcosecant -> 6\n");
               scanf("%d", &pomoc[1]);
               switch (pomoc[1])
               {
               case 1:
                    textcolor(kolor);
                    printf("\n\n\tWybrales sinus. Podaj miare kata.\n");
                    scanf("%f", &unit[1]);
                    unit[2] = sin(unit[1]) * unit[0];
                    printf("\t\tsinus z tego kata wynosi %f\n\n", unit[2]);
                    system("pause");
                    goto exit;
                    break;
               case 2:
                    textcolor(kolor);
                    printf("\n\n\tWybrales cosinus. Podaj miare kata.\n");
                    scanf("%f", &unit[1]);
                    unit[2] = cos(unit[1]) * unit[0];
                    printf("\t\tcosinus z tego kata wynosi %f\n\n", unit[2]);
                    system("pause");
                    goto exit;
                    break;
               case 3:
                    textcolor(kolor);
                    printf("\n\n\tWybrales tanges. Podaj miare kata.\n");
                    scanf("%f", &unit[1]);
                    unit[2] = tan(unit[1]) * unit[0];
                    printf("\t\ttanges z tego kata wynosi %f\n\n", unit[2]);
                    system("pause");
                    goto exit;
                    break;
               case 4:
                    textcolor(kolor);
                    printf("\n\n\tWybrales cotanges. Podaj miare kata.\n");
                    scanf("%f", &unit[1]);
                    unit[2] = cot(unit[1]) * unit[0];
                    printf("\t\tcotanges z tego kata wynosi %f\n\n", unit[2]);
                    system("pause");
                    goto exit;
                    break;
               case 5:
                    textcolor(kolor);
                    printf("\n\n\tWybrales sekant. Podaj miare kata.\n");
                    scanf("%f", &unit[1]);
                    unit[2] = sec(unit[1]) * unit[0];
                    printf("\t\tsecant z tego kata wynosi %f\n\n", unit[2]);
                    system("pause");
                    goto exit;
                    break;
               case 6:
                    textcolor(kolor);
                    printf("\n\n\tWybrales cosekant. Podaj miare kata.\n");
                    scanf("%f", &unit[1]);
                    unit[2] = csc(unit[1]) * unit[0];
                    printf("\t\tcosecant z tego kata wynosi %f\n\n", unit[2]);
                    system("pause");
                    goto exit;
                    break;
               }
          }
          if (opcja == 3)
          {
               clrscr();
               textcolor(kolor);
               printf("\tWybrales inne obliczenia. Wybierz funkcje:\n\n");
               textcolor(GREEN);
               printf("\n\tsilnia                             -> 1\n");
               textcolor(BLUE);
               textbackground(WHITE);
               printf("\tnajwiekszy wspolny dzielnik        -> 2\n");
               textcolor(GREEN);
               textbackground(WHITE);
               printf("\tnajmniejsza wspolna wielokrotnosc  -> 3\n");
               printf("\t---------------------------------------\n");
               scanf("%d", &pomoc[11]);
               clrscr();

               if (pomoc[11] == 1)
               {
                    textcolor(kolor);
                    printf("\n\tPodaj liczbe z ktorej ma byc wyciagnieta silnia (max 16)\n");
                    scanf("%d", &pomoc[9]);
                    pomoc[5] = silnia(pomoc[9]);
                    printf("\n\t %d! wynosi %d\n\n", pomoc[9], pomoc[5]);
                    system("pause");
                    getchar();
                    goto exit;
               }
               if (pomoc[11] == 2)
               {
                    int a, b;
                    textcolor(kolor);
                    printf("\n\tNWD liczb A i B, A=");
                    scanf("%d", &a);
                    printf("\t                 B=");
                    scanf("%d", &b);
                    int c = euklid(a, b);
                    printf("\n\tNWD wynosi %d\n\n", c);
                    system("pause");
                    getchar();
                    goto exit;
               }
               if (pomoc[11] == 3)
               {
                    int a, b;
                    textcolor(kolor);
                    printf("\n\tNWW liczb A i B, A=");
                    scanf("%d", &a);
                    printf("\t                 B=");
                    scanf("%d", &b);
                    int c = euklid(a, b);
                    printf("\n\tNWW wynosi %d\n\n", (a * b) / c);
                    system("pause");
                    getchar();
                    goto exit;
               }
          }
          if (opcja == 5)
          {
               clrscr();
               czekaj(300);
               textcolor(GREEN);
               printf("\n\t................................................................");
               czekaj(300);
               printf("\n\t................................................................");
               czekaj(300);
               printf("\n\t..................   _   _    |XXXX|  _     _   ................");
               czekaj(300);
               printf("\n\t..................  |X| |X|  |X|     |XX|  |X|  ................");
               czekaj(300);
               printf("\n\t..................  |X||X|  |X|      |X|X| |X|  ................");
               czekaj(300);
               printf("\n\t..................  |XXX|   |X|      |X||X||X|  ................");
               czekaj(300);
               printf("\n\t..................  |X||X|  |X|____  |X| |X|X|  ................");
               czekaj(300);
               printf("\n\t..................  |X| |X|  |XXXXX| |X|   |X|  ................");
               czekaj(300);
               printf("\n\t................................................................");
               czekaj(300);
               printf("\n\t................................................................");
               czekaj(300);
               printf("\n\t................................................................");
               czekaj(300);
               printf("\n\t................................................................");
               czekaj(300);
               printf("\n\t.....................[ kalkulator v1.1 beta ]...................");
               czekaj(300);
               printf("\n\t.............[ skompilowano w Bloodshet Dev-C++ 4.992 ].........");
               czekaj(300);
               printf("\n\t....................[ CONIO Borland DevPacks ]..................");
               czekaj(300);
               printf("\n\t................................................................");
               czekaj(300);
               printf("\n\t..............................-2o10-............................");
               czekaj(300);
               printf("\n\t................................................................\n\n");
               system("pause");
               getchar();
               goto exit;
          }
          if (opcja == 4)
          {
               clrscr();
               textcolor(RED);
               printf("\n\n\tKalkulator v1.1 beta\n\n\tObsluga\n\n");

               system("pause");
               getchar();
               goto exit;
          }
          if (opcja != 1 && opcja != 2 && opcja != 3 && opcja != 4 && opcja != 5 && opcja != 6) // kolo ratunkowe, jesli userowi strzeli do pustego lba wpisac inna wartosc
          {
               clrscr();
               textcolor(RED);
               printf("\n\n\tBledna wartosc\n\n");
               system("pause");
               getchar();
               goto exit;
          }
          if (opcja == 6)
          {
               clrscr();
               textcolor(GREEN);
               printf("\t________________________________________________\n");
               printf("\t________________________________________________\n");
               printf("\t                     #                          \n");
               printf("\t                    ###                         \n");
               printf("\t  #                 ###                #        \n");
               printf("\t   ##              #####             ##         \n");
               printf("\t    ###            #####           ###          \n");
               printf("\t     #####         #####        #####           \n");
               printf("\t      #######      #####     #######            \n");
               printf("\t        #######    #####   #######              \n");
               printf("\t           #####    ###   #####                 \n");
               printf("\t  #######      ###  ###  ###      #######       \n");
               printf("\t      ########    ## # ##   ########            \n");
               printf("\t          ######### ### #########               \n");
               printf("\t                 ### # ###                      \n");
               printf("\t             #####   #  #####                   \n");
               printf("\t                     #                          \n");
               printf("\t________________________________________________\n");
               printf("\t_____________[sm00ke_some_weed]_________________\n");
               printf("\t________________________________________________\n\n\n");

               system("pause");
               getchar();
               goto exit;
          }

     exit:
          clrscr();
          textcolor(RED);
          printf("\n\nCzy chcesz wylaczyc program? (t/n)");
          scanf("%s", &ster);
          clrscr();
     }

     system("PAUSE");
     return 0;
}
