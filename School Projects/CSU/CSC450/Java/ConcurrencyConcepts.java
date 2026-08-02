
public class ConcurrencyConcepts{

    public static void main(String[] args){
        try{
            //create object of ConcurrencyThread type
            ConcurrencyThreads countThread = new ConcurrencyThreads();

            //call on our override run() method to start sub-threads. We can use start() or call on run() directly to achieve this task.
            countThread.start();

            //join threads to pause main thread until sub-threads finish running
            countThread.join();

            //Call on methods to write results to file
            countThread.write_threads();
            
        }

        //IlllegalAccessError occures when an application trys to invoke a method that is inaccessible
        catch (IllegalAccessError e){
            System.out.println("IllegalAccessError in main()!");
            e.printStackTrace();
        }

        //If an exception is thrown in the ConcurrencyThreads class we will have an exception in the main thread. we need to handel this here.
        catch (InterruptedException e) {
            System.out.println("InterruptedException thrown while joining threads.");
            e.printStackTrace();
        }
        //Catch unforseen exceptions
        catch (Exception e){
            System.out.println("An unexpected error has occured in main().");
            e.printStackTrace();
        }
    }

}
