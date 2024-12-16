import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
//import javax.swing.JScrollPane;

/**
* A client for the Gomoku game
* 
* ---------------------------------------------------
* | >> communication between client and server:		|
* ---------------------------------------------------
* | Client -> Server     | Server -> Client			|
* |----------------------|---------------------------
* | MOVE x y		     | WELCOME X, WELCOME O		|
* | QUIT                 | VALID_MOVE				|
* |                      | OTHER_PLAYER_MOVED x y	| 
* |                      | VICTORY					|
* |                      | DEFEAT					|	
* |                      | TIE						|
* |                      | MESSAGE <text>			|
* ---------------------------------------------------
**/
public class GomokuClient {

	
    private JFrame frame = new JFrame("Tic Tac Toe");
    private JPanel boardPanel;
    private JLabel messageLabel = new JLabel("");
    private ImageIcon icon;
    private ImageIcon opponentIcon;

    private int size=20;
    //private int newSize=size;
    private int startX=0;
    private ArrayList<Square> board=new ArrayList<Square>();
    
    private Square s;
    private Square currentSquare;

    private static int PORT = 9909;
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;
    
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
        				out.println("MOVE " + currentSquare.locationX +" "+currentSquare.locationY);
                    }
                });
            
        	board.add(s);
            boardPanel.add(s);
        	}
        }
        frame.add(boardPanel, "Center");
        //frame.add(new JScrollPane(boardPanel));
    }
    
    /**
     * The main thread of the client will listen for messages
     * from the server. 
     */
    public void play() throws Exception {
        String response;
        try {
            response = in.readLine();
            if (response.startsWith("WELCOME")) {
                char mark = response.charAt(8);
                icon = new ImageIcon(mark == 'X' ? "x.gif" : "o.gif");
                opponentIcon  = new ImageIcon(mark == 'X' ? "o.gif" : "x.gif");
                frame.setTitle("Player " + mark);
            }
            while (true) {
                response = in.readLine();
                if (response.startsWith("VALID_MOVE")) {
                    messageLabel.setText("Valid move, please wait");
                    currentSquare.setIcon(icon);
                    currentSquare.repaint();
                    //addSquares();
                } else if (response.startsWith("OPPONENT_MOVED")) {
                    int locX = Integer.parseInt(response.substring(response.indexOf(" ")+1,response.lastIndexOf(" ")));
                    int locY = Integer.parseInt(response.substring(response.lastIndexOf(" ")+1));
                    board.get(board.indexOf(new Square(locX,locY))).setIcon(opponentIcon);
                    board.get(board.indexOf(new Square(locX,locY))).repaint();
                    //addSquares();
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
    static class Square extends JPanel {
		private static final long serialVersionUID = 1L;
		
		private int locationX=0;
		private int locationY=0;
		
		
		JLabel label = new JLabel((Icon)null);
		

        public Square() {
            setBackground(Color.white);
            add(label);
        }

        public Square(int x, int y) {
        	locationX=x;
        	locationY=y;
            setBackground(Color.white);
            add(label);
        }
        

        public void setIcon(Icon icon) {
            label.setIcon(icon);
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