import java.util.ArrayList;

public class Display<T> {
    //CustomerOrder currentOrder = new CustomerOrder(null, 0, 0);
    /*
     * arrayId to hold the sorted orders in an array by the order number.
     */
    static ArrayList<CustomerOrder> arrayID = new ArrayList<>();
    /*
     * arrayNames to hold the sorted orders in an array by the orders last name
     */
    static ArrayList<CustomerOrder> arrayNames  = new ArrayList<>();

    static CustomerOrder currentOrder = new CustomerOrder(null, 0, 0);

    /*
     * Method to update array lists as orders are entered
     */
    public static void updateOrder(){
        currentOrder = Order.getOrder();
        arrayID.add(currentOrder);
        arrayNames.add(currentOrder);
        /*
         * using isEmpty() on queue to ensure everything has been removed and output 
         * boolean results to console
         */
        System.out.println("Queue is empty. [" + Order.checkOrderQueue() + "]  ");
        
        /*
         * after copying objects to array list, pass them to methods to be sorted
         */
        sortID(arrayID);
        sortName(arrayNames);
        /*
         * print each new entry to console in sorted list
         */
        displayOrders();
    }

    /*
     * Method to call on QuickSort and assign results into appropriate array
     */

    public static void addOrder() {
        /*
        * Using while loop to poll() off queue and copy objects to two Array List
        */
        while(!Order.checkOrderQueue()){
            currentOrder = Order.getOrder();
            //Add object to arrayID
            arrayID.add(currentOrder);
            arrayNames.add(currentOrder);
        }

        /*
         * using isEmpty() on queue to ensure everything has been removed and output 
         * boolean results to console
         */
        System.out.println("Queue is empty. [" + Order.checkOrderQueue() + "]  ");
        
        /*
         * after copying objects to array list, pass them to methods to be sorted
         */
        sortID(arrayID);
        sortName(arrayNames);
    }
    
    /*
     * Method sortID is used to pass arrayID list to Quick Sort to be sorted in 
     * descending order.
     */
    public static void sortID (ArrayList<CustomerOrder> arrayID){
       QuickSort.sortID(arrayID, 0, arrayID.size() - 1);
        
    }
    /*
     * Method sortName is used to pass arrayNames list to Quick Sort to be sorted in 
     * descending order.
     */
    public static void sortName (ArrayList<CustomerOrder> arrayNames){
        QuickSort.sortName(arrayNames, 0, arrayNames.size() - 1);

    }

    /*
     * displayOrders outputs both sorted arrays to console 
     */
    public static void displayOrders(){
        System.out.println("---------------------Sort by Order Number---------------------/n");
        System.out.println(arrayID.toString());

        System.out.println("---------------------Sort by Last Name---------------------/n");
        System.out.println(arrayNames.toString());
    }
}