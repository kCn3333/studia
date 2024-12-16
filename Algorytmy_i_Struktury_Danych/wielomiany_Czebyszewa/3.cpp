/*--A-l-g-o-r-y-t-m-y--i--S-t-r-u-k-t-u-r-y--D-a-n-y-c-h--|
|                                                         |
|            3.cpp rekurencja drugiego stopnia            |
|                  wielomiany czebyszewa                  |
|                                                         |
|                                                         |
|--------------------------------------------------------*/

#include <iostream>

using namespace std;

double czebyszew(int n, double x)
{
if(n==0)
    return 1;
else if(n==1)
    return x;
else
    return ((2*x*czebyszew(n-1,x))-czebyszew(n-2,x));
}

main()
{
int n;
double x;

cout <<"\n\t>> Wielomiany Czebyszewa <<\n\n"
     <<"\tpodaj nr wyrazu ktory wyswietlic: ";
cin >>n;
cout <<"\tpodaj argument, x=";
cin >>x;

cout <<"\n\t#wynik: "<<czebyszew(n,x)<<"\n\n";

return 0;
}
