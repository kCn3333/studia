#include<iostream> 
#include<fstream> 
#include<cstdlib> 

using namespace std; 

int sc_zwyciestwa, pierwsze_losowanie, sc_odkryta; 

// funkcja sprawdzajaca ilosc poprawnych trafien w przypadku pozostania przy 1 wyborze 
int spr_sukces_a() 
{ 
    int losowa; 
    
    losowa = pierwsze_losowanie; 
    
    if(losowa == sc_zwyciestwa) 
       return 1;      
    else 
       return 0; 
} 

// funkcja sprawdzajaca ilosc poprawnych trafien przy losowym wyborze sciezki 
// gdy odslonimy juz jedna 
float spr_sukces_b() 
{ 
    int losowa; 
    int zmiana;//zmienna losowej zmiany sciezki(cos jak bool) 
    
    zmiana = rand() %2; 
    
    if(zmiana == 1)//gdy wylosujemy zmiane sciezki 
      do 
      { 
        losowa = rand() % 3; 
      } 
      while((losowa == pierwsze_losowanie) || (losowa == sc_odkryta)); 
        
    else//gdy wylosujemy pozostanie przy obecnej sciezce 
      losowa = pierwsze_losowanie; 
    
    if(losowa == sc_zwyciestwa) 
      return 1; 
    else 
      return 0; 
} 
// funkcja sprawdzajaca ilosc poprawnych trafien gdy zmienimy sciezke na 
// przeciwna po wczesniejszym odslonieniu jednej falszywej 
float spr_sukces_c() 
{ 
    int losowa; 
    
    do//zamiana sciezki 
    { 
      losowa = rand() % 3; 
    } 
    while((losowa == pierwsze_losowanie) || (losowa == sc_odkryta)); 
    
    if(losowa == sc_zwyciestwa) 
      return 1; 
    else 
      return 0; 
} 
// funkcja sprawdzajaca prawdopodobienstwo 
float chk_prawdopodobienstwo(int wybor)
{ 
    float prawd;//prawdopodobienstwo 
    float ile=0;//ile razy wypadnie sukces 
  
    for(int i=0; i < 10000; i++) 
    { 
        sc_zwyciestwa = rand() % 3; 
        pierwsze_losowanie = rand() % 3; 
        
        do//odkrywamy jedna falszywa sciezke 
        { 
           sc_odkryta = rand() % 3; 
        } 
        while((sc_odkryta == pierwsze_losowanie) || (sc_odkryta == sc_zwyciestwa)); 
        
        if(wybor == 1) 
        { 
            if(spr_sukces_a()==1)//jesli sukces to zwieksz      
              ile++; 
        } 
        if(wybor == 2) 
        { 
            if(spr_sukces_b()==1)//jesli sukces to zwieksz      
              ile++; 
                
        } 
        if(wybor == 3) 
        { 
           if(spr_sukces_c()==1)//jesli sukces to zwieksz      
              ile++;  
        } 
    } 
    prawd = ile / 10000.0; 
    
    return prawd; 
} 
main() 
{      
      int wybor; 
      
      while(1) 
      {                  //menu 
              cout<<"\n\tWpisz: \n\n" 
                    "\t[1] - aby spr.prawdopodobienstwo przy losowym wyborze sciezki\n" 
                    "\t[2] - aby spr.prawdopodobienstwo przy losowym wyborze sciezki,\n" 
                    "\t      a nastepnie jej losowej zamianie\n" 
                    "\t[3] - aby spr.prawdopodobienstwo przy losowym wyborze sciezki,\n" 
                    "\t      a nastepnie jej zamianie\n" 
                    "\t[4] - zby zakonczyc program\n"; 
              cin>>wybor; 
                    
         switch(wybor) 
         { 
                      case 1: 
                           cout<<"prawdopodobienstwo: "<<chk_prawdopodobienstwo(1)<<endl; 
                           break; 
                      
                      case 2: 
                           cout<<"prawdopodobienstwo: "<<chk_prawdopodobienstwo(2)<<endl; 
                           break; 
                            
                      case 3: 
                           cout<<"prawdopodobienstwo: "<<chk_prawdopodobienstwo(3)<<endl; 
                           break; 
                            
                      case 4: 
                           exit(0); 
                      
         } 
      } 
} 
