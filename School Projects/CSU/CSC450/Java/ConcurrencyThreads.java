import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ConcurrentModificationException;

public class ConcurrencyThreads extends Thread {

    //A Default Constructor
    public ConcurrencyThreads(){

    }
    
    //int array to hold thread counts set to private to block outside access
    private int[] countUp = new int[21];
    private int[] countDown = new int[21];

    //overide Thread class run method
    @Override
    public void run() {
        try{
            count_up(countUp);
            count_down(countDown);
        }
        //Illeagal Argument Exception will catch illegal therad state and number format exceptions
        catch(IllegalArgumentException e){
            System.out.println("IllegalArgumentException in @override run().");
            e.printStackTrace();
        }
        catch(ConcurrentModificationException e){
            System.out.println("ConcurrentModificationException in @override run()");
            e.printStackTrace();
        }
        catch(Exception e){
            System.out.println("Unexpected Exception in @override run().");
            e.printStackTrace();
        }
        //No resources are being utilized here. No call for finally()
        
    }

    //private method for thread count up to 20 from 0
    private void count_up(int[] count){
        try{
            for (int i = 0; i < 21; i++){
                count[i] = i;
                System.out.println("Count up is: " + count[i]);
            }
        }
        catch(IndexOutOfBoundsException e){
            System.out.println("IndexOutOfBoundsException in count up!");
            e.printStackTrace();
        }
        catch(IllegalArgumentException e){
            System.out.println("IllegalArgumentException in count up!");
            e.printStackTrace();
        }
        catch(Exception e){
            System.out.println("Unexpected Exception in count up!");
            e.printStackTrace();
        }
        //No resources are being utilized here. No call for finally()
    }
    //private method for thread to count down to 0 from 20
    private void count_down(int[] count){
        try{
            for (int i = 20; i >= 0; i--){
                //store results in an integer array
                count[i] = i;
                //print results to counsel
                System.out.println("CountDown is: " + count[i]);
            }
        }
        catch (IndexOutOfBoundsException e){
            System.out.println("IndexOutOfBoundsException in Count Down!");
        }
        catch(IllegalArgumentException e){
            System.out.println("IllegalArgumentException in count down!");
            e.printStackTrace();
        }
        //For unforseen exceptions
        catch(Exception e){
            System.out.println("Unexpected Exception in count down!");
            e.printStackTrace();
        }
        //No resources are being utilized here. No call for finally()
        
    }

    //Write_threads allows for private integer arrays to be passed to write_array method with id numbers
    protected void write_threads(){
        try{
            write_array(countUp, 1);
            write_array(countDown, 2);
            
            //to test our custom exception, we will pass an invalid id number
            write_array(countDown, 0);
        }
        catch(NoSuchMethodError e){
            System.out.println("NoSuchMethodError in write_threads!");
            e.printStackTrace();
        }
        catch(IllegalAccessError e){
            System.out.println("IlleagalAccessError in write_threads!");
            e.printStackTrace();
        }
        //last resort is a catch all
        catch(Exception e){
            System.out.println("Unexpected Exception in write_threads!");
            e.printStackTrace();
        }
        //No resources are being utilized here. No call for finally()
        
    }
    

    /*If we set parameter of filewriter to false, we will clear and write new information to file. True sets file to be appended.
     * This means if file is not found an IOException can be thrown. I went ahead and put a custom exception to handle invalid id, 
     * file not found and ioexception with a catch all to catch unforseen errors.
     */
    //Iterate through integer array and write results to text file
    private void write_array(int[] count, int id){

        //Try-with-Resources replaces try-catch-finally. Allows for auto-close of resources that are within the try-with-resources block
        try(BufferedWriter writeArray = new BufferedWriter(new FileWriter("Results.txt", true));) {
            //If exception is not thrown, file is open correctly
            System.out.println("\nID: " + id + " File is open.\n");

            //check if id matches count up id
            if (id == 1){
                writeArray.write("\n-------------------COUNT UP-------------------\n");
                //write thread arrays to text file
                for (int i = 0; i < 21; i++){
                    writeArray.write("Count is: " + count[i] + "\n");
                }
            }
            //check if id matches count down id
            else if (id == 2){
                writeArray.write("\n-------------------COUNT DOWN-------------------\n");
                //write thread arrays to text file
                for (int i = 20; i >= 0; i--){
                    writeArray.write("Count is: " + count[i] + "\n");
                }
            }
            //if id does not match count up or count down throw invalid id exception
            else {
                //we will throw a custom exception
                throw new InvalidIDException();
            }
        }

        //Custom Exception for user ID
        catch(InvalidIDException e){
            System.out.println("Invalid ID used. InvalidIDException thrown!");
        }
        //catch file not found excpetion
        catch(FileNotFoundException e){
            System.out.println("File not found!");
            e.printStackTrace();
        }
        //catch input output exception
        catch(IOException e){
            System.out.println("IOException has occured in write_array!");
            e.printStackTrace();
        }
        //last resort is a catch all
        catch(Exception e){
            System.out.println("Unexpected exception has occured in write_array@!");
            e.printStackTrace();
        }

        //Since we are using try-with-resources that auto closes. If we make it here the file is closed.
        System.out.println("ID: " + id + " File is closed.");
    }

}
