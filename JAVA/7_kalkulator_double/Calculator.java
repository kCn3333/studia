import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.UIManager;

public class Calculator extends JFrame implements ActionListener {

  private static final long serialVersionUID = 1L;

  private static final Font czcionka = new Font("Verdana", Font.PLAIN, 20);
  private static final Font czcionka2 = new Font("Times New Roman", Font.PLAIN, 20);
  private JTextField display = new JTextField("0", 20);

  private String cyfry = "1234567890.C";
  private String znaki = "+-*/=";
  private double x = 0.0;
  private double result = 0;
  private String lastOperator = "=";
  private String operator = "=";
  private boolean calculating = true;

  /* ----- ----- ----- konstruktor ----- ----- ----- */
  public Calculator() {

    JPanel panel = new JPanel();
    // setLayout(new BorderLayout());

    display.setEditable(false); // parametry wyswietlacza
    display.setFont(czcionka);
    display.setHorizontalAlignment(JTextField.RIGHT);

    JPanel cyfryPanel = new JPanel(); // panel z cyframi
    cyfryPanel.setLayout(new GridLayout(5, 3, 3, 3));

    for (int i = 0; i < cyfry.length(); i++) {
      JButton b = new JButton(cyfry.substring(i, i + 1));
      b.setFont(czcionka2);
      b.setForeground(Color.blue);
      cyfryPanel.add(b);
      if (cyfry.substring(i, i + 1).equals("C")) {
        b.addActionListener(new ClearListener());
        b.setForeground(Color.red);
      } else
        b.addActionListener(this);
    }

    JPanel znakiPanel = new JPanel(); // panel z znakami
    znakiPanel.setLayout(new GridLayout(5, 1, 2, 2));

    for (int i = 0; i < znaki.length(); i++) {
      JButton b = new JButton(znaki.substring(i, i + 1));
      b.setFont(czcionka);
      b.setForeground(Color.red);
      znakiPanel.add(b);
      b.addActionListener(this);
    }

    panel.setLayout(new BorderLayout(5, 5));
    panel.add(display, BorderLayout.NORTH);
    panel.add(cyfryPanel, BorderLayout.CENTER);
    panel.add(znakiPanel, BorderLayout.EAST);
    panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

    this.setContentPane(panel);
    this.setLocationRelativeTo(null);
    this.setTitle("Kalkulator");
    this.setSize(300, 300);
    this.setResizable(false);
    this.addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent e) {
        System.exit(0);
      }
    });
  }

  /* ----- ----- ----- Action Listener ----- ----- ----- */
  public void actionPerformed(ActionEvent evt) {
    String cmd = evt.getActionCommand();

    if ('0' <= cmd.charAt(0) && cmd.charAt(0) <= '9' || cmd.equals(".")) {
      if (calculating)
        display.setText(cmd); // wyswietla 1-sza cyfre
      else
        display.setText(display.getText() + cmd); // kolejne cyfry
      calculating = false;
    } else {
      if (calculating) { // liczby ujemne
        if (cmd.equals("-")) {
          display.setText(cmd);
          calculating = false;
        } else { // 'dzialanie wielokrotne'
          operator = cmd;
          if (operator.equals("=")) {
            operator = lastOperator;
            calculate(x);
          }
        }
      } else {
        try {
          x = Double.parseDouble(display.getText()); // wczytuje cala liczbe
        } catch (NumberFormatException e) { // blad skladni
          x = 0.0;
        }
        if (!operator.equals("=")) // zapamietuje ostatni operator rozny od '='
          lastOperator = operator;
        calculate(x);
        operator = cmd;
        calculating = true;
      }
    }
  }

  /* ----- ----- ----- kalkulator ----- ----- ----- */
  private void calculate(double n) {
    if (operator.equals("+"))
      result += n;
    else if (operator.equals("-"))
      result -= n;
    else if (operator.equals("*"))
      result *= n;
    else if (operator.equals("/")) {
      if (n == 0.0) {
        display.setText("nie dzielimy przez zero");
        return;
      } else
        result /= n;
    } else if (operator.equals("=") && lastOperator.equals("="))
      result = n;

    if (result == -0)
      result = 0.0; // problem -0.0
    display.setText("" + result);
  }

  /* ----- ----- ----- czyszczenie ----- ----- ----- */
  class ClearListener implements ActionListener {
    public void actionPerformed(ActionEvent e) {
      clear();
    }
  }

  private void clear() {
    calculating = true;
    display.setText("0");
    operator = "=";
    lastOperator = "=";
    result = 0.0;
    x = 0.0;
  }

  public static void main(String[] args) {
    // wyglad systemowy

    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    } catch (Exception unused) {
      ;
    }

    Calculator window = new Calculator();
    window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    window.setVisible(true);

  }
}
