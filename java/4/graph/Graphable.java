package graph;
import java.util.LinkedList;

public interface Graphable <T1,T2>{ 
	public void addVertex(T1 v);
	public void addEdge(T1 v1, T1 v2, T2 e);
	public LinkedList<T1> getNeighbours(T1 v); 
}

