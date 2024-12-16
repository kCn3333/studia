/*
   sortowanie babelkowe

--------------------------
Pawel Kwiecien
gr.1 SRO 10:00-12:00

*/

#include <iostream>

using namespace std;

main()
{
	int n = 0;
	int w[10] = {44, 55, 12, 42, 94, 18, 6, 67, 25, 72};
	for (int i = 0; i <= 10; i++)
	{
		cout << w[i] << " ";
	}
	cout << endl;

	for (int i = 0; i <= 10; i++)
	{
		for (int j = 0; j <= 10; j++)
		{
			if (w[j] > w[j + 1])
			{
				int a;
				a = w[j];
				w[j] = w[j + 1];
				w[j + 1] = a;
			}
		}
	}

	for (int i = 0; i <= 10; i++)
		cout << w[i] << " ";
	cout << endl;
}
