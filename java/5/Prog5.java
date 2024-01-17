import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class Prog5 {
        public static void main(String [] args) {
                FileInputStream file_in = null; 	// czytanie z pliku
                OutputStream stream_out = null;
                
                //FileOutputStream file_out = null; // pisanie do pliku
                //InputStream stream_in = null;
 
                // otwieranie pliku do czytania
                try {
                    file_in = new FileInputStream("dane.txt");
                } catch (FileNotFoundException e) {
                    System.out.println("Nie znaleziono pliku dane.txt");
                    System.exit(1);
                }
                // otwieranie pliku do pisania
                try {
                	stream_out = new FileOutputStream("wynik.txt");
                } catch (FileNotFoundException e) {
                    System.out.println("Nie znaleziono pliku wyniki.txt");
                    System.exit(2);
                }
 
                Szyfrowanie szyfr = new Szyfrowanie(stream_out);
                //Szyfrowanie szyfr = new Szyfrowanie(System.out);
                
                //Deszyfrowanie deszyfr = new Deszyfrowanie(file_in);
                
                // odczyt bajtow z pliku 
                int b = 0;
                try {
                         do { 
                                b = file_in.read();
								//b = deszyfr.read();
                                System.out.println("Przeczytalem: " + (char)b);
							    szyfr.write(b); 
                        } while(b != -1); // -1 gdy koniec pliku
                         
                } catch (IOException e) {
                        System.out.println("Blad odczytu...");
                        System.exit(3); 
                }
 
                // zamykanie plikow
                try {
                        file_in.close();
                } catch (IOException e) {
                        e.printStackTrace();
                } 
                try {
                		stream_out.close();
                } catch (IOException e) {
                        e.printStackTrace();
                } 
        }
}