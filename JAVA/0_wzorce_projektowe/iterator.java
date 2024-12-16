
import java.util.*; 
class IteratorDemo { 
public static void main(String args[]) { 

ArrayList lista = new ArrayList(); 

lista.add("A"); 
lista.add("B"); 
lista.add("C"); 
lista.add("D"); 
lista.add("E"); 

System.out.print("orginalna lista: "); 
Iterator itr = lista.iterator(); 
while(itr.hasNext()) {

    Object element = itr.next(); 
    System.out.print(element + " ");

} 
System.out.println(); 

ListIterator litr = lista.listIterator(); 
while(litr.hasNext()) {

    Object element = litr.next(); 
    litr.set(element + "1");

} 
System.out.print("zmodyfikowana lista: "); 
itr = lista.iterator();
while(itr.hasNext()) {

    Object element = itr.next(); 
    System.out.print(element + " ");

} 
System.out.println(); 

} 
}