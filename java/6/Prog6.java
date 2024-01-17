import java.util.Random;

public class Prog6 {

    public static int numThreads;		// liczba watkow


    /* sprawdza czy posortowane */
    public static boolean isSorted(int[] data) {
        for (int i = 0; i < data.length-1; ++i) {
            if (data[i]>data[i+1])
                return false;
        }
        return true;
    }

    /* sortowanie */
    public static int[] sort(int[] data, int numThreads) { 
        int[] temp = mergesort(data, 0, data.length-1, numThreads);
        return temp;
    }

    /* 
     * sortowanie przez scalanie:
     *   sortuje data[firstIndex...lastIndex] uzywajac numThreads watkow
     *   zwraca posortowana tablice 
     */
    private static int[] mergesort(int[] data, 
            int firstIndex, int lastIndex, int numThreads) 
    {
        if (firstIndex > lastIndex) {
            return new int[0];
        }
        else if (firstIndex == lastIndex) {
            return new int[] { data[firstIndex] };
        }
        int midIndex = (firstIndex + lastIndex) / 2;

        int[] temp1 = null;
        Thread otherThread = null;
        ForThread other = null;
        
        /* sortowanie lewej czesci */
        if (numThreads > 1) {
            /* nowy watek */
            other = new ForThread(data, firstIndex, midIndex, numThreads/2);
            otherThread = new Thread(other);
            otherThread.start();
        }
        else {
            /* sortowanie w tym samym watku */
        	//System.out.println("watek... sortuje od " + firstIndex + " do "+ midIndex);
            temp1 = mergesort(data, firstIndex, midIndex, numThreads/2);
        }
        /* sortowanie prawej czesci */
        int[] temp2 = mergesort(data, midIndex+1, lastIndex, numThreads-(numThreads/2));

        if (numThreads > 1) {
        	
            /* czeka na zakonczenie watku */
            try {
                otherThread.join();
                //System.out.println(otherThread.activeCount() + " join()");
            }
            catch (InterruptedException e) {
                System.out.println(" #blad");
            }
            temp1 = other.getResult();
        }
        /* scalanie */
        return merge(temp1, temp2);
    }

    /* scalanie posortowanych czesci */
    private static int[] merge(int[] a1, int[] a2) {
        int[] result = new int[a1.length + a2.length];

        int i1 = 0; 	// index dla a1
        int i2 = 0; 	// index dla a2

        for (int j = 0; j < result.length; ++j) {
            if (i2 >= a2.length) {
                result[j] = a1[i1++];
            }
            else if (i1 >= a1.length) {
                result[j] = a2[i2++];
            }
            else if (a1[i1] <= a2[i2]) {
                result[j] = a1[i1++];
            }
            else {
                result[j] = a2[i2++];
            }
        }
        return result;
    }

    /* ... dla kolejnych watkow */

    private static class ForThread implements Runnable {

        private int[] data;
        private int firstIndex;
        private int lastIndex;
        int numThreads;
        private int[] result;

        public ForThread(int[] d, int first, int last, int nThreads) 
        {
            data = d;
            firstIndex = first;
            lastIndex = last;
            numThreads = nThreads;
        }

        public void run() {
        	//System.out.println(" nowy watek... sortuje od " + firstIndex + " do "+ lastIndex);
         	result = mergesort(data, firstIndex, lastIndex, numThreads);
        }

        public int[] getResult() { return result; }
    }
    
    
    public static void main(String[] args) {
    	
        numThreads = 2; 			// liczba watkow
        int n = 10000000;			// ile elementow do posortowania
        int seed = n;				// zakres liczb

        int[] tab1 = new int[n];
        int[] tab2 = new int[n];
        Random randGen = new Random((long) seed);
        for (int i = 0; i < tab1.length; ++i) {
            tab1[i] = new Integer(randGen.nextInt(seed));
            tab2[i] = tab1[i];
        }
        
        System.out.println("> sortowanie " + n + " liczb z zakresu 0-" + seed + " ...\n" );
        System.out.println("--- sortowanie w " + numThreads + " watkach ---");
               
        long startTime = System.currentTimeMillis();
        tab1 = sort(tab1, numThreads);
        long endTime = System.currentTimeMillis();

        if (isSorted(tab1)) {
            System.out.println("> OK");
        }
        else {
            System.out.println("#blad sortowania");
        }
        System.out.println("---------------------------------\n" +
        		"-zakonczono w czasie " + ((double) (endTime - startTime) / 1000) + " sekund");
        
        
        System.out.println("\n--- sortowanie w jednym watku ---");
        startTime = System.currentTimeMillis();
        tab2 = sort(tab2, 1);
        endTime = System.currentTimeMillis();

        if (isSorted(tab1)) {
            System.out.println("> OK");
        }
        else {
            System.out.println("#blad");
        }
        System.out.println("---------------------------------\n" +
        		"-zakonczono w czasie " + ((double) (endTime - startTime) / 1000) + " sekund");
    }

}