import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Collections;


/**
** Class Game 
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
class Game {

private int size=100;	// size of a board is size*size
Player currentPlayer;	// current Player
private ArrayList<Game.Field> board = new ArrayList<Field>();	// board for storing occupied fields
private Field field;

    /**
     * Class for storing fields 
     * x and y are coordinates, x for number of row and y for columns
     * mark is a sight of player   
     */
	class Field implements Comparable<Game.Field> {
		private int x;
		private int y;
		private char mark;
	
		Field(int a, int b, char m) {
			this.x=a;
			this.y=b;
			this.mark=m;
		}
		Field(int a, int b, Player p) {
			this.x=a;
			this.y=b;
			this.mark=p.mark;
		}
		Field() {
			this.x=0;
			this.y=0;
			this.mark=0;
		}
		Field(Field p) {
			this.x=p.x;
			this.y=p.y;
			this.mark=p.mark;
		}
		Field(int location, Player pp) {
			this.y=location%size;
			this.x=location/size;
			this.mark=pp.mark;
		}
		
		void incrementX(){
			this.x++;
		}
		void incrementY(){
			this.y++;
		}
		void decrementX(){
			this.x--;
		}
		void decrementY(){
			this.y--;
		}
		
		public String toString(){
			String s= new String();
			s=this.mark+" moves to ("+this.x+","+this.y+")\n";
			return s;
		}

		@Override
			public int compareTo(Field p) {
				int xx = ((Field) p).x; // same type object
				int yy = ((Field) p).y; // same type object
				if (this.x > xx)
					return 1;
				else if (this.x < xx)
					return -1;
				else if(this.x==xx & this.y > yy)
					return 1;
				else if(this.x==xx & this.y < yy)
					return -1;
				else
					return 0;
			}
		
	    public boolean equals(Object object) {
	        boolean sameSame = false;
	        if (object != null && object instanceof Field) {
	            sameSame = (this.x == ((Field) object).x && this.y == ((Field) object).y);
	        }
	        return sameSame;
	    }
			
	}
	//------------------------------end of class Field--------------------------------	
	
	/**
     * check if player is a winner
     * variable 'z' could be X or O for current player
     */
    public boolean isWinner(char z)
    {
    	ArrayList<Game.Field> boardTemp = new ArrayList<Field>();
    	Field fieldNextX;
    	Field fieldNextY;
    	Field fieldNextXY;
    	Field fieldNextYX;

    	int count=0;
    	
    	for (Field item: board)
    	if(item.mark==z)
    		boardTemp.add(item);

        Collections.sort(boardTemp);
    	
    	for(Field item: boardTemp){
    		fieldNextX=new Field(item); fieldNextX.incrementX();
    		fieldNextY=new Field(item); fieldNextY.incrementY();
        	fieldNextXY=new Field(item); fieldNextXY.decrementY(); fieldNextXY.incrementX();
    		fieldNextYX=new Field(item); fieldNextYX.incrementY(); fieldNextYX.incrementX();
        
 
        	while(true){
        		if(boardTemp.contains(fieldNextX)) {	// checking horizontally 
        			++count;
        			if(count==4) return true;
        			fieldNextX.incrementX();
        		}
        		else { 
        			count=0;
        			break;
        		}
        	}
        	while(true){
            	if(boardTemp.contains(fieldNextY)) { 	// checking vertically 
            		++count;
        			if(count==4) return true;
        			fieldNextY.incrementY();
        		}
        		else { 
        			count=0;
        			break;
        		}
           	}
        	while(true){
            	if(boardTemp.contains(fieldNextXY)) {	// checking diagonally (from top to bottom)
            		++count;
        			if(count==4) return true;
        			fieldNextXY.incrementX();
        			fieldNextXY.decrementY();
        		}
        		else { 
        			count=0;
        			break;
        		}
           	}
        	while(true){
            	if(boardTemp.contains(fieldNextYX)) { 	// checking diagonally (from bottom to top)
            		++count;
        			if(count==4) return true;
        			fieldNextYX.incrementX();
        			fieldNextYX.incrementY();
         		}
        		else { 
        			count=0;
        			break;
        		}
           	}
    	}
    	return false;
    	
    }


 //-------------- returns whether there are no more empty squares--------------
    public boolean boardFilledUp2() {		
    	if(board.size()==size*size)
        return true;			// if all fields are occupied
    	else return false;
    }

