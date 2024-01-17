
public class Test extends Prog2
{

	public double func(double x)
	{
		return x * x * x * (x + Math.sin(x * x - 1) - 1) - 1;
	}
	

	public static void main(String[] args) 
	{
		Test test1= new Test();
		test1.mzerowe();
	}

}
