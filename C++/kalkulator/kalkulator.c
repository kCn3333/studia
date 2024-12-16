/*
Pawel Kwiecien

plik nalezy kompilowac z parametrem -lm (linkowanie funkcji matematycznych)
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

unsigned int euklid(unsigned int a, unsigned int b) /*NWD*/
{
     unsigned int t;
     while (t = a % b)
     {
          a = b;
          b = t;
     }
     return b;
}

double sec(double x) { return 1.0 / cos(x); } /*deklaracje funkcji trygonometrycznych nie zawartych w math.h*/
double csc(double x) { return 1.0 / sin(x); }
double cot(double x) { return 1.0 / tan(x); }

int silnia(int x) /*silnia*/
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

int main(int argc, char *argv[]) /*   poczatek main()  */
{
     int ster = 'n';
     int opcja = 4;
     int opcja3 = 0;
     int help[10];
     int pomoc[11];
     float unit[9];

     printf("\n\n <-------------------------------------kCn------------------------------------->\n");
     printf(" |X| |X|   |X|   |X|    |X| |X| |X|  |X| |X|      |X|  |XXXXX|  |XXXX|  |XXXX|\n");
     printf(" |X||X|  |X| |X| |X|    |X||X|  |X|  |X| |X|    |X| |X|  |X|   |X|  |X| |X| |X|\n");
     printf(" |XXX|   |XXXXX| |X|    |XXX|   |X|  |X| |X|    |XXXXX|  |X|   |X|  |X| |XXXX|\n");
     printf(" |X||X|  |X| |X| |X|    |X||X|  |X|  |X| |X|    |X| |X|  |X|   |X|  |X| |X| |X|\n");
     printf(" |X| |X| |X| |X| |XXXX| |X| |X|  |XXXX|  |XXXX| |X| |X|  |X|    |XXXX|  |X|  |X|\n");
     printf(" <----------------------------------------------------------------------------->\n\n\n");

     while (ster == 'n' || ster == 'N')
     { /*   MENU 1   */
          printf("\n\tPodstawowe dzialania       -> 1\n");
          printf("\tFunkcje trygonometryczne   -> 2\n");
          printf("\tObliczenia dodatkowe       -> 3\n");
          printf("\t-------------------------------\n");
          printf("\n\tPomoc  -> 4\n");
          printf("\tInfo   -> 5\n");
          scanf("%d", &opcja);

          if (opcja == 1)
          {
               int opcja2;
               float liczba[3];
               int liczba2;
               printf("\n <----------------------------------------------------------------------------->\n");
               printf("\n\tDodawanie         -> 1\n"); /*   MENU 2   */
               printf("\tOdejmowanie       -> 2\n");
               printf("\tMnozenie          -> 3\n");
               printf("\tDzielenie         -> 4\n");
               printf("\tPotegowanie       -> 5\n");
               printf("\tPierwiastkowanie  -> 6\n");
               printf("\t----------------------\n");
               scanf("%d", &opcja2);

               if (opcja2 == 1)
               {
                    printf("\n"); /*   DODAWANIE   */
                    printf("\twybrales dodawanie (A+B), A=");
                    scanf("%f", &liczba[0]);
                    printf("\t                          B=");
                    scanf("%f", &liczba[1]);
                    liczba[3] = liczba[0] + liczba[1];
                    printf("\tsuma A+B = %f", liczba[3]);
                    goto exit2; /* zastosowalem goto bo sie psulo =]*/
               }
               if (opcja2 == 2)
               {
                    printf("\n"); /*   ODEJMOWANIE   */
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
                    printf("\n"); /*   MNOZENIE  */
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
                    printf("\n"); /*   DZIELENIE   */
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
                    printf("\n"); /*   POTEGA   */
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
                    printf("\n"); /*   PIERWIASTEK   */
                    printf("\twybrales pierwiastkowanie, A=");
                    scanf("%f", &liczba[2]);
                    printf("\t                   wykladnik=");
                    scanf("%f", &liczba[1]);
                    liczba[3] = pow(liczba[2], (1.0 / liczba[0]));
                    printf("\tpierwiastek z A stopnia B = %f", liczba[3]);
                    goto exit;
               }
          exit2:
               printf("\n"); /*   WYJSCIE Z MENU 2   */
               printf("\n aby kontynuowac nacisnij ENTER");
               getchar();
               while (opcja3 = !0)
               {
                    printf("\n\n\n\t\t\twynik wynosi %f", liczba[3]);
                    printf("\n\n\n"); /*   MENU 3   */
                    printf("\tdodaj do wyniku       -> 1\n");
                    printf("\todejmij od wyniku     -> 2\n");
                    printf("\tpomnoz wynik          -> 3\n");
                    printf("\tpodziel wynik         -> 4\n");
                    printf("\tspoteguj wynik        -> 5\n");
                    printf("\tspierwiastkuj wynik   -> 6\n");
                    printf("\t----------------------\n");
                    printf("\tzakoncz  -> 0\n");
                    scanf("%d", &opcja3);

                    switch (opcja3)
                    {
                    case 0:
                         goto exit;
                         break;
                    case 1:
                         printf("\n\n\tpodaj liczbe ktora dodac ");
                         scanf("%f", &liczba[2]);
                         liczba[3] = liczba[3] + liczba[2];
                         printf("\n %f", liczba[3]);
                         break;
                    case 2:
                         printf("\n\n\tpodaj liczbe ktora odjac ");
                         scanf("%f", &liczba[2]);
                         liczba[3] = liczba[3] - liczba[2];
                         printf("\n %f", liczba[3]);
                         break;
                    case 3:
                         printf("\n\n\tpodaj drugi czynnik ");
                         scanf("%f", &liczba[2]);
                         liczba[3] = liczba[3] * liczba[2];
                         printf("\n %f", liczba[3]);
                         break;
                    case 4:
                         printf("\n\n\tpodaj dzielnik ");
                         scanf("%f", &liczba[2]);
                         liczba[3] = liczba[3] / liczba[2];
                         printf("\n %f", liczba[3]);
                         break;
                    case 5:
                         printf("\n\n\tpodaj wykladnik potegi ");
                         scanf("%f", &liczba[2]);
                         liczba[3] = pow(liczba[3], liczba[2]);
                         printf("\n %f", liczba[3]);
                         break;
                    case 6:
                         printf("\n\n\tpodaj wykladnik pierwiastka ");
                         scanf("%f", &liczba[2]);
                         liczba[3] = pow(liczba[3], 1.0 / liczba[2]);
                         printf("\n %f", liczba[3]);
                         break;
                    default:
                         goto exit;
                    }
               }
          }
          if (opcja == 2)
          {
               printf("\n\twybrales funkcje trygonometryczne kata plaskiego.\n\n\tPodaj jednostke: \n\t radiany -> 1\n\t stopnie -> 2\n\n");
               scanf("%d", &help[0]);
               if (help[0] == 2)
               {
                    printf("\tWybrales stopnie. Wybierz funkcje\n\n");
                    unit[0] = 180 / M_PI;
               }
               if (help[0] == 1)
               {
                    printf("\tWybrales Radiany. Wybierz funkcje\n\n");
                    unit[0] = 1.0;
               } /*   MENU 4   */
               printf("\tsinus    -> 1\n");
               printf("\tcosinus  -> 2\n");
               printf("\ttanges   -> 3\n");
               printf("\tcotanges -> 4\n");
               printf("\tsecant   -> 5\n");
               printf("\tcosecant -> 6\n");
               scanf("%d", &pomoc[1]);
               switch (pomoc[1])
               {
               case 1:
                    printf("\n\n\tWybrales sinus. Podaj miare kata.\n");
                    scanf("%f", &unit[1]); /*   SINUS  */
                    unit[2] = sin(unit[1]) * unit[0];
                    printf("\t\tsinus z tego kata wynosi %f\n\n", unit[2]);
                    goto exit;
                    break;
               case 2:
                    printf("\n\n\tWybrales cosinus. Podaj miare kata.\n");
                    scanf("%f", &unit[1]); /*   COSINUS   */
                    unit[2] = cos(unit[1]) * unit[0];
                    printf("\t\tcosinus z tego kata wynosi %f\n\n", unit[2]);
                    goto exit;
                    break;
               case 3:
                    printf("\n\n\tWybrales tanges. Podaj miare kata.\n");
                    scanf("%f", &unit[1]); /*   TANGENS   */
                    unit[2] = tan(unit[1]) * unit[0];
                    printf("\t\ttanges z tego kata wynosi %f\n\n", unit[2]);
                    goto exit;
                    break;
               case 4:
                    printf("\n\n\tWybrales cotanges. Podaj miare kata.\n");
                    scanf("%f", &unit[1]); /*   COTANGENS   */
                    unit[2] = cot(unit[1]) * unit[0];
                    printf("\t\tcotanges z tego kata wynosi %f\n\n", unit[2]);
                    goto exit;
                    break;
               case 5:
                    printf("\n\n\tWybrales sekant. Podaj miare kata.\n");
                    scanf("%f", &unit[1]); /*   SECANT   */
                    unit[2] = sec(unit[1]) * unit[0];
                    printf("\t\tsecant z tego kata wynosi %f\n\n", unit[2]);
                    goto exit;
                    break;
               case 6:
                    printf("\n\n\tWybrales cosekant. Podaj miare kata.\n");
                    scanf("%f", &unit[1]); /*   COSECANT   */
                    unit[2] = csc(unit[1]) * unit[0];
                    printf("\t\tcosecant z tego kata wynosi %f\n\n", unit[2]);
                    goto exit;
                    break;
               }
          }
          if (opcja == 3)
          { /*   MENU 5   */
               printf("\tWybrales inne obliczenia. Wybierz funkcje:\n\n");
               printf("\n\tsilnia                             -> 1\n");
               printf("\tnajwiekszy wspolny dzielnik        -> 2\n");
               printf("\tnajmniejsza wspolna wielokrotnosc  -> 3\n");
               printf("\t---------------------------------------\n");
               scanf("%d", &pomoc[11]);

               if (pomoc[11] == 1)
               {
                    printf("\n\tPodaj liczbe z ktorej ma byc wyciagnieta silnia (max 16)\n");
                    scanf("%d", &pomoc[9]); /*   SILNIA   */
                    pomoc[5] = silnia(pomoc[9]);
                    printf("\n\t %d! wynosi %d\n\n", pomoc[9], pomoc[5]);
                    goto exit;
               }
               if (pomoc[11] == 2)
               {
                    int a, b; /*   najwiekszy wspolny dzielnik   */
                    printf("\n\tNWD liczb A i B, A=");
                    scanf("%d", &a);
                    printf("\t                 B=");
                    scanf("%d", &b);
                    int c = euklid(a, b);
                    printf("\n\tNWD wynosi %d\n\n", c);
                    goto exit;
               }
               if (pomoc[11] == 3)
               {
                    int a, b;
                    printf("\n\tNWW liczb A i B, A=");
                    scanf("%d", &a); /*   najmniejsza wspolna wielokrotnosc  */
                    printf("\t                 B=");
                    scanf("%d", &b);
                    int c = euklid(a, b);
                    printf("\n\tNWW wynosi %d\n\n", (a * b) / c);
                    goto exit;
               }
          }
          if (opcja == 5)
          {
               printf("\n\t................................................................");
               printf("\n\t................................................................");
               printf("\n\t..................   _   _    |XXXX|  _     _   ................");
               printf("\n\t..................  |X| |X|  |X|     |XX|  |X|  ................");
               printf("\n\t..................  |X||X|  |X|      |X|X| |X|  ................");
               printf("\n\t..................  |XXX|   |X|      |X||X||X|  ................");
               printf("\n\t..................  |X||X|  |X|____  |X| |X|X|  ................");
               printf("\n\t..................  |X| |X|  |XXXXX| |X|   |X|  ................");
               printf("\n\t................................................................");
               printf("\n\t................................................................");
               printf("\n\t................................................................");
               printf("\n\t................................................................");
               printf("\n\t.....................[ kalkulator v1.1 beta ]...................");
               printf("\n\t.............[ skompilowano w gcc 4.1.0 (SUSE Linux) ]..........");
               printf("\n\t................................................................");
               printf("\n\t..............................-2oo7-............................");
               printf("\n\t................................................................\n\n");
               goto exit;
          }
          if (opcja == 4)
          {
               printf("\n <----------------------------------------------------------------------------->\n");
               printf("\n\n\t>>> Kalkulator v1.1 beta <<<\n\n\n\t[ INFO ]\n");
               printf("\n\tW funkcjach trygonometrycznych podczas obliczania w stopniach,\n\tmoga wystepowac bledy natury technicznej, dlatego zalecane sa radiany.\n\n");
               printf("\n\tFunkcja silnia dziala dla liczb naturalnych <17,\n\tdla innych wynik wyniesie 0 \n\n");
               printf("\n <----------------------------------------------------------------------------->\n");
               goto exit;
          }
          if (opcja != 1 && opcja != 2 && opcja != 3 && opcja != 4 && opcja != 5) /*   ERROR   */
          {
               printf("\n\n\tBledna wartosc\n\n");
               goto exit;
          }
     exit: /*   GLOWNE WYJSCIE   */
          printf("\n\nCzy chcesz wylaczyc program? (t/n)");
          scanf("%s", &ster);
     }
     return 0;
}
