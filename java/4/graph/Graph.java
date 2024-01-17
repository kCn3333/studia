package graph;

import java.util.LinkedList;
 
/**
 * Klasa graf skierowany, wazony
 */

public class Graph implements Graphable<Vertex, Edge>
{
    private LinkedList<Vertex> vertex = new LinkedList<Vertex>();    // lista wierzcholkow grafu
    private int vertexCount;            		// liczba wierzcholkow grafu 
 
    public Graph()
    {
        vertexCount = 0;
    }
 
    /**
     * Tworzy graf z n wierzcholkami
     * @param n ilosc wierzcholkow do utworzenia
     */
    public Graph(int n)
    {
        for(int i=0; i<n; i++)
            vertex.add(new Vertex(i));
 
        vertexCount = n;
    }
 
    public String toString()
    {
        String out = new String();
        for(Vertex v : vertex)
            if(v != null && v.toString() != "")
                out = out + v.toString() + "\n";
        return out;
    }
 
    /**
     * Dodaje kolejny wierzcholek do grafu
     */
    public void addVertex()
    {
        vertex.add( new Vertex(vertexCount) );
        vertexCount++;
    }
    /**
     * Dodaje wierzcholek do grafu
     */
    public void addVertex(Vertex x)
    {
        vertex.add( x );
        vertexCount++;
    }

 
    /**
     * Dodaje do grafu krawedz e
     * @param e krawedz ktora ma byc dodana do grafu
     */
    public void addEdge(Edge e)
    {
        vertex.get( e.getBegin().getNumber() ).addEdge( e );
    }
 
    /**
     * Dodaje do grafu krawedz o wadze w, a --> b.
     * @param a numer poczatkowego wierzcholka
     * @param b numer koncowego wierzcholka 
     * @param w waga dodawanej krawedzi
     */
    public void addEdge(int a, int b, double w)
    {
        if( a>=0 && a<=vertexCount && b>=0 && b<=vertexCount && vertex.get(a)!=null && vertex.get(b)!=null)
            addEdge( new Edge(vertex.get(a), vertex.get(b), w) ); 
    }
    public void addEdge(Vertex a, Vertex b, double w)
    {
        if( a.getNumber()>=0 && a.getNumber()<=vertexCount && b.getNumber()>=0 && b.getNumber()<=vertexCount && vertex.get(a.getNumber())!=null && vertex.get(b.getNumber())!=null)
            addEdge( new Edge(vertex.get(a.getNumber()), vertex.get(b.getNumber()), w) ); 
    }
    public void addEdge(Vertex a, Vertex b, Edge k)
    {
        if( a.getNumber()>=0 && a.getNumber()<=vertexCount && b.getNumber()>=0 && b.getNumber()<=vertexCount && vertex.get(a.getNumber())!=null && vertex.get(b.getNumber())!=null)
            addEdge( k ); 
    }

 
    /**
     * Zwraca wierzcholek o liczbie porzadkowej n
     * @param n liczba porzadkowa szukanego wierzcholka
     */
    public Vertex getVertex(int n)
    {
        return vertex.get(n);
    }
    
    /**
     * Zwraca liste sasiadow podanego wierzcholka
     * @param x interesujacy nas wierzcholek
     */
    public LinkedList<Vertex> getNeighbours(Vertex x)
    {
    	LinkedList<Vertex> n= new LinkedList<Vertex>();
        for(Edge e : x.edge)
            n.add(e.getEnd());
    	return n;
    }
    /**
     * Zwraca liste sasiadow podanego wierzcholka
     * @param x numer interesujacego nas wierzcholek
     */
    public LinkedList<Vertex> getNeighbours(int x)
    {
    	LinkedList<Vertex> n= new LinkedList<Vertex>();
        for(Edge e : vertex.get(x).edge)
            n.add(e.getEnd());
    	return n;
    }



}