import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        /*
         * Main switch case for navigating order system
         */
        try{
            boolean j = false;
            while(!j){
                String switchCase;
            
                System.out.println("\n----------Order List----------");
                System.out.println("Enter A to add orders.\nEnter R to First entered order.");
                System.out.println("Enter C to copy queue to arrays and sort.\nEnter D to display orders.");
                System.out.println("Enter Z to clear queue.\nEnter E to exit.");
                System.out.println("------------------------------\n");
                switchCase = sc.nextLine();

                switch(switchCase){
                    case "A":
                    case "a": {
                        /*
                         * calls Order.addOrders() create object collections for queue
                         */
                        Order.addOrders();
                        break; //breaks out of case and returns to while loop parameters
                    }
                    case "R":
                    case "r": {
                        /*
                         * Since Order.removeItem will throw NoSuchElementException if 
                         * queue is empty, use if statement to only call if queue is not
                         * empty
                         */
                        if(!Order.checkOrderQueue()){
                            System.out.println(Order.removeItem() + " removed from queue.");
                            break; //breaks out of case and returns to while loop parameters
                        }
                        else{
                            System.out.println("Queue is empty!");
                            break; //breaks out of case and returns to while loop parameters
                        }
                    }
                    case "C":
                    case "c": {
                        /*
                         * would be used to ensure all objects are copied out of queue into 
                         * array lists. Will inform if queue is empty.
                         */
                        Display.addOrder();
                        break; //breaks out of case and returns to while loop parameters
                    }
                    case "D": 
                    case "d": {
                        /*
                         * Used to call on Display.displayOrders() to output both array list of 
                         * sorted objects
                         */
                        Display.displayOrders();
                        break; //breaks out of case and returns to while loop parameters
                    }
                    case "Z":
                    case "z": {
                        /*
                         * Using clear() to clear all items from queue
                         */
                        Order.clearQueue();
                        /*
                         * using isEmpty() on queue to ensure everything has been removed and output 
                         * boolean results to console
                         */
                        System.out.println("Queue is empty. [" + Order.checkOrderQueue() + "]  ");
                        break; //breaks out of case and returns to while loop parameters
                    }
                    case "E":
                    case "e": {
                        j = true;
                        break; //breaks out of case and returns to while loop parameters
                    }
                    //Default case:
                    default: {
                        System.out.println("Invalid option.");
                    }

                }
                
            }
            //close scanner
            sc.close();
        }
        catch (Exception e){
            System.out.println("Exception Thrown in Main Switch");
            //e.printStackTrace(); //For Troubleshooting Only
        } 
    }
}
