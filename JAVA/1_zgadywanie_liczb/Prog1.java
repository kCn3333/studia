import java.util.Random;
import java.util.ArrayList;
import java.util.Scanner;

public class Prog1
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
			//System.out.println(" index= " + index + " war=" + wylosowane.get(index));
			//System.out.println(wylosowane.toString());
			if (wylosowane.get(index)==x) trafiony =true;
			else wylosowane.remove(index);
			counter--;
		} 
		System.out.println(" po " + (n-counter) +" probach ");
		return wylosowane.get(index);
		
	}

	public static void main(String[] args)
	{
		Scanner skaner = new Scanner(System.in);
		System.out.println("\n Podaj zakres, od 0 do :");
		int n = skaner.nextInt();
		System.out.println(" Podaj swoja liczbe :");
		int k = skaner.nextInt();
		System.out.println(" ------------------------");
		System.out.println(" odgadlem liczbe: "+ losuj(k,n));	
   
	}

}