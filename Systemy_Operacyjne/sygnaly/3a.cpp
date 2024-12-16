/*
PAWEL KWIECIEN
--------------
- SYGNALY -
obsluga sygnalów z kliawiatury

*/

#include <stdio.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

void my_sighandler(int sygnal)
{
  cout << "\n\t__________________________________\n"
       << "\t>>\tOBSLUGA SYGNALU NR " << sygnal << "\t<<\n"
       << "\t----------------------------------\n";
}

main(int argc, char *argv[])
{
  int tryb, sygnal;

  if (argc < 2)
  {
    cout << "\nskladnia " << argv[0] << " [sygnal] [tryb obslugi 0 - domyslny, 1 - ignoruj, 2 - wlasna obsluga]\n";
    exit(EXIT_FAILURE);
  }
  else if (argc == 2)
  {
    tryb = 0;
  }
  else
  {
    sygnal = atoi(argv[1]);
    tryb = atoi(argv[2]);
  }

  cout << "\n\t *** PROCES NR " << getpid() << " ***\n";

  switch (tryb)
  {
  case 1:
  {
    cout << "\n\t sygnal zostanie zignorowany\n";
    if (signal(atoi(argv[1]), SIG_IGN) == SIG_ERR)
    {
      perror("\n #blad funkcji signal\n");
      exit(EXIT_FAILURE);
    }
    break;
  }
  case 2:
  {
    cout << "\n\t wlasna obsluga sygnalu\n";
    if (signal(atoi(argv[1]), my_sighandler) == SIG_ERR)
    {
      perror("\n #blad funkcji signal\n");
      exit(EXIT_FAILURE);
    }
    break;
  }
  default:
  {
    cout << "\n\t domyslna obsluga sygnalu\n";
    if (signal(atoi(argv[2]), SIG_DFL) == SIG_ERR)
    {
      perror("\n #blad funkcji signal\n");
      exit(EXIT_FAILURE);
    }
    break;
  }
  }

  cout << "\n oczekiwanie na sygnal...\n";
  pause();

  return 0;
}
