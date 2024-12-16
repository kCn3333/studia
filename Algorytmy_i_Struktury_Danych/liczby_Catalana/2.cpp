/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|            2.cpp program wyliczajacy wartosci           |
|                   trzydziestu poczatkowych              |
|                        liczb Catalana                   |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>

using namespace std;

main()
{
    cout << "----------[L-i-c-z-b-y--C-a-t-a-l-a-n-a]----------" << endl;

    double c[30];
    c[0] = 1;

    for (int i = 1; i < 30; i++) // czyszczenie tablicy
    {
        c[i] = 0;
    }
    for (int n = 0; n < 30; n++)
    {
        c[n + 1] = (c[n] * (2 * n + 1) * 2) / (n + 2); // ze wzoru C(n+1)=(2(2n+1)*Cn)/(n+2)
    }

    for (int i = 0; i < 30; i++)
        cout << " C" << i << " " << c[i] << endl;
}
