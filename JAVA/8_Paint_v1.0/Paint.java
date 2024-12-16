import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.border.BevelBorder;

public class Paint extends JPanel
implements MouseListener, MouseMotionListener, ActionListener{
   
	private static final long serialVersionUID = 1L;
	
 	private static JPanel statusPanel;
 	private static JLabel statusLabel;
	private static JMenu menuFile, menuColor;
	private static ButtonGroup group;
	private static JMenuItem menuitemExit;
	private static JMenuItem menuitemNew;
 	private static JRadioButtonMenuItem rbMenuItemBLACK;
 	private static JRadioButtonMenuItem rbMenuItemRED;   
 	private static JRadioButtonMenuItem rbMenuItemORANGE;   
 	private static JRadioButtonMenuItem rbMenuItemYELLOW; 
 	private static JRadioButtonMenuItem rbMenuItemGREEN; 
  	private static JRadioButtonMenuItem rbMenuItemCYAN;
 	private static JRadioButtonMenuItem rbMenuItemBLUE;
 	private final static int BLACK = 0;
 	private final static int RED = 1;   
 	private final static int ORANGE = 2;   
 	private final static int YELLOW = 3; 
 	private final static int GREEN = 4;   
 	private final static int CYAN = 5;
 	private final static int BLUE = 6;
      
    private int currentColor = BLACK; 
	
	private static JMenuBar mb;
	Font f12 = new Font("Verdana", 0, 12);
	Font f121 = new Font("Verdana", 1, 12);

 
      private int prevX, prevY; 
      private boolean dragging;  
      private Graphics graphicsForDrawing;  

      Paint() {
         setBackground(Color.WHITE);
         addMouseListener(this);
         addMouseMotionListener(this);
         //setSize(600,480);
                 
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

		menuitemExit = new JMenuItem("Exit");
		menuitemExit.setFont(f12);
		menuitemExit.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_X,
				ActionEvent.CTRL_MASK));
		menuFile.add(menuitemExit);
		
		menuitemNew.addActionListener(this);
		menuitemExit.addActionListener(this);
		

		menuColor = new JMenu("Color");
		menuColor.setFont(f12);
		menuFile.setMnemonic(KeyEvent.VK_C);
		group=new ButtonGroup();
		
		rbMenuItemBLACK = new JRadioButtonMenuItem("Black");
		rbMenuItemBLACK.setForeground(Color.black);
		rbMenuItemBLACK.setSelected(true);
		group.add(rbMenuItemBLACK);
		menuColor.add(rbMenuItemBLACK);

		rbMenuItemRED = new JRadioButtonMenuItem("Red");
		rbMenuItemRED.setForeground(Color.red);
		group.add(rbMenuItemRED);
		menuColor.add(rbMenuItemRED);
		
		rbMenuItemORANGE = new JRadioButtonMenuItem("Orange");
		rbMenuItemORANGE.setForeground(Color.orange);
		group.add(rbMenuItemORANGE);
		menuColor.add(rbMenuItemORANGE);
		
		rbMenuItemYELLOW = new JRadioButtonMenuItem("Yellow");
		rbMenuItemYELLOW.setForeground(Color.yellow);
		group.add(rbMenuItemYELLOW);
		menuColor.add(rbMenuItemYELLOW);
		
		rbMenuItemGREEN = new JRadioButtonMenuItem("Green");
		rbMenuItemGREEN.setForeground(Color.green);
		group.add(rbMenuItemGREEN);
		menuColor.add(rbMenuItemGREEN);
		
		rbMenuItemCYAN = new JRadioButtonMenuItem("Cyan");
		rbMenuItemCYAN.setForeground(Color.cyan);
		group.add(rbMenuItemCYAN);
		menuColor.add(rbMenuItemCYAN);
		
		rbMenuItemBLUE = new JRadioButtonMenuItem("Blue");
		rbMenuItemBLUE.setForeground(Color.blue);
		group.add(rbMenuItemBLUE);
		menuColor.add(rbMenuItemBLUE);
		
		rbMenuItemBLACK.addActionListener(this);
		rbMenuItemRED.addActionListener(this);  
		rbMenuItemORANGE.addActionListener(this);   
		rbMenuItemYELLOW.addActionListener(this); 
		rbMenuItemGREEN.addActionListener(this); 
		rbMenuItemCYAN.addActionListener(this);
		rbMenuItemBLUE.addActionListener(this);

		mb = new JMenuBar();
		mb.add(menuFile);
		mb.add(menuColor);
         
      }
      
  	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == menuitemNew) {
			repaint(); 
		} 
		else if (e.getSource() == menuitemExit) {
			System.exit(0);
		}
		else if(e.getSource()== rbMenuItemBLACK) currentColor=BLACK;
		else if(e.getSource()== rbMenuItemRED) currentColor=RED;
		else if(e.getSource()== rbMenuItemORANGE) currentColor=ORANGE;
		else if(e.getSource()== rbMenuItemYELLOW) currentColor=YELLOW;
		else if(e.getSource()== rbMenuItemGREEN) currentColor=GREEN;
		else if(e.getSource()== rbMenuItemCYAN) currentColor=CYAN;
		else if(e.getSource()== rbMenuItemBLUE) currentColor=BLUE;
  	}
  	
    private void setUpDrawingGraphics() {
        graphicsForDrawing = getGraphics();
        switch (currentColor) {
        case BLACK:
           graphicsForDrawing.setColor(Color.BLACK);
           break;
        case RED:
           graphicsForDrawing.setColor(Color.RED);
           break;
        case ORANGE:
           graphicsForDrawing.setColor(Color.ORANGE);
           break;
        case YELLOW:
           graphicsForDrawing.setColor(Color.YELLOW);
           break;
        case GREEN:
           graphicsForDrawing.setColor(Color.GREEN);
           break;
        case CYAN:
           graphicsForDrawing.setColor(Color.CYAN);
           break;
        case BLUE:
            graphicsForDrawing.setColor(Color.BLUE);
            break;
        }
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
         
         graphicsForDrawing.drawLine(prevX, prevY, x, y);
         
         prevX = x;
         prevY = y;
         statusLabel.setText(" "+(x-3)+", "+(y-3)+"px   |   "+(getWidth()-6)+" x "+(getHeight()-6)+"px");
      } 
      
      /* ------------- mysz poza obszarem ------------- */
      public void mouseExited(MouseEvent evt) {          
    	  statusLabel.setText(" "+0+", "+0+"px   |   "+(getWidth()-6)+" x "+(getHeight()-6)+"px");
      }    
      
      
      /* ------------- ruch myszy ------------- */
      public void mouseMoved(MouseEvent evt) {  
          int x = evt.getX();  
          int y = evt.getY();  
    	  if (x > 3 && x < getWidth() - 3 && y > 3 && y < getHeight() - 3) {
          statusLabel.setText(" "+(x-3)+", "+(y-3)+"px   |   "+(getWidth()-6)+" x "+(getHeight()-6)+"px");
          }
    	  else {
        	  statusLabel.setText(" "+0+", "+0+"px   |   "+(getWidth()-6)+" x "+(getHeight()-6)+"px");
    	  }
      }    
      
      public void mouseEntered(MouseEvent evt) { }
      public void mouseClicked(MouseEvent evt) { } 
      
      
      public static void main(String[] args) {
          JFrame window = new JFrame("Paint");
          Paint p = new Paint();
       
          window.setJMenuBar(mb);
          
          window.add(statusPanel, BorderLayout.SOUTH);
          statusPanel.setPreferredSize(new Dimension(window.getWidth(), 18));
          window.add(p);
          //window.setContentPane(p);
          //window.getContentPane().setPreferredSize(new Dimension(400, 400));
          window.setSize(622,565);
          window.setLocation(100,100);
          window.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
          window.setVisible(true);

       }
      
   } 
