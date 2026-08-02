import java.util.LinkedList;
import java.util.Queue;

public class Order {
    //Create new CustomerOrder object
    static CustomerOrder newOrder = new CustomerOrder(null, 0, 0);
    //Declare a queue
    static Queue<CustomerOrder> queue = new LinkedList<>();

    
    /*
     * addOrders() calls on CustomerOrder class
     * to add assign last name, order number, and cost.
     * Using queue.offer to add elements as a collection to queue.
     * Then call Display.updateOrder() to update lists
     */
    public static void addOrders(){
        newOrder.assignLastName();
        newOrder.assignOrderNumber();
        newOrder.assignCost();
        /*
         * Using offer() to add object to queue.
         * offer() returns true if successful and false if unsuccessful
         */
        System.out.println("Order added to queue. [" + queue.offer(new CustomerOrder(newOrder.getLastName(), newOrder.getOrderNumber(), newOrder.getOrderCost())) + "]");

        //update ArrayLists in Display class
        Display.updateOrder();
    }
    /*
	 * poll()removes object from from front of queue.
	 * @return returns object from the queue.
	 * will return null if the queue is empty.
	 */
    public static CustomerOrder getOrder(){
        return queue.poll();
    }
    /*
	 * isEmpty() detects if queue is empty.
	 * @return true if empty
	 */
    public static boolean checkOrderQueue(){
        return queue.isEmpty();
    }
    /*
     *
	 * @returns element from the front of the queue, 
	 * will return null if queue is empty
	 */
    public static CustomerOrder addToArray(){
        return queue.peek();
    }
    /*
     * removeItem() will remove first added object from the end of list
     * @return will return object
     * if queue is empty will throw NoSuchElementException 
     */
    public static CustomerOrder removeItem(){
        return queue.remove();
    }
     /*
      * clearQueue() uses queue.clear() to clear all objects from queue
      */
    public static void clearQueue(){
        queue.clear();
    }
    
}
