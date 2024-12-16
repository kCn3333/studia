import java.io.IOException;
import java.io.InputStream;


public class Deszyfrowanie extends InputStream {
	InputStream stream_in = null;
    
    Deszyfrowanie(InputStream str_in) { // strumien wejsciowy
            stream_in = str_in; 
    }

	@Override
	public int read() throws IOException {

				int znak = stream_in.read();
				
				//A-Z
                if ((znak >= 65 ) && ( znak <= 90)) {
                        znak -= 65;
                        znak -= 3;
 						if(znak<=0) znak+=26;
                        znak = (znak % 26);
                        znak += 65;
                        return znak;
                }
                //a-z
                else if ((znak >= 97) && (znak <= 122)) {
                        znak -= 97;
                        znak -= 3;
                        if(znak<=0) znak+=26;
						znak = (znak % 26);  
						znak += 97;
                        return znak; 
                }
                //0-9
                else if ((znak >= 48) && (znak <= 57)) {
                        znak -= 48;
                        znak -= 3;
                        if(znak<0) znak+=10;
						znak = (znak % 10);
						znak += 48;
                        return znak;
                }
                else 
                        return znak;
        }



}