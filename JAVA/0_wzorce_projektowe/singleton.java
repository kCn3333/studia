public class Sigleton {
	  
	public static Singleton getInstance() {
			if (_theInstance == null) {
			synchronized (Singleton.class) {
			if (_theInstance == null) {
			  _theInstance = new Singleton();
			}
			}
			}
			return _theInstance;
		
}