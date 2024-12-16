import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.SocketException;
import java.util.ArrayList;
import javax.swing.*;


public class IncomePaint extends JPanel implements Runnable
{
		private static final long serialVersionUID = 1L;
		private ArrayList<ArrayList<Point>> strokess;
 	   	BufferedImage off_Image;

	   	public IncomePaint() {
	   		setBackground(Color.WHITE);
	   		strokess = new ArrayList<ArrayList<Point>>();
	   	}
      
      
      public void paintComponent(Graphics g)
      {
          super.paintComponent(g);
          Graphics2D g2 = (Graphics2D)g;
          for (int i = 0; i < strokess.size(); i++){
        	  for (int j = 0; j < strokess.get(i).size()-1; j++){
       		   		  g2.drawLine(strokess.get(i).get(j).getX(),strokess.get(i).get(j).getY(),
           		  	  strokess.get(i).get(j+1).getX(),strokess.get(i).get(j+1).getY());
          	  }
          }

      }


	@SuppressWarnings("unchecked")
	@Override
	public void run() {

			while(PaintChat.connected) {
				//System.out.println(">odebralem: ");
            try {
                Object object=null;
				try {
					try {
						try {
							object = PaintChat.objectInput.readObject();
						} catch (SocketException e) {
							System.exit(1);
						}
					} catch (NullPointerException e) {
						//System.out.println("pusto... ");
						strokess =new ArrayList<ArrayList<Point>>();  
					}

					strokess = new ArrayList<ArrayList<Point>>();  
					
		               if ( object instanceof ArrayList<?> ) {  
		               	  ArrayList<?> temp=(ArrayList<?>)object;
		               	  //System.out.println("rozmiar: "+temp.size());
		               	  if (temp.get(0) instanceof ArrayList<?>) {
		             		  strokess = (ArrayList<ArrayList<Point>>)temp;
								repaint();
		                   }  
		                }
	            
				} catch (IOException e) {
					e.printStackTrace();
				}
				
                //System.out.println(strokess);

            } catch (ClassNotFoundException e) {
                System.out.println("strokes list has not come from the server");
                e.printStackTrace();
            }

		}
	}
		
}
      

      
      
      
      
      
  	
 
