/*
PAWEL KWIECIEN
--------------
- WYSYLANIE I OBSLUGA SYGNALOW -
obsluga sygnalów z procesu macierzystego

*/

#include <stdio.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

main(int argc, char *argv[])
{
	pid_t pid;

	cout << "\n\t*** PROCES NR " << getpid() << " ***\n";
	cout << "\n\ttworzenie procesu potomnego... \n";

	pid = fork();

	switch (pid)
	{
	case -1: // BLAD
	{
		perror("\n#blad funkcji fork");
		exit(EXIT_FAILURE);
		break;
	}
	case 0: // proces potomny, uruchom obsluge sygnalow
	{
		execl("./3.exe", "3.exe", "7", "2", NULL);
		perror("\n#blad funkcji execl");
		exit(EXIT_FAILURE);
		break;
	}
	default: // proces glowny, sygnal do procesu potomnego
	{
		sleep(1);
		cout << "\n\twysylanie sygnalu do procesu nr " << pid << "...";
		if (kill(pid, 7) == -1)
		{
			perror("\n#blad funkcji kill");
			exit(EXIT_FAILURE);
		}
		sleep(1);
		break;
	}
	}
	cout << "\n\n[KONIEC]\n";
	return 0;
}
