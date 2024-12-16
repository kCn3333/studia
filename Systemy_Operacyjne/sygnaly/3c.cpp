/*
PAWEL KWIECIEN
--------------
- WYSYLANIE I OBSLUGA SYGNALOW -
obsluga sygnalów wysylanych do grupy
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
	pid_t pid, pid_g;

	cout << "\n\t*** PROCES NR " << getpid() << " ***\n";
	cout << "\n\ttworzenie grupy procesow potomnych... \n";

	for (int i = 0; i < 5; i++)
	{
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
			sleep(2);
			break;
		}
		}
	}

	if (signal(7, SIG_IGN) == SIG_ERR) // proces glowny ma ignorowac sygnal wysylany do grupy
	{
		perror("\n#blad funkcji signal\n");
		exit(EXIT_FAILURE);
	}

	pid_g = getpgrp(); // identyfikator grupy utworzonych procesow

	cout << "\n\twysylanie sygnalu do grupy utworzonych procesow... \n";
	if (kill(-pid_g, 7) == -1) // wysylanie sygnalu do grupy
	{
		perror("\n#blad funkcji kill\n");
		exit(EXIT_FAILURE);
	}

	wait(0);

	cout << "\n\n[KONIEC]\n";
	return 0;
}
