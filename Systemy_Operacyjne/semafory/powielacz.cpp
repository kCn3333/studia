#include "semafor.h"

int main(int argc, char **argv)
{
	int s_id, ile;
	key_t key;

	if (argc != 3)
	{
		cout << "\n skladnia " << argv[0] << " [ile_procesow] [proces.exe]\n";
		exit(EXIT_FAILURE);
	}
	else
	{
		ile = atoi(argv[1]);
	}

	key = ftok(".", 'A');

	s_id = tworz(key, 1);
	inicjuj(s_id, 1, 0);

	info(s_id);

	for (int i = 0; i < ile; i++)
	{
		switch (fork())
		{
		case -1:
			perror("\n #blad funkcji fork\n");
			exit(EXIT_FAILURE);
			break;

		case 0:
			if (execv(argv[2], 0) == -1)
			{
				perror("\n\n");
				exit(EXIT_FAILURE);
			}
			break;
		}
	}

	for (int i = 0; i < ile; i++)
		wait(0);

	usun(s_id);

	return 0;
}
