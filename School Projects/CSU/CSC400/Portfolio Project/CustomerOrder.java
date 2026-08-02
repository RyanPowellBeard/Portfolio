import java.util.Scanner;

public class CustomerOrder {

    //Class Variables
    private String lastName;
    private int orderNumber;
    private double orderCost;
    static Scanner sc = new Scanner(System.in);
    static int idCount;

    //Parameterized Constructors
    protected CustomerOrder(String lastName, int orderNumber, double orderCost){
        this.lastName = lastName;
        this.orderNumber = orderNumber;
        this.orderCost = orderCost;
    }

    //Getters
    protected String getLastName(){return lastName;}
    protected int getOrderNumber(){return orderNumber;}
    protected double getOrderCost(){return orderCost;}

    //Setters
    protected void setLastName(String lastName){this.lastName = lastName;}
    protected void setOrderNumber(int orderNumber){this.orderNumber = orderNumber;}
    protected void setOrderCost(double orderCost){this.orderCost = orderCost;}

    //Method for acquiring last name
    protected void assignLastName(){
        try{
            System.out.println("Enter last name: ");
            lastName = sc.nextLine();
        }
        catch(Exception e){
            System.out.println("That is not a valid entry.\nEnter last name: ");
            lastName = sc.nextLine();
        }
    }
    /*
     * Method for acquiring orderNumber
     * Takes no arguments
     * returns no values
     */
    protected void assignOrderNumber(){
        orderNumber = idCount + 1;
        idCount++;
    }

    /*
     * Method for acquiring order amount.
     * takes no arguments
     * returns no values
     */
    protected void assignCost(){
        System.out.print("Enter order cost: $");
        while(!sc.hasNextDouble()){
            System.out.print("Enter a valid price. $");
            sc.next();
        }
        orderCost = sc.nextDouble();
        sc.nextLine();
        System.out.println("\n");
    }
    /*
     * toString() allows for consistency of how objects will be displayed and organized within the queue, and array lists.
     * Precision is set for double as well.
     */
    public String toString() {
        return this.lastName + " - " + this.orderNumber + " - $" + String.format("%.2f", this.orderCost);
    }

}
