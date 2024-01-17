import java.io.Serializable;


public class Move implements Serializable{

	private static final long serialVersionUID = 1L;
	
	private int x;
	private int y;
	private char m;
	
	public Move(){
		x=0;
		y=0;
		m=0;
	}
	public Move(int xx, int yy, char mm){
		x=xx;
		y=yy;
		m=mm;
	}
	
	@Override
	public String toString() {
		return "[" + m + "] " + x + " " + y;
	}
	public int getX() {
		return x;
	}
	public void setX(int x) {
		this.x = x;
	}
	public int getY() {
		return y;
	}
	public void setY(int y) {
		this.y = y;
	}
	public char getM() {
		return m;
	}
	public void setM(char m) {
		this.m = m;
	}
	

}
