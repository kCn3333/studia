import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
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
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.filechooser.FileNameExtensionFilter;




/**
* A client for the Gomoku game
* 
* ---------------------------------------------------
* | >> communication between client and server:		|
* ---------------------------------------------------
* | Client -> Server     | Server -> Client			|
* |----------------------|---------------------------
* | CLEAR				 | CLEAR					|
* | LOAD				 | LOAD						|
* | [X] x y				 | [X] x y 					|	
* | MOVE x y		     | WELCOME X, WELCOME O		|
* | QUIT                 | VALID_MOVE				|
* |                      | OTHER_PLAYER_MOVED x y	| 
* |                      | VICTORY					|
* |                      | DEFEAT					|	
* |                      | TIE						|
* |                      | MESSAGE <text>			|
* ---------------------------------------------------
**/
public class GomokuClient implements ActionListener{

	
    private JFrame frame = new JFrame("Tic Tac Toe");
    private JPanel boardPanel;
    private JLabel messageLabel = new JLabel("");
    private ImageIcon icon;
    private ImageIcon opponentIcon;
    
	private static JMenu menuFile;
	private static JMenuBar mb;
	private static JMenuItem menuitemExit;
	private static JMenuItem menuitemNew;
	private static JMenuItem menuitemXML;
	private static JMenuItem menuitemJPG;
	private static JMenuItem menuitemFromXML;

    private int size=20;
    //private int newSize=size;
    private int startX=0;
    private ArrayList<Square> board=new ArrayList<Square>();
    private ArrayList<Move> moves=new ArrayList<Move>();
    
    private Square s;
    private Square currentSquare;

    private static int PORT = 9909;
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;
    private char mark;
    private String response;
    
    /*
    private enum Direction {
    	NORTH, SOUTH, EAST, WEST;
    }
	*/

    public GomokuClient(String serverAddress) throws Exception {

        //--------------- Setup networking ---------------
        socket = new Socket(serverAddress, PORT);
        in = new BufferedReader(new InputStreamReader(
            socket.getInputStream()));
        out = new PrintWriter(socket.getOutputStream(), true);

        //--------------- Layout GUI ---------------
 		menuFile = new JMenu("File");
		
		menuitemNew = new JMenuItem("New Game");
		menuFile.add(menuitemNew);
		menuFile.addSeparator();

		menuitemJPG= new JMenuItem("Save To JPG");
		menuFile.add(menuitemJPG);
		menuFile.addSeparator();
		
		menuitemXML = new JMenuItem("Save To XML");
		menuFile.add(menuitemXML);
				
		menuitemFromXML = new JMenuItem("Read from XML");
		menuFile.add(menuitemFromXML);
		menuFile.addSeparator();		
		
		menuitemExit = new JMenuItem("Exit");
		menuFile.add(menuitemExit);
		
		menuitemNew.addActionListener(this);
		menuitemXML.addActionListener(this);
		menuitemJPG.addActionListener(this);
		menuitemFromXML.addActionListener(this);
		menuitemExit.addActionListener(this);
        
        messageLabel.setBackground(Color.lightGray);
        frame.getContentPane().add(messageLabel, "South");

        boardPanel = new JPanel();
        boardPanel.setBackground(Color.black);
        boardPanel.setLayout(new GridLayout(size, size, 2, 2));
        for (int i = startX; i < size+startX; i++) {
        	for(int j= startX; j< size+startX; j++) {
        		final int location = ((i-startX)*size)+(j-startX);
        		s=new Square(i,j);
        		
        		s.addMouseListener(new MouseAdapter() {
        			public void mousePressed(MouseEvent e) {
        				currentSquare = board.get(location);
        				out.println("MOVE " + currentSquare.getLocationX() +" "+currentSquare.getLocationY());
        				
                    }
                });
            
        	board.add(s);
            boardPanel.add(s);
        	}
        }
		mb = new JMenuBar();
		mb.add(menuFile);
        frame.setJMenuBar(mb);
        frame.add(boardPanel, "Center");
        //frame.add(new JScrollPane(boardPanel));
    }
    
    /**
     * The main thread of the client will listen for messages
     * from the server. 
     */
    public void play() throws Exception {
        
        try {
            response = in.readLine();
            if (response.startsWith("WELCOME")) {
                mark = response.charAt(8);
                icon = new ImageIcon(mark == 'X' ? "x.gif" : "o.gif");
                opponentIcon  = new ImageIcon(mark == 'X' ? "o.gif" : "x.gif");
                frame.setTitle("Player " + mark);
            }
            while (true) {
                response = in.readLine();
                if (response.startsWith("CLEAR")) {
                	System.out.println(response);
                	clearBoard();

                }
                if (response.startsWith("LOAD")) {
                	//output.println("Waiting...");
                	//board = new ArrayList<Field>();
                	//opponent.output.println(response);
                	System.out.println(response);
                	response = in.readLine();
                	System.out.println("after LOAD "+response);  
                	
                	clearBoard();
                	
                	char m='0';
                	while (response.startsWith("[")){
                		System.out.println(response);
                		//opponent.output.println(response);
                		m=(char)(response.charAt(1));
                        int locX = Integer.parseInt(response.substring(response.indexOf(" ")+1,response.lastIndexOf(" ")));
                        int locY = Integer.parseInt(response.substring(response.lastIndexOf(" ")+1));
                        if(m==mark){
                            board.get(board.indexOf(new Square(locX,locY))).setIcon(icon);
                            board.get(board.indexOf(new Square(locX,locY))).repaint();
                        }
                        
                        else {
                            board.get(board.indexOf(new Square(locX,locY))).setIcon(opponentIcon);
                            board.get(board.indexOf(new Square(locX,locY))).repaint();
                        }
                        //field=new Field(locX,locY,m);
                        //board.add(field);
                        //output.println("Added");
                        response = in.readLine();
                	}
                	//if(m==mark) currentPlayer = currentPlayer.opponent;
                }
                if (response.startsWith("VALID_MOVE")) {
                    messageLabel.setText("Valid move, please wait");
                    currentSquare.setIcon(icon);
                    currentSquare.repaint();
                    
                    moves.add(new Move(currentSquare.getLocationX(),currentSquare.getLocationY(),mark) );
                    //addSquares();
                } else if (response.startsWith("OPPONENT_MOVED")) {
                    int locX = Integer.parseInt(response.substring(response.indexOf(" ")+1,response.lastIndexOf(" ")));
                    int locY = Integer.parseInt(response.substring(response.lastIndexOf(" ")+1));
                    board.get(board.indexOf(new Square(locX,locY))).setIcon(opponentIcon);
                    board.get(board.indexOf(new Square(locX,locY))).repaint();
                    //addSquares();
                    moves.add(new Move(locX,locY,(mark=='X' ? 'O' : 'X')) );
                    
                    messageLabel.setText("Opponent moved, your turn");
                } else if (response.startsWith("VICTORY")) {
                    messageLabel.setText("You win");
                    break;
                } else if (response.startsWith("DEFEAT")) {
                    messageLabel.setText("You lose");
                    break;
                } else if (response.startsWith("TIE")) {
                    messageLabel.setText("You tied");
                    break;
                } else if (response.startsWith("MESSAGE")) {
                    messageLabel.setText(response.substring(8));
                }
            }
            out.println("QUIT");
        }
        finally {
            socket.close();
        }
    }
    public void clearBoard(){
    	for (Square item : board ){
    		board.get(board.indexOf(item)).clearIcon();
    		board.get(board.indexOf(item)).repaint();
    	}
    }
        
        
	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == menuitemNew) {
			clearBoard();
			out.println("CLEAR");
	

		} 
		else if (e.getSource() == menuitemXML) {
			ArrayList<Move> temp= new ArrayList<Move>();
			temp = moves;
			ToXml(temp);
		} 
		else if (e.getSource() == menuitemJPG) {
			save();
		} 
		else if (e.getSource() == menuitemExit) {
			System.exit(0);
		}
		else if (e.getSource() == menuitemFromXML) {
			System.out.println(moves);
			moves.clear();
			moves=load();
			//frame.repaint();
			System.out.println("-----------------loading from XML------------------");
			System.out.println(moves);
			out.println("LOAD");
			System.out.println(" loading to the server...");
			
			for(Square item: board){
				board.get(board.indexOf(item)).clearIcon();
				board.get(board.indexOf(item)).repaint();
			}

			//try {
			//response=in.readLine();	
			
				for(Move item : moves){
					
					out.println(item);
										
					int x=item.getX();
					int y=item.getY();
					ImageIcon iconn = new ImageIcon(item.getM()=='X' ? "x.gif" : "o.gif");
						//response=in.readLine();
	                board.get(board.indexOf(new Square(x,y))).setIcon(iconn);
	                board.get(board.indexOf(new Square(x,y))).repaint();

					
				}
				out.println("compled");
				/*
			} catch (IOException e1) {
				System.out.println(" error "+response+" ");
				e1.printStackTrace();
			}*/

				
		} 
  	}
	
    private void save()
    {
			try {
              BufferedImage image = new BufferedImage(600, 600,
                      BufferedImage.TYPE_INT_RGB);
              Graphics2D g2 = image.createGraphics();
              boardPanel.paint(g2);
              g2.dispose();
				ImageIO.write(image, "jpeg", new File("image.jpeg"));
				JOptionPane.showMessageDialog(null, "Plik image.jpeg zosta³ zapisany na dysku");
			} catch (IOException e1) {
				 e1.printStackTrace();
			}
    }
	
    private static void ToXml(ArrayList<Move> s)
    {
  	  XMLEncoder ee;
		try {
			ee = new XMLEncoder(
			          new BufferedOutputStream(
			              new FileOutputStream("GameXML.xml")));
			
	          ee.writeObject(s);
	          ee.close();
	          System.out.println("====================================================================");
	          System.out.println("> zapisano do XML:");
	          
	          OutputStream memStream = new ByteArrayOutputStream();
	          XMLEncoder mencoder = new XMLEncoder(memStream);
	          mencoder.writeObject(s);//.getContentPane()
	          mencoder.close();
	          String xmlString = memStream.toString();
	          System.out.println(xmlString);
	          JOptionPane.showMessageDialog(null, "Plik GameXML.xml zosta³ zapisany na dysku");
	          
		} catch (FileNotFoundException e) {
			System.out.println("nie powiodlo sie zapisanie...");
			e.printStackTrace();
		}
    }
    
	@SuppressWarnings("unchecked")
	private static ArrayList<Move> load()
    {
       
       JFileChooser chooser = new JFileChooser();
       FileNameExtensionFilter xmlfilter = new FileNameExtensionFilter(
           "xml files (*.xml)", "xml");
       chooser.setFileFilter(xmlfilter);
       chooser.setDialogTitle("Open game file");
       	// set selected filter
       chooser.setFileFilter(xmlfilter);
		// show file chooser dialog
       int r = chooser.showOpenDialog(null);
       ArrayList<Move> y=new ArrayList<Move>();

       // if file selected, open
       if(r == JFileChooser.APPROVE_OPTION)
       {
          try
          {
             File file = chooser.getSelectedFile();
             XMLDecoder decoder = new XMLDecoder(new FileInputStream(file));
             Object obj=decoder.readObject(); 
             if ( obj instanceof ArrayList<?> ) {  
            	  	y=(ArrayList<Move>) obj;
             }


 			   //repaint(); 
 			   decoder.close();

          }
          catch (IOException e)
          {
             JOptionPane.showMessageDialog(null, e);
          }
       }
       return y;
    }
    
    
    //-------------- do you want to play again ? --------------
    private boolean wantsToPlayAgain() {
        int response = JOptionPane.showConfirmDialog(frame,
            "Want to play again?"," ",
            JOptionPane.YES_NO_OPTION);
        frame.dispose();
        return response == JOptionPane.YES_OPTION;
    }

    /**
     * Class for storing fields 
     * x and y are coordinates, x for number of row and y for columns
     */
    


    public static void main(String[] args) throws Exception {
        while (true) {
            String serverAddress = (args.length == 0) ? "localhost" : args[1];
            GomokuClient client = new GomokuClient(serverAddress);
            client.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            client.frame.setSize(600,600);
            client.frame.setVisible(true);
            client.frame.setResizable(true);
            client.play();
            if (!client.wantsToPlayAgain()) {
                break;
            }
        }
    }


    
    
    /*
    private void addSquares(){
    	newSize=newSize+2;
    	startX--;
       	for(int i=startX; i<startX+newSize; i++){	// NORTH
   			s=new Square(startX,i);
			b.add(i-startX,s);
       	}
       	for(int i=startX+newSize; i<startX+newSize+newSize; i++){	// SOUTH
   			s=new Square(startX+newSize-1,i-newSize);
			b.add(s);
       	} 
       	for(int i=startX; i<startX+size; i=i+(newSize-1)){	// EAST
   			s=new Square(i,startX);
			b.add(i-startX,s);
       	}
       	for(int i=startX+newSize-1; i<startX+size; i=i+(newSize-1)){	// WEST
   			s=new Square(i,startX);
			b.add(i-startX,s);
       	}
       	
        boardPanel.setLayout(new GridLayout(newSize, newSize, 2, 2));

        for(Square item: b){
        	final int location = b.indexOf(item);
    		item.addMouseListener(new MouseAdapter() {
    			public void mousePressed(MouseEvent e) {
    				currentSquare = b.get(location);
    				out.println("MOVE " + currentSquare.locationX +" "+currentSquare.locationY);
                }
            });
        boardPanel=new JPanel();
        boardPanel.add(item);
        boardPanel.validate();
         item.repaint();
        }
    }
  	*/
}