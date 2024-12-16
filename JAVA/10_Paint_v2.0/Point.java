import java.io.Serializable;

	public class Point implements Serializable{

		private static final long serialVersionUID = 1L;
		
		public int x,y;
		
		public void setX(int xx) {
			this.x=xx;
		}
		public void setY(int yy) {
			this.y=yy;
		}
		public int getX(){
			return this.x;
		}
		public int getY(){
			return this.y;
		}
		
		public Point() {
			this.x=0; this.y=0;
		}
		public Point(int xx,int yy) { 
			this.x=xx; this.y=yy;
		}
		
		
	}