import java.util.*;
 
/* produkt koncowy */
class Zamowienie {
private String danie_glowne;
private String zupa;
private String przystawka;
private String napoj;
 
public void setDanie_glowne(String danie_glowne){
this.danie_glowne = danie_glowne ;
}
 
public void setZupa(String zupa){
this.zupa = zupa;
}
 
public void setPrzystawka(String przystawka){
this.przystawka = przystawka;
}
 
public void setNapoj(String napoj){
this.napoj = napoj;
}

 
public void show(){
if(danie_glowne!=null) System.out.println("danie_glowne = " + danie_glowne);
if(zupa!=null) System.out.println("zupa = " + zupa);
if(przystawka!=null) System.out.println("przystawka = " + przystawka);
if(napoj!=null) System.out.println("napoj = " + napoj);
}
}
 
/* glowny interface */
abstract class Builder {
protected Zamowienie Zamowienie;
 
public void newZestaw(){
Zamowienie = new Zamowienie();
}
 
public Zamowienie getZestaw(){
return Zamowienie;
}
 
public abstract void buildDanie_glowne();
public abstract void buildZupa();
public abstract void buildPrzystawka();
public abstract void buildNapoj();
}
 
 
class Zestaw1 extends Builder {
 
 
public void buildDanie_glowne(){
	Scanner in = new Scanner(System.in);
	 
	int a;
	while(true){
	System.out.println("Proponujemy: Schabowy [1], Mielony [2], Golonka [3]");
	a = in.nextInt();
	if(a>0 && a<4) break;
	}
	 
	String wynik="";
	if(a==1) wynik = "Schabowy";
	else if(a==2) wynik = "Mielony";
	else if(a==3) wynik = "Golonka";
	 
	Zamowienie.setDanie_glowne(wynik);
}
 
public void buildNapoj(){
	Scanner in = new Scanner(System.in);
	 
	int a;
	while(true){
	System.out.println("Dostepne napoje: Wino [1], Piwo [2], Woda [3]");
	a = in.nextInt();
	if(a>0 && a<4) break;
	}
	 
	String wynik="";
	if(a==1) wynik = "Wino";
	else if(a==2) wynik = "Piwo";
	else if(a==3) wynik = "Woda";
	 
	Zamowienie.setNapoj(wynik);
}
 
public void buildZupa(){
	Scanner in = new Scanner(System.in);
	 
	int a;
	while(true){
	System.out.println("Dostepne zupy: Pomidorowa [1], Grzybowa [2]");
	a = in.nextInt();
	if(a>0 && a<3) break;
	}
	 
	String wynik="";
	if(a==1) wynik = "Pomidorowa";
	else if(a==2) wynik = "Grzybowa";
	 
	Zamowienie.setZupa(wynik);
}
 
public void buildPrzystawka(){
	Zamowienie.setPrzystawka("Tatar");
}

}
 
 
 
class Zestaw2 extends Builder {
 
public void buildDanie_glowne(){
Zamowienie.setDanie_glowne("Schabowy");
}
 
public void buildZupa(){
Zamowienie.setZupa("Grzybowa");
}
 
public void buildPrzystawka(){
//zestaw bez przystawki
}
 
public void buildNapoj(){
Zamowienie.setNapoj("Piwo");
}
 
}
 
 
/* kelner */
class Director {
private Builder builder;
 
public void setBuilder(Builder builder){
this.builder = builder;
}
 
public Zamowienie getZestaw(){
return builder.getZestaw();
}
 
public void skladaj(){
builder.newZestaw();
builder.buildDanie_glowne();
builder.buildZupa();
builder.buildNapoj();
builder.buildPrzystawka();
}
}

public class Menu {

	public static void main(String[]args){
		 
		Director szef = new Director();
		Builder builder = new Zestaw1();
		Builder builder2 = new Zestaw2();
		 
		System.out.println("\nZESTAW1");
		szef.setBuilder(builder);
		szef.skladaj();
		Zamowienie zestaw1 = szef.getZestaw();
		 
		 
		szef.setBuilder(builder2);
		szef.skladaj();
		Zamowienie zestaw2 = szef.getZestaw();
		 
		 
		zestaw1.show();
		System.out.println("\n\nZESTAW2");
		zestaw2.show();
		}

}
