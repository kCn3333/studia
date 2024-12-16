/*---------S-y-s-s-t-e-m-y----O-p-e-r-a-c-y-j-n-e---------|
|                          1.cpp                          |
|                     Procesy potomne                     |
|                                                         |
|--------------------------------------------------------*/

#include <stdio.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <time.h>

using namespace std;

main()
{
	int UID = getuid();	  // identyfikator urzytkownika
	int GID = getgid();	  // identyfikator grupy uzytkownika
	int PID = getpid();	  // identyfikator procesu
	int PPID = getppid(); // identyfikator procesu macierzystego (przodka)
	int PGID = getpgrp(); // identyfikator grupy procesow

	cout << "  +---------------------------------------+" << endl;
	cout << "  | " << "identyfikator urzytkownika      " << UID << "  | " << endl;
	cout << "  | " << "identyfikator grupy uzytkownika " << GID << " | " << endl;
	cout << "  | " << "identyfikator procesu           " << PID << " | " << endl;
	cout << "  | " << "procesu macierzystego           " << PPID << " | " << endl;
	cout << "  | " << "identyfikator grupy procesow    " << PGID << " | " << endl;
	cout << "  +---------------------------------------+" << endl
		 << endl;

	for (int i = 0; i < 3; i++)
	{
		switch (fork())
		{
		case -1:
			perror("fork error");
			exit(1);
		case 0:
			PID = getpid();
			cout << i << "   I'm the child    " << PID << endl;
		// proces potomny
		default:
			PPID = getppid();
			cout << i << "   I'm the parent   " << PPID << endl;
			// proces macierzysty
		}
		sleep(1);
	}
}
