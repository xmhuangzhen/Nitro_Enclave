class myTimer extends Thread {
    myTimer(String s) {
        super(s);
    }

    public void run() {
        while(true) {
            System.out.println("Hello World!");
            try {
                sleep(5000); 
            }catch (InterruptedException e) {
                return;
            }
        }     
   }
}

public class Test3{
    public static void main(String[] args) {
        myTimer t1 = new myTimer("Test3");
        t1.start();
   }
}