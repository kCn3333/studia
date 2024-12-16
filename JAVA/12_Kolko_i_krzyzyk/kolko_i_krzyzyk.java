/*
o----------------P-r-o-j-e-k-t---J-A-V-A------------------o
|                                                         |
|     		Gra kó³ko i krzy¿yk, JavaSE-1.6 	          |
|													      |
|			trzy poziomy trudnoœci:                       |
|			- £atwy, komputer wykonuje losowe ruchy       |
|			- Œredni, pierwszy ruch losowy nastepne       |
|			  przy u¿yciu AI		                      |	
|			- Trudny, wszystkie ruchy wykonuje AI		  |
|                                                         |
|                  ____________________________________   |
|                  Pawe³ Kwiecieñ gr. "PON 10:00-12:00"   |
|             Eclipse Version: Helios Service Release 1	  |
|                               Build id: 20100917-0705   |
|                                                         |
o------------------------12.2o1o--------------------------o
*/

import java.awt.*;
import java.awt.event.*;
import java.util.Random;
import javax.swing.*;

public class kolko_i_krzyzyk implements ActionListener 		// interfejs
{
    private int[][] winCombinations = new int[][] {			//warunek wygranej
            {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, 	// poziomo
            {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, 	// pionowo
            {1, 5, 9}, {3, 5, 7} };            	// przekatna
            
    private int count = 0;						// licznik ruchow
    private String letter = "";					// X lub O
    private boolean win = false;			
    private int level=3;						// poziom trudnosci

    private JFrame okno = new JFrame("kolko i krzyzyk ");		// okno
    private JButton pole[] = new JButton[10];					// pola gry
    private JMenu menu = new JMenu("Menu");						
    private JMenu submenu = new JMenu("Poziom trudnosci");
    private JMenuBar menuBar= new JMenuBar();
    private JMenuItem[] items = {new JMenuItem("Nowa gra"), new JMenuItem("O programie"), new JMenuItem("Zakoñcz")};
    private JMenuItem menuItem;
    
    private ActionListener Quit = new ActionListener() {		// konczy program
    	public void actionPerformed(ActionEvent e){
    		System.exit(0);
    	}
    };
    private ActionListener Info = new ActionListener() {		// wyswietla informacje o programie
    	public void actionPerformed(ActionEvent e){
    		JOptionPane.showMessageDialog(null, "----------------------------" +
    										  "\n     Gra \"kó³ko i krzy¿yk\"  " +
    										  "\n     Jêzyk: Java SDK 1.4      " +
    										  "\n    Autor: Pawe³ Kwiecieñ    " +
    										  "\n     Wersja: v1.1.12.2010     " +
    										  "\n----------------------------");
    	}
    };
    private ActionListener NewGame = new ActionListener() {		// nowa gra
    	public void actionPerformed(ActionEvent e){
    		count =0; win=false;
    		reset();
    	}
    };

    private ActionListener NewGameL = new ActionListener() {	// nowa gra, poziom ³atwy
    	public void actionPerformed(ActionEvent e){
    		count =0; win=false; level=1;
    		reset();
    	}
    };
    private ActionListener NewGameS = new ActionListener() {	// nowa gra, poziom œredni 
    	public void actionPerformed(ActionEvent e){
    		count =0; win=false; level=2;
    		reset();
    	}
    };
    private ActionListener NewGameT = new ActionListener() {	// nowa gra, poziom trudny
    	public void actionPerformed(ActionEvent e){
    		count =0; win=false; level=3;
    		reset();
    	}
    };


    public kolko_i_krzyzyk()
    {
    	 
    okno.setPreferredSize(new Dimension(300,300));			// otwiera okno
    okno.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);	// zamykanie okna
    okno.setLayout(new GridLayout(3,3));					// tabelka 3x3
    
    for(int i = 1; i<=9; i++)
    {
        pole[i] = new JButton();
        pole[i].setFont(new Font("Verdana", Font.BOLD, 40));	
        okno.add(pole[i]);									// dodaje pola - przyciski
        pole[i].addActionListener(this);
    }
    
    menu.add(items[0]);										// menu
    items[0].addActionListener(NewGame);

    ButtonGroup group = new ButtonGroup();
    menuItem = new JRadioButtonMenuItem("£atwy");
    menuItem.addActionListener(NewGameL);
    group.add(menuItem);
    submenu.add(menuItem);

    menuItem = new JRadioButtonMenuItem("Œredni");
    menuItem.addActionListener(NewGameS);
    group.add(menuItem);
    submenu.add(menuItem);

    menuItem = new JRadioButtonMenuItem("Trudny");
    menuItem.addActionListener(NewGameT);
    menuItem.setSelected(true);
    group.add(menuItem);
    submenu.add(menuItem);
    menu.add(submenu);
    
    menu.addSeparator();
    menu.add(items[1]);
    items[1].addActionListener(Info);
    menu.addSeparator();
    items[2].addActionListener(Quit);
    items[2].setMnemonic(KeyEvent.VK_ESCAPE);
    menu.add(items[2]);

    menuBar.add(menu);    	
   	okno.setJMenuBar(menuBar);
   	
    okno.setVisible(true);
    okno.pack();
   
    }
    
    public void actionPerformed(ActionEvent e) 				
    {
        for(int i = 1; i<= 9; i++){
            if(e.getSource() == pole[i]){
            	pole[i].setText("X");						// zapisuje ruch gracza
                pole[i].setEnabled(false);
            }
        }
        count++; 
        checkWin();
        if(win!=true){										// ruch po stronie komputera
            if(level==1){
        	RandomMove(); count++; checkWin();				// poziom ³atwy
        	}
            else if(level==2){
        	RandomMove(); count++; level=3;					// poziom sredni
        	}
            else if(level==3)
        	AI();											// poziom trudny
        }
    }
    
    public void checkWin()						// sprawdza zwyciesce
    { 
        for(int i=0; i<=7; i++){
            if( pole[winCombinations[i][0]].getText().equals(pole[winCombinations[i][1]].getText()) && 
                pole[winCombinations[i][1]].getText().equals(pole[winCombinations[i][2]].getText()) && 
                !pole[winCombinations[i][0]].getText().equals("")) {
                win = true;
            }
        }
        
        if(count % 2 != 0)
            letter = "X";
        else
            letter = "O";
        
        if(win == true){
        	if (letter=="O"){
        		JOptionPane.showMessageDialog(null, "Przegra³eœ");
        		for(int i = 1; i<=9; i++){
        			if(pole[i].getText().equals(""))
        				pole[i].setEnabled(false);
        		}
        	}
        	if (letter=="X"){
        		JOptionPane.showMessageDialog(null, "Pokona³eœ komputer, brawo !");
        		for(int i = 1; i<=9; i++){
        			if(pole[i].getText().equals(""))
        				pole[i].setEnabled(false);
        		}
        	}
        } 
        else if(count >= 9 && win == false){
            JOptionPane.showMessageDialog(null, "Gra zakonczy³a siê remisem");
    		win=true;
            //System.exit(0);
        }
    }
    
    public void AI()										// algorytm gry
    {
        count++;
        if(pole[1].getText().equals("O") && pole[2].getText().equals("O") && pole[3].getText().equals("")){        
            pole[3].setText("O");
            pole[3].setEnabled(false);
        } 
        else if(pole[4].getText().equals("O") && pole[5].getText().equals("O") && pole[6].getText().equals("")){
            pole[6].setText("O");
            pole[6].setEnabled(false);
        } else if(pole[7].getText().equals("O") && pole[8].getText().equals("O") && pole[9].getText().equals("")){
            pole[9].setText("O");
            pole[9].setEnabled(false);                
        } 
        
        else if(pole[2].getText().equals("O") && pole[3].getText().equals("O") && pole[1].getText().equals("")){
            pole[1].setText("O");
            pole[1].setEnabled(false);                
        } else if(pole[5].getText().equals("O") && pole[6].getText().equals("O") && pole[4].getText().equals("")){
            pole[4].setText("O");
            pole[4].setEnabled(false);                
        } else if(pole[8].getText().equals("O") && pole[9].getText().equals("O") && pole[7].getText().equals("")){
            pole[7].setText("O");
            pole[7].setEnabled(false);                
        }
        
        else if(pole[1].getText().equals("O") && pole[3].getText().equals("O") && pole[2].getText().equals("")){
            pole[2].setText("O");
            pole[2].setEnabled(false);                
        } else if(pole[4].getText().equals("O") && pole[6].getText().equals("O") && pole[5].getText().equals("")){
            pole[5].setText("O");
            pole[5].setEnabled(false);                
        } else if(pole[7].getText().equals("O") && pole[9].getText().equals("O") && pole[8].getText().equals("")){
            pole[8].setText("O");
            pole[8].setEnabled(false);                
        }
        
        else if(pole[1].getText().equals("O") && pole[4].getText().equals("O") && pole[7].getText().equals("")){
            pole[7].setText("O");
            pole[7].setEnabled(false);                
        } else if(pole[2].getText().equals("O") && pole[5].getText().equals("O") && pole[8].getText().equals("")){
            pole[4].setText("O");
            pole[4].setEnabled(false);                
        } else if(pole[3].getText().equals("O") && pole[6].getText().equals("O") && pole[9].getText().equals("")){
            pole[9].setText("O");
            pole[9].setEnabled(false);                
        }
        
        else if(pole[4].getText().equals("O") && pole[7].getText().equals("O") && pole[1].getText().equals("")){
            pole[1].setText("O");
            pole[1].setEnabled(false);                
        } else if(pole[5].getText().equals("O") && pole[8].getText().equals("O") && pole[2].getText().equals("")){
            pole[2].setText("O");
            pole[2].setEnabled(false);                
        } else if(pole[6].getText().equals("O") && pole[9].getText().equals("O") && pole[3].getText().equals("")){
            pole[3].setText("O");
            pole[3].setEnabled(false);                
        }
        
        else if(pole[1].getText().equals("O") && pole[7].getText().equals("O") && pole[4].getText().equals("")){
            pole[4].setText("O");
            pole[4].setEnabled(false);                
        } else if(pole[2].getText().equals("O") && pole[8].getText().equals("O") && pole[5].getText().equals("")){
            pole[5].setText("O");
            pole[5].setEnabled(false);                
        } else if(pole[3].getText().equals("O") && pole[9].getText().equals("O") && pole[6].getText().equals("")){
            pole[6].setText("O");
            pole[6].setEnabled(false);                
        }
        
        else if(pole[1].getText().equals("O") && pole[5].getText().equals("O") && pole[9].getText().equals("")){
            pole[9].setText("O");
            pole[9].setEnabled(false);                
        } else if(pole[5].getText().equals("O") && pole[9].getText().equals("O") && pole[1].getText().equals("")){
            pole[1].setText("O");
            pole[1].setEnabled(false);                
        } else if(pole[1].getText().equals("O") && pole[9].getText().equals("O") && pole[5].getText().equals("")){
            pole[5].setText("O");
            pole[5].setEnabled(false);                
        }
        
        else if(pole[3].getText().equals("O") && pole[5].getText().equals("O") && pole[7].getText().equals("")){
            pole[7].setText("O");
            pole[7].setEnabled(false);                
        } else if(pole[7].getText().equals("O") && pole[5].getText().equals("O") && pole[3].getText().equals("")){
            pole[3].setText("O");
            pole[3].setEnabled(false);                
        } else if(pole[7].getText().equals("O") && pole[3].getText().equals("O") && pole[5].getText().equals("")){
            pole[5].setText("O");
            pole[5].setEnabled(false);                
        }
        
        else if(pole[1].getText().equals("X") && pole[2].getText().equals("X") && pole[3].getText().equals("")){
            pole[3].setText("O");
            pole[3].setEnabled(false);
        } else if(pole[4].getText().equals("X") && pole[5].getText().equals("X") && pole[6].getText().equals("")){
            pole[6].setText("O");
            pole[6].setEnabled(false);                
        } else if(pole[7].getText().equals("X") && pole[8].getText().equals("X") && pole[9].getText().equals("")){
            pole[9].setText("O");
            pole[9].setEnabled(false);                
        } 
        
        else if(pole[2].getText().equals("X") && pole[3].getText().equals("X") && pole[1].getText().equals("")){
            pole[1].setText("O");
            pole[1].setEnabled(false);                
        } else if(pole[5].getText().equals("X") && pole[6].getText().equals("X") && pole[4].getText().equals("")){
            pole[4].setText("O");
            pole[4].setEnabled(false);                
        } else if(pole[8].getText().equals("X") && pole[9].getText().equals("X") && pole[7].getText().equals("")){
            pole[7].setText("O");
            pole[7].setEnabled(false);                
        }
        
        else if(pole[1].getText().equals("X") && pole[3].getText().equals("X") && pole[2].getText().equals("")){
            pole[2].setText("O");
            pole[2].setEnabled(false);                
        } else if(pole[4].getText().equals("X") && pole[6].getText().equals("X") && pole[5].getText().equals("")){
            pole[5].setText("O");
            pole[5].setEnabled(false);                
        } else if(pole[7].getText().equals("X") && pole[9].getText().equals("X") && pole[8].getText().equals("")){
            pole[8].setText("O");
            pole[8].setEnabled(false);                
        }
        
        else if(pole[1].getText().equals("X") && pole[4].getText().equals("X") && pole[7].getText().equals("")){
            pole[7].setText("O");
            pole[7].setEnabled(false);                
        } else if(pole[2].getText().equals("X") && pole[5].getText().equals("X") && pole[8].getText().equals("")){
            pole[8].setText("O");
            pole[8].setEnabled(false);                
        } else if(pole[3].getText().equals("X") && pole[6].getText().equals("X") && pole[9].getText().equals("")){
            pole[9].setText("O");
            pole[9].setEnabled(false);                
        }
        
        else if(pole[4].getText().equals("X") && pole[7].getText().equals("X") && pole[1].getText().equals("")){
            pole[1].setText("O");
            pole[1].setEnabled(false);                
        } else if(pole[5].getText().equals("X") && pole[8].getText().equals("X") && pole[2].getText().equals("")){
            pole[2].setText("O");
            pole[2].setEnabled(false);                
        } else if(pole[6].getText().equals("X") && pole[9].getText().equals("X") && pole[3].getText().equals("")){
            pole[3].setText("O");
            pole[3].setEnabled(false);                
        }
        
        else if(pole[1].getText().equals("X") && pole[7].getText().equals("X") && pole[4].getText().equals("")){
            pole[4].setText("O");
            pole[4].setEnabled(false);                
        } else if(pole[2].getText().equals("X") && pole[8].getText().equals("X") && pole[5].getText().equals("")){
            pole[5].setText("O");
            pole[5].setEnabled(false);                
        } else if(pole[3].getText().equals("X") && pole[9].getText().equals("X") && pole[6].getText().equals("")){
            pole[6].setText("O");
            pole[6].setEnabled(false);                
        }
        
        else if(pole[1].getText().equals("X") && pole[5].getText().equals("X") && pole[9].getText().equals("")){
            pole[9].setText("O");
            pole[9].setEnabled(false);                
        } else if(pole[5].getText().equals("X") && pole[9].getText().equals("X") && pole[1].getText().equals("")){
            pole[1].setText("O");
            pole[1].setEnabled(false);                
        } else if(pole[1].getText().equals("X") && pole[9].getText().equals("X") && pole[5].getText().equals("")){
            pole[5].setText("O");
            pole[5].setEnabled(false);                
        }
        
        else if(pole[3].getText().equals("X") && pole[5].getText().equals("X") && pole[7].getText().equals("")){
            pole[7].setText("O");
            pole[7].setEnabled(false);                
        } else if(pole[7].getText().equals("X") && pole[5].getText().equals("X") && pole[3].getText().equals("")){
            pole[3].setText("O");
            pole[3].setEnabled(false);                
        } else if(pole[7].getText().equals("X") && pole[3].getText().equals("X") && pole[5].getText().equals("")){
            pole[5].setText("O");
            pole[5].setEnabled(false);                
        }
        
        else if(pole[1].getText().equals("X") && pole[5].getText().equals("O") && pole[9].getText().equals("X")) {
            pole[6].setText("O");
            pole[6].setEnabled(false);            
        }    
        
        else if(pole[3].getText().equals("X") && pole[5].getText().equals("O") && pole[7].getText().equals("X")) {
            pole[4].setText("O");
            pole[4].setEnabled(false);            
        }
        
        else if(pole[5].getText().equals("")){
            pole[5].setText("O");
            pole[5].setEnabled(false);                
        }
        
        else if(pole[1].getText().equals("")){
            pole[1].setText("O");
            pole[1].setEnabled(false);                
        }
        else {
            if(count >= 9)
                checkWin();
            else
                RandomMove();
        }
        
        checkWin();

    }
	public void reset()							// czysci pola gry
	{
		for(int i = 1; i<=9; i++){
			pole[i].setText("");
			pole[i].setEnabled(true);
		}
    }
   
    public void RandomMove()					// losowy ruch
    {
        Random x = new Random();
        int y = 1 + x.nextInt(9);
        if(pole[y].getText().equals("O") || pole[y].getText().equals("X") ){
            RandomMove();
        } else {
            pole[y].setText("O");
            pole[y].setEnabled(false);
        }
    }
    
    public static void main(String[] args)
    {
    	try {
    			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());	// ustawia widok okna
    	}
    	catch (Exception e) {					// przechwycenie wyjatku
    		throw new RuntimeException(e);
    	}
    	new kolko_i_krzyzyk();
    }
}