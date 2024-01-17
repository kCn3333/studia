import java.util.Random;
import java.util.ArrayList;
//import java.util.Scanner;

public class Prog3
{
	public static int losuj(int x, int n)
	{
		Random losowa = new Random();
		ArrayList <Integer> wylosowane = new ArrayList <Integer>(n);
		
		 int counter =n;
		 int index=1;
		 boolean trafiony =false;		
		 int y=0;
		 
		for(int i=1; i<=n; i++)
		{
			y=losowa.nextInt(n);
			if(!wylosowane.contains(y)) wylosowane.add(y);
			else i--;
		}
		
		while(!trafiony)
		{
			index = losowa.nextInt(counter);
			//System.out.println(wylosowane.toString());
			if (wylosowane.get(index)==x) trafiony =true;
			else wylosowane.remove(index);
			counter--;
		} 
		//System.out.println("1] po " + (n-counter) +" probach ");
		//return wylosowane.get(index);
		return (n-counter);
		
	}
		
	//------------------------------------------------------------------------------
	public static int losuj2(int x, int n)
		{
			Random losowa = new Random();
			ArrayList <Integer> wylosowane = new ArrayList <Integer>(n);
			
			 int counter =n;
			 int index=1;
			 boolean trafiony =false;		
			 
			for(int i=0; i<=n; i++)
				 wylosowane.add(i); 

			while(!trafiony)
			{
				index = losowa.nextInt(wylosowane.size()-1);

				if (wylosowane.get(index)==x) trafiony =true;
				else 
					{
						if (wylosowane.get(index)<x)
							for(int j=index; j>=0; j--)
								wylosowane.remove(0);
						else
							for(int j=wylosowane.size()-1; j>=index; j--)
								wylosowane.remove(wylosowane.size()-1);
					}
				counter--;
				if(wylosowane.size()==1) { index =0; break; }
				//System.out.println(wylosowane.toString());
			} 
			//System.out.println("2] po " + (n-counter) +" probach ");
			//return wylosowane.get(index);
			return (n-counter);
		
	}
		
	//------------------------------------------------------------------------------
	public static int losuj3(int x, int n)
		{
			ArrayList <Integer> wylosowane = new ArrayList <Integer>(n);
			
			 int counter =1;
			 int index=0;
			 
			for(int i=0; i<=n; i++)
				wylosowane.add(i);

			int l = 0;
			int p = n;
			while (l <= p) 
			{
				index = (l + p) / 2;
			 
				if (wylosowane.get(index) == x) 
				{
					//System.out.println("3] po " + counter +" probach ");
					break;
				}
				else if (wylosowane.get(index) < x)
				{ l = index + 1; counter++;}
				else
				{ p = index - 1; counter++;}     
			}
			//return wylosowane.get(index);
			return counter;
		
	}

	public static void main(String[] args)
	{
	int n=100;						// zakres
	int k=(int)(Math.random()*n);	// szukana liczba	
	int a=0,b=0,c=0;	
	int ile=10000;					// liczba prob
	
	/*	Scanner skaner = new Scanner(System.in);
		System.out.println("\n Podaj zakres, od 0 do :");
		n = skaner.nextInt();
		System.out.println(" Podaj swoja liczbe :");
		k = skaner.nextInt();
	*/

		for(int i=0; i<ile; i++)
		{
			a+=losuj(k,n);
			b+=losuj2(k,n);
			c+=losuj3(k,n);
			k=(int)(Math.random()*n);
		}
		System.out.print(" | \n |(1)");
		for(int i=0; i<a/ile; i++) System.out.print("#");
		System.out.print("\n |(2)");
		for(int i=0; i<b/ile; i++) System.out.print("#");
		System.out.print("\n |(3)");
		for(int i=0; i<c/ile; i++) System.out.print("#");
		System.out.print("\n |"); 
		for(int i=0; i<(a/ile+1); i++) System.out.print("-");
		System.out.print("[" + (a/ile) + "]" + "->" + "\n"); 
		System.out.println(" > metoda 1: srednia liczba prob "+ a/ile);
		System.out.println(" > metoda 2: srednia liczba prob "+ b/ile);
		System.out.println(" > metoda 3: srednia liczba prob "+ c/ile);
		
		
	}

}