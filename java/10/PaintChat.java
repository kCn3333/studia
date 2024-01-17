import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.beans.XMLDecoder;
import java.beans.XMLEncoder;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.border.BevelBorder;
import javax.swing.border.LineBorder;
import javax.swing.border.TitledBorder;

/*
AS A SERVER                             AS A CLIENT
,--------------.                      ,--------------.
|            ,-|                      |              |
|    accept  | |<---------------------|   create     |
|            `-|                      |              |
|            ,-|                      |-.            |
| read/write | | <------------------->| | read/write |
|            `-|                      |-'            |
`--------------'                      `--------------'
*/
public class PaintChat extends JPanel
implements MouseListener, MouseMotionListener, ActionListener{
   
	private static final long serialVersionUID = 1L;
	
		public static boolean connected=false;
		public static boolean server=false;
	    private static JFileChooser chooser;
	    public static Thread t;
	   
	   private ArrayList<ArrayList<Point>> strokes,strokes2;
	   private int lineCounter;
	   private int counter;
	   private ArrayList<Point> temp;
	   private static String status;
	   
	   //private static int portNumber =2222;
	   private static ServerSocket listener;
	   private static Socket clientSocket;
       static PrintWriter out = null;
       static BufferedReader in = null;
       public static ObjectOutputStream objectOutput;
       public static ObjectInputStream objectInput;
	   
	
	   private static JPanel statusPanel;
	   private static JLabel statusLabel;
	private static JMenu menuFile;
	private static JMenuItem menuitemExit;
	private static JMenuItem menuitemNew;
	private static JMenuItem menuitemXML;
	private static JMenuItem menuitemJPG;
	private static JMenuItem menuitemFromXML;
	private static JMenuItem menuitemConnect;
	private static JMenuItem menuitemConnectfrom;

	
	private static JMenuBar mb;
	Font f12 = new Font("Verdana", 0, 12);
	Font f121 = new Font("Verdana", 1, 12);


 
      @SuppressWarnings("unused")
      private int prevX, prevY; 
      private boolean dragging;  
      

      private Graphics graphicsForDrawing;  
      BufferedImage off_Image;

      public PaintChat() {
    	  
    	  off_Image =
    	  	    new BufferedImage(622,565,
    	  	                      BufferedImage.TYPE_INT_ARGB);

    	  graphicsForDrawing=off_Image.createGraphics();
    	  
    	  
         setBackground(Color.WHITE);
         addMouseListener(this);
         addMouseMotionListener(this);
         //setSize(100,100);
                 
         statusPanel = new JPanel();
         statusPanel.setBorder(new BevelBorder(BevelBorder.LOWERED));
         statusPanel.setPreferredSize(new Dimension(getWidth(), 16));
         statusPanel.setLayout(new BoxLayout(statusPanel, BoxLayout.X_AXIS));
         statusLabel = new JLabel("status");
         statusLabel.setHorizontalAlignment(SwingConstants.LEFT);
         statusPanel.add(statusLabel);
         
 		menuFile = new JMenu("File");
		menuFile.setFont(f12);
		
		menuitemNew = new JMenuItem("New");
		menuitemNew.setFont(f121);
				menuitemNew.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N,
				ActionEvent.CTRL_MASK));
		menuFile.add(menuitemNew);
		menuFile.addSeparator();
		
		menuitemConnect = new JMenuItem("Connect to");
		menuitemConnect.setFont(f12);
		menuFile.add(menuitemConnect);
		
		menuitemConnectfrom= new JMenuItem("Make connection");
		menuitemConnectfrom.setFont(f12);
		menuFile.add(menuitemConnectfrom);
		menuFile.addSeparator();
		
		menuitemXML = new JMenuItem("Save To XML");
		menuitemXML.setFont(f12);
		menuFile.add(menuitemXML);
		
		menuitemJPG= new JMenuItem("Save To JPG");
		menuitemJPG.setFont(f12);
		menuFile.add(menuitemJPG);
		
		menuitemFromXML = new JMenuItem("Read from XML");
		menuitemFromXML.setFont(f12);
		menuFile.add(menuitemFromXML);
		menuFile.addSeparator();
		
		
		menuitemExit = new JMenuItem("Exit");
		menuitemExit.setFont(f12);
		menuitemExit.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_X,
				ActionEvent.CTRL_MASK));
		menuFile.add(menuitemExit);
		
		menuitemNew.addActionListener(this);
		menuitemXML.addActionListener(this);
		menuitemJPG.addActionListener(this);
		menuitemFromXML.addActionListener(this);
		menuitemConnect.addActionListener(this);
		menuitemConnectfrom.addActionListener(this);
		menuitemExit.addActionListener(this);
		

		

		mb = new JMenuBar();
		mb.add(menuFile);
         
		strokes = new ArrayList<ArrayList<Point>>();
		strokes.add(new ArrayList<Point>());
	    chooser = new JFileChooser();
	    lineCounter=0;
	    counter=0;
	    temp=new ArrayList<Point>();
	    status="";
      }
      
      
      public void paintComponent(Graphics g)
      {
          super.paintComponent(g);
          Graphics2D g2 = (Graphics2D)g;
          for (int i = 0; i < strokes.size(); i++)
          {
        	  for (int j = 0; j < strokes.get(i).size()-1; j++) {
              g2.drawLine(strokes.get(i).get(j).getX(),strokes.get(i).get(j).getY(),
            		  	  strokes.get(i).get(j+1).getX(),strokes.get(i).get(j+1).getY());
        	  }
          }
        	  
      }
      

      
      
      @SuppressWarnings("unchecked")
	private void load()
      {
         // show file chooser dialog
         int r = chooser.showOpenDialog(null);

         // if file selected, open
         if(r == JFileChooser.APPROVE_OPTION)
         {
            try
            {
               File file = chooser.getSelectedFile();
               XMLDecoder decoder = new XMLDecoder(new FileInputStream(file));
               Object obj=decoder.readObject(); 
               if ( obj instanceof ArrayList<?> ) {  
              	  ArrayList<?> temp=(ArrayList<?>)obj;
            	  if (temp.get(0) instanceof ArrayList<?>) {
            		  strokes2 = (ArrayList<ArrayList<Point>>)temp;  
                  }  
               }

   			   strokes.clear();
   			   lineCounter=0;
   			   strokes=new ArrayList<ArrayList<Point>>();
   			   
   			   repaint(); 
   			   lineCounter=strokes2.size()-1;
   			   strokes=strokes2;
   			   repaint(); 
   			   decoder.close();

   			   if(connected){   			   
   				   try {
   					   objectOutput.writeObject(strokes);
   					   objectOutput.flush();
   				   } catch (IOException e) {
   				
   					   e.printStackTrace();
   				   }
   			   }
   			   strokes.add( new ArrayList<Point>());
            }
            catch (IOException e)
            {
               JOptionPane.showMessageDialog(null, e);
            }
         }
      }

      private void save()
      {
			try {
                BufferedImage image = new BufferedImage(250, 250,
                        BufferedImage.TYPE_INT_RGB);
                Graphics2D g2 = image.createGraphics();
                super.paint(g2);
                g2.dispose();
				ImageIO.write(image, "jpeg", new File("image.jpeg"));
				JOptionPane.showMessageDialog(null, "Plik image.jpeg zosta³ zapisany na dysku");
			} catch (IOException e1) {
				 e1.printStackTrace();
			}
      }

      
      private void ToXml()
      {
    	  XMLEncoder ee;
		try {
			ee = new XMLEncoder(
			          new BufferedOutputStream(
			              new FileOutputStream("ImageXML.xml")));
	          ee.writeObject(strokes);
	          ee.close();
	          System.out.println("===================================================================="+counter);
	          System.out.println("> zapisano do XML:");
	          
	          OutputStream memStream = new ByteArrayOutputStream();
	          XMLEncoder mencoder = new XMLEncoder(memStream);
	          mencoder.writeObject(strokes);//.getContentPane()
	          mencoder.close();
	          String xmlString = memStream.toString();
	          System.out.println(xmlString);
	          counter++;
	          JOptionPane.showMessageDialog(null, "Plik ImageXML.xml zosta³ zapisany na dysku");
	          
		} catch (FileNotFoundException e) {
			System.out.println("nie powiodlo sie zapisanie...");
			e.printStackTrace();
		}



    	  
      }
      
      /*
      public void repaint(){
			strokes.clear();
			lineCounter=0;
			strokes=new ArrayList<ArrayList<Point>>();
			strokes.add( new ArrayList<Point>());
			super.repaint(); 
    	  
      }*/
      
      	private static void Connection(){
      		
      		String port = JOptionPane.showInputDialog(null,"enter port number: ");
		    try {
				listener = new ServerSocket(Integer.parseInt(port));
				server=true;
			} catch (IOException e1) {
				System.out.println("can't make a serverSocket at port "+port);
				e1.printStackTrace();
			}
			JOptionPane.showMessageDialog(null, "waiting for connection on port "+port);
			try {
				clientSocket= listener.accept();
			} 
			catch (IOException e2) {

				System.out.println("fail to accept() "+port);
				e2.printStackTrace();
			}
		    int reply = JOptionPane.showConfirmDialog(null, "do you want to accept connection ?", "", JOptionPane.YES_NO_OPTION);
	        if (reply == JOptionPane.YES_OPTION) {
	          JOptionPane.showMessageDialog(null, "OK");
	          connected=true;
	          System.out.println("Conection accepted, conected: "+connected);
	          t.start();
	        }
	        else {
	           try {
				clientSocket.close();
	           } 
	           catch (IOException e1) {
				System.out.println("can't make a serverSocket at port "+port);
				e1.printStackTrace();
	           }
	        }

            try  {
                	objectOutput = new ObjectOutputStream(clientSocket.getOutputStream());
            } 
            catch (IOException e) 
            {
                e.printStackTrace();
            } 
            try {
					objectInput = new ObjectInputStream(clientSocket.getInputStream());
			} catch (IOException e) {

				e.printStackTrace();
			}
			status ="  |  working as a server on port "+port;
			
      	}

      
 
          private static void RequestConnection()
          {
        	  //String answer=JOptionPane.showInputDialog(null, "establish connection with : ", 
        		//	  "", 1);
        	  String answer="localhost";
        	  String answer2=JOptionPane.showInputDialog(null, "on port number : ", 
        			  "", 1);
        	  //System.out.println(">>host: "+answer+":"+answer2);
              try {
                  clientSocket = new Socket(answer, Integer.parseInt(answer2));
                  try  {
                      objectOutput = new ObjectOutputStream(clientSocket.getOutputStream());
                  } 
                  catch (IOException e) 
                  {
                      e.printStackTrace();
                  } 
                  try {
      					objectInput = new ObjectInputStream(clientSocket.getInputStream());
      					
      			} catch (IOException e) {

      				e.printStackTrace();
      			}
      			connected=true;
      			System.out.println("request accepted, conected: "+connected);
      			t.start();
              } catch (UnknownHostException e) {
                  System.err.println("Don't know about host: "+answer);
                  //System.exit(1);
              } catch (IOException e) {
                  System.err.println("Couldn't get I/O for "
                                     + "the connection to: "+answer+":"+answer2);
                  //System.exit(1);
              }
              status ="  |  connected with "+answer+":"+answer2;
              
 
          }
      
      
      
      
      
  	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == menuitemNew) {
			strokes.clear();
			lineCounter=0;
			strokes=new ArrayList<ArrayList<Point>>();
			strokes.add( new ArrayList<Point>());
			repaint(); 
	        if(connected){
	        	try {
	        		System.out.println("wysylam: ");
	        		System.out.println(strokes);
	        		objectOutput.writeObject(strokes);
	        		objectOutput.flush();
	        		
	        	} catch (IOException ee) {
				
	        		ee.printStackTrace();
	        	}
	        }
		} 
		else if (e.getSource() == menuitemXML) {
			ToXml();
		} 
		else if (e.getSource() == menuitemJPG) {
			save();
		} 
		else if (e.getSource() == menuitemExit) {
			System.exit(0);
		}
		else if (e.getSource() == menuitemConnect){
			RequestConnection();
		}
		else if(e.getSource() == menuitemConnectfrom){
			Connection();
		}
		else if (e.getSource() == menuitemFromXML) {
			load();
		} 
  	}
  	
    private void setUpDrawingGraphics() {
        graphicsForDrawing = getGraphics();
     }
      
      
      /* ------------- nacisniecie przycisku myszy ------------- */
    public void mousePressed(MouseEvent evt) {
         
         int x = evt.getX();   
         int y = evt.getY();   
         
         int width = getWidth();   
         int height = getHeight();
         
         if (dragging == true) 
           return;    
         
         if (x > 3 && x < width - 3 && y > 3 && y < height - 3) {
            prevX = x;
            prevY = y;

            dragging = true;
            setUpDrawingGraphics();
            
          }
         
      }

      /* ------------- zwolnienie przycisku myszy ------------- */
    public void mouseReleased(MouseEvent evt) {		
         if (dragging == false)
            return;  
        dragging = false;
        graphicsForDrawing.dispose();
        graphicsForDrawing = null;
        
        if(connected){
        	try {
        		//System.out.println("wysylam: ");
        		//System.out.println(strokes);
        		objectOutput.reset();
        		objectOutput.writeObject(strokes);
        		objectOutput.flush();
        	} catch (IOException e) {
			
        		e.printStackTrace();
        	}
        }
        lineCounter++;
        strokes.add(new ArrayList<Point>());
        temp.clear();
        
      }
      
      /* ------------- ruch na wcisnietym przycisku myszy ------------- */
    public void mouseDragged(MouseEvent evt) {
         
         if (dragging == false)
            return;
         
         int x = evt.getX(); 
         int y = evt.getY(); 
                 
         if (x < 3)                
            x = 3;            
         if (x > getWidth() - 3) 
            x = getWidth() - 3;
         
         if (y < 3)         
            y = 3;             
         if (y > getHeight() - 3)    
            y = getHeight() - 3;
         
         //graphicsForDrawing.drawLine(prevX, prevY, x, y);
         
         strokes.get(strokes.size()-1).add(new Point(x,y));
         
         //temp.add(new Point(x,y));
         paint(graphicsForDrawing);
         
         
         prevX = x;
         prevY = y;
         statusLabel.setText(" "+(x-3)+", "+(y-3)+"px   |   "+(getWidth()-6)+" x "+(getHeight()-6)+"px"+status);
      } 
      
      /* ------------- mysz poza obszarem ------------- */
    public void mouseExited(MouseEvent evt) {          
    	  statusLabel.setText(" "+0+", "+0+"px   |   "+(getWidth()-6)+" x "+(getHeight()-6)+"px"+status);
      }    
      
      
      /* ------------- ruch myszy ------------- */
    public void mouseMoved(MouseEvent evt) {  
          int x = evt.getX();  
          int y = evt.getY();  
    	  if (x > 3 && x < getWidth() - 3 && y > 3 && y < getHeight() - 3) {
          statusLabel.setText(" "+(x-3)+", "+(y-3)+"px   |   "+(getWidth()-6)+" x "+(getHeight()-6)+"px"+status);
          }
    	  else {
        	  statusLabel.setText(" "+0+", "+0+"px   |   "+(getWidth()-6)+" x "+(getHeight()-6)+"px"+status);
    	  }
      }    
      
    public void mouseEntered(MouseEvent evt) { }
    public void mouseClicked(MouseEvent evt) { } 
      
      

    
    public static void main(String[] args) {
    	
    	String name = JOptionPane.showInputDialog(null,"What's your name?");
    	
          JFrame window = new JFrame("PaintChat");
          PaintChat p = new PaintChat();
          IncomePaint p2= new IncomePaint();
          
          t = new Thread(p2, "income");

          window.setSize(620,318);
          window.setJMenuBar(mb);
          
          JPanel pane1 = new JPanel();
          JPanel pane2 = new JPanel();
          
          Dimension size = new Dimension(250,250);
          p.setMaximumSize(size);
          p.setPreferredSize(size);
          p.setMinimumSize(size);
          p2.setMaximumSize(size);
          p2.setPreferredSize(size);
          p2.setMinimumSize(size);
          TitledBorder border = new TitledBorder(
                                    new LineBorder(Color.black),
                                    "",
                                    TitledBorder.CENTER,
                                    TitledBorder.BELOW_TOP);
          border.setTitleColor(Color.black);
          p.setBorder(border);
          p2.setBorder(border);
   
  
          //String title1;
          //title1 = "BOX 1:";
          String title2;
          title2 = "Income Box:";
  
          pane1.setBorder(BorderFactory.createTitledBorder(name));
          pane1.setLayout(new BoxLayout(pane1, BoxLayout.Y_AXIS));
          pane2.setBorder(BorderFactory.createTitledBorder(title2));
          pane2.setLayout(new BoxLayout(pane2, BoxLayout.Y_AXIS));
          pane1.add(p);
          pane2.add(p2);

          window.add(pane1,BorderLayout.WEST);
          window.add(pane2,BorderLayout.EAST);
          window.add(statusPanel, BorderLayout.SOUTH); 

          window.setLocation(100,100);
          window.setResizable( false );
          window.addWindowListener(new WindowAdapter() {

			public void windowClosing(WindowEvent e) {
          	  	connected=false;
          		System.out.println(">> server off line");
          		try {
          			if (connected)
          			clientSocket.close();
          			if (server)
          			listener.close();
				} catch (IOException e2) {
					e2.printStackTrace();
				}

              System.exit(0);
            }
          });
          window.pack();
          window.setVisible(true);
          


       }
      
   } 
