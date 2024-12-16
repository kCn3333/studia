import java.io.IOException;
import java.io.OutputStream;

public class Szyfrowanie extends OutputStream {
        OutputStream stream_out = null;
 
        Szyfrowanie(OutputStream str_out) { // strumien wyjsciowy
               stream_out = str_out; 
        }
 
 
        @Override
        public void write(int b) throws IOException {
                
        		char znak = (char)b;
                
                //A-Z
                if ((znak >= 65 ) && ( znak <= 90)) {
                        znak -= 65;
                        znak += 3;
                         znak = (char) (znak % 26);
                        znak += 65;
                        stream_out.write(znak);
                }
                //a-z
                else if ((znak >= 97) && (znak <= 122)) {
                        znak -= 97;
                        znak += 3;
                        znak = (char) (znak % 26);  
                        znak += 97;
                        stream_out.write(znak); 
                }
                //0-9
                else if ((znak >= 48) && (znak <= 57)) {
                        znak -= 48;
                        znak += 3;
                        znak = (char) (znak % 10);
                        znak += 48;
                        stream_out.write(znak);
                }
                else 
                        stream_out.write(znak);
        }
}