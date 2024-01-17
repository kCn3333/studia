import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.UnknownHostException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.SwingConstants;
import javax.swing.UIManager;
import javax.swing.border.BevelBorder;
import javax.swing.text.DefaultCaret;

/**
** Class Server for Gomoku game 
*
*/
public class GomokuServer extends JFrame{

	private static final long serialVersionUID = 1L;
	
    static JTextArea console;
 	private static JPanel statusPanel;
 	private static JLabel statusLabel;
    private static ServerSocket listener;
    private static boolean ON;

    
	public static class tryNet {
		public static void displayStuff(String whichHost, InetAddress inetAddr) {
	        console.append("[o==============================o]\n");
	        console.append("[       Tic Tac Toe Server       ]\n");
	        console.append("[o==============================o]\n\n");
	        console.append(" serwer up till "+getDateTime()+"\n");
	        
	        statusLabel.setText(" >> SERWER ONLINE <<");
			console.append("----------------------------------\n");
			console.append("> host: " + whichHost+"\n");
			console.append("> Canonical host name: " + inetAddr.getCanonicalHostName()+"\n");
			console.append("> Host Name: " + inetAddr.getHostName()+"\n");
			console.append("> Host Address: " + inetAddr.getHostAddress()+"\n");
			if(listener.getLocalPort()!=0) console.append("> Port: " + listener.getLocalPort()+"\n");
			console.append("----------------------------------"+"\n\n");
		}
	}
   public static String getDateTime() {
        DateFormat dateFormat = new SimpleDateFormat("[HH:mm:ss]");
        Date date = new Date();
        return dateFormat.format(date);
    }
	
   
    /**
     * Runs the application. Pairs up clients that connect
     */
    	GomokuServer() throws Exception {
    		ON=true;
    		console = new JTextArea();
            console.setEditable(false);
            console.setBackground(Color.BLACK);
            console.setForeground(Color.WHITE);
            console.setFont(new Font("Lucida Console", Font.PLAIN, 14));
            DefaultCaret caret = (DefaultCaret)console.getCaret();  // auto-scroll
            caret.setUpdatePolicy(DefaultCaret.ALWAYS_UPDATE);  
            
            this.add(new JScrollPane(console));
            this.pack();
            this.setSize(310, 310);
            this.setVisible(true);
            this.setTitle("GomokuServer");
            //this.setResizable(false);
            
            this.addWindowListener(new WindowAdapter() {
              public void windowClosing(WindowEvent e) {
            	  	ON=false;
            		System.out.println(">> server off line");
  
            		try {
						Thread.sleep(3000L);
					} catch (InterruptedException e1) {
						e1.printStackTrace();
					}
                System.exit(0);
              }
            });
            
            statusPanel = new JPanel();
            statusPanel.setBorder(new BevelBorder(BevelBorder.LOWERED));
            statusPanel.setPreferredSize(new Dimension(this.getWidth(), 16));
            statusPanel.setLayout(new BoxLayout(statusPanel, BoxLayout.X_AXIS));
            statusLabel = new JLabel("status");
            statusLabel.setFont(new Font("Lucida Console", Font.PLAIN, 14));
            
            statusLabel.setHorizontalAlignment(SwingConstants.LEFT);
            statusPanel.add(statusLabel);

            this.add(statusPanel, BorderLayout.SOUTH);
            statusPanel.setPreferredSize(new Dimension(this.getWidth(), 18));

            listener = new ServerSocket(9909);
            
      
        
        try {
            InetAddress inetAddr = InetAddress.getLocalHost();
            tryNet.displayStuff("localhost", inetAddr);
        }

        catch (UnknownHostException e) {
            e.printStackTrace();
        }

        try {
            while (ON) {
                Game game = new Game();
                Game.Player playerX = game.new Player(listener.accept(), 'X');
                Game.Player playerO = game.new Player(listener.accept(), 'O');
                playerX.setOpponent(playerO);
                playerO.setOpponent(playerX);
                game.currentPlayer = playerX;
                playerX.start();
                playerO.start();
            }
        } finally {
            listener.close();
        }
    }
    	
        public static void main(String[] args) throws Exception {
        	System.out.println(">> server on line");
      	  try {
              UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
          } catch (Exception unused) {
              ; 
          }
          
         GomokuServer window = new GomokuServer();
         window.setVisible(true);
  		
        }

}