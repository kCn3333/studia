package graph;

import java.util.LinkedList;

/**
 * Klasa  wierzcholek grafu
 */
public class Vertex
{
    private int number;    //numer wierzcholka
    protected LinkedList<Edge> edge = new LinkedList<Edge>();    //lista krawedzi wychodzacych z wierzcholka
 
    public Vertex(){}
 
    /**
     * @param i numer porzadkowy tworzonego wierzcholka
     */
    public Vertex(int i)
    {
        number = i;
    }
 
    public String toString()
    {
        String out = new String();
        out= "wierzcholek " + number + "\n-------------\n";
        if(edge.size() == 0) return out;
        for(Edge e : edge)
            out = out + e.toString() + "\n";
        return out;
    }
    
    public LinkedList<Vertex> getNeighbours()
    {
    	LinkedList<Vertex> n= new LinkedList<Vertex>();
        for(Edge e : edge)
            n.add(e.getEnd());
    	return n;
    }
    
    /**
     * Zwraca numer porzadkowy wierzcholka
     */
    public int getNumber() 
    {
        return number;
    }
 
    /**
     * Zwraca kopie listy krawedzi wychodzacych z wierzcholka
     */
    public LinkedList<Edge> getEdgeList()
    {
        return new LinkedList<Edge>(edge);
    }
 

    /**
     * Dodaje nowa krawedz do wierzcholka
     * @param e dodawana krawedz
     */
    public void addEdge(Edge e)
    {
        edge.add(e);
    }
    
}
 