//-------------- checks if the move is legal--------------
    public synchronized boolean legalMove(Field p, Player player) {
    	
    	Field p2=new Field(p); 
    	if(p2.mark=='X') 
    		p2.mark='O'; 
    	else p2.mark='X'; 	
    	
        if (player == currentPlayer && !board.contains(p)  && !board.contains(p2)) {
        	board.add(p);
        	
            currentPlayer = currentPlayer.opponent;
            currentPlayer.otherPlayerMoved(p);
            return true;
        }
        return false;
    }
    

    /**
     * The class Player for multithread server application.
     * Player is identified by a character mark
     * which is 'X' or 'O'. For communication with the
     * client the player has a socket with input and output
     * streams.
     */
    class Player extends Thread {
        char mark;
        Player opponent;
        Socket socket;
        BufferedReader input;
        PrintWriter output;

        public Player(Socket socket, char mark) {
            this.socket = socket;
            this.mark = mark;
            try {
                input = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));
                output = new PrintWriter(socket.getOutputStream(), true);
                output.println("WELCOME " + mark);
                GomokuServer.console.append(GomokuServer.getDateTime()+" "+"WELCOME " + mark + " Player \n");
                output.println("MESSAGE Waiting for opponent to connect");
            } catch (IOException e) {
            	GomokuServer.console.append(GomokuServer.getDateTime()+" "+this.mark+" Player disconnected: " + e +"\n");
            }
        }

//-------------- setting opponent --------------
        public void setOpponent(Player opponent) {
            this.opponent = opponent;
        }


//-------------- handles the otherPlayerMoved message --------------
        public void otherPlayerMoved(Field p) {
            output.println("OPPONENT_MOVED " + p.x +" "+p.y);
            output.println(
                isWinner(p.mark) ? "DEFEAT" : boardFilledUp2() ? "TIE" : "");
        }

//-------------- the run method of this thread --------------

public void run() {
            try {
                // the thread is only started after everyone connects
                output.println("MESSAGE All players connected");
                

                // tell the first player that it is his turn
                if (mark == 'X') {
                    output.println("MESSAGE Your move");
                    GomokuServer.console.append(GomokuServer.getDateTime()+" Players connected \n");
                }

                // repeatedly get commands from the client and process them
                while (true) {
                    String command = input.readLine();
                    if (command.startsWith("MOVE")) {
                        int locX = Integer.parseInt(command.substring(command.indexOf(" ")+1,command.lastIndexOf(" ")));
                        int locY = Integer.parseInt(command.substring(command.lastIndexOf(" ")+1));
                        field=new Field(locX,locY,this);
                        
                        if (legalMove(field, this)) {
                            output.println("VALID_MOVE");
                            GomokuServer.console.append(GomokuServer.getDateTime()+" "+field );
                            
                            if(isWinner(this.mark)){
                            	output.println("VICTORY");
                            	GomokuServer.console.append(GomokuServer.getDateTime()+" Player "+field.mark +" is a winner \n" );
                            }
                            else if(boardFilledUp2()){
                            	output.println("TIE");
                            	GomokuServer.console.append(GomokuServer.getDateTime()+" we have a draw... \n" );
                            }
                            else output.println("");

                        } else {
                            output.println("MESSAGE ?");
                        }
                    } else if (command.startsWith("QUIT")) {
                        return;
                    }
                }
            } catch (IOException e) {
            	GomokuServer.console.append(GomokuServer.getDateTime()+" "+this.mark+" Player died: \n" + e +"\n");
            } finally {
                try {socket.close();} catch (IOException e) {}
            }
        }
    }
    }