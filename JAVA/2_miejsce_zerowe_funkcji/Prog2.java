
public abstract class Prog2 
{
	private static final double precision=0.00000001;				// precyzja obliczen
	private static final double start=	-1.0;					// poczatek przedzialu poszukiwan
	private static final double meta=	1.0;					// koniec przedzialu
	
	abstract protected double func(double x);

	protected double mzerowe()
	{
		double a=start;		// poczatek przedzialu
		double b=meta;		// koniec przedzialu
		double x0=0;	// potencjalne miejsce zerowe
		double fa=0;	// wartosc fukncji w poczatku przedzialu
		double fb=0;	// wartosc funkcji na koncu przedzialu
		double f0=0;	// wartosc funkcji w potencjalnym miejscu zerowym
		int iter=1; 	// licznik podzialow

		System.out.println("\n|------------------------------------------------------|");
		System.out.println("| OBLICZANIE MIEJSC ZEROWYCH FUNKCJI - METODA BISEKCJI |");
	    System.out.println("|------------------------------------------------------|\n");

	    fa = func(a);     // obliczamy wartoœci funkcji na koncach przedzialu
	    fb = func(b);
	    
	    if(fa * fb < 0)		// i sprawdzamy, czy funkcja ma tam ró¿ne znaki
	    {
	        while(true)
	        {
	            x0 = (a + b) / 2;
	            f0 = func(x0);
	          
	            if(Math.abs(f0) < precision) 	 // sprawdzamy, czy x0 jest przybli¿onym pierwiastkiem
	            {
	            	System.out.println(">> po " + iter + " podzialach odnalezione miejsce zerowe:" );
	            	System.out.println("x0 = " + x0 + " f(x0) = " + f0 );
	                break; 		// pierwiastek znaleziony, przerywamy pêtlê
	            }
	            if(fa * f0 < 0)		// za nowy przedzia³ przyjmujemy te polowke, w której funkcja zmienia znak
	            {
	                b = x0; fb = f0; iter++;
	            }
	            else
	            {
	                a = x0; fa = f0; iter++;
	            }
	        }
	    }
	    else System.out.println( "FUNKCJA NIE SPELNIA WARUNKU \n(wartosci na koncach przedzialow nie maja roznych znakow)\n");

	    return 0;
	} 
		
}
