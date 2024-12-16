import java.awt.Color;
import java.io.Serializable;
import javax.swing.Icon;
import javax.swing.JLabel;
import javax.swing.JPanel;


public class Square extends JPanel implements Serializable{
		private static final long serialVersionUID = 1L;
		
		private int locationX;
		private int locationY;
		
		
		private JLabel label;
		

        public Square() {
            setBackground(Color.white);
            label=new JLabel((Icon)null);
            add(label);
        }

        public Square(int x, int y) {
        	locationX=x;
        	locationY=y;
            setBackground(Color.white);
            label=new JLabel((Icon)null);
            add(label);
        }
        

        public void setIcon(Icon icon) {
            label.setIcon(icon);
        }
        public void clearIcon() {
         	remove(label);
            label=new JLabel((Icon)null);
            add(label);
        }
        
        
	    public int getLocationX() {
			return locationX;
		}

		public void setLocationX(int locationX) {
			this.locationX = locationX;
		}

		public int getLocationY() {
			return locationY;
		}

		public void setLocationY(int locationY) {
			this.locationY = locationY;
		}

		public JLabel getLabel() {
			return label;
		}

		public void setLabel(JLabel label) {
			this.label = label;
		}

		public boolean equals(Object object)
	    {
	        boolean sameSame = false;
	        if (object != null && object instanceof Square){
	            sameSame = (this.locationX == ((Square) object).locationX && this.locationY == ((Square) object).locationY);
	        }
	        return sameSame;
	    }
		
		
	   
	    
    }
