import java.util.LinkedList;

import graph.*;

public class GraphTest {

	public static void main(String[] args) 
	{
		Graph graftestowy= new Graph();
		Vertex a= new Vertex(0);
		graftestowy.addVertex(a);
		Vertex b= new Vertex(1);
		graftestowy.addVertex(b);
		Vertex c= new Vertex(2);
		graftestowy.addVertex(c);
		
		Edge krawedz = new Edge(c,a,55);
		
		graftestowy.addEdge(krawedz);
		graftestowy.addEdge(a,b,10);
		graftestowy.addEdge(1,2,100);
		graftestowy.addEdge(2,1,70);
		
		LinkedList<Vertex> L= new LinkedList<Vertex>();
		L=graftestowy.getNeighbours(a);

		System.out.print(graftestowy);
		System.out.print("\n--------------------------");
		//System.out.print("\n" + c + "--------------------------\n" + graftestowy.getNeighbours(c));
		//System.out.print("\n" + a + "--------------------------\n" + a.getNeighbours());
		System.out.print("\n" + L);
		
		

	}

}
