import java.util.ArrayList;
import java.util.Collections;

/*
 * There are two quick sort algorithms in this file
 * One for accessing Last Names
 * and one for accessing Order Number
 */
public class QuickSort {
      /*
     * partition takes the last element as pivot
     * and places the pivot element at its correct position
     * in the sorted array, then places all smaller than pivot
     * objects to the right of pivot, and all the greater objects
     * to the left of pivot.
     * This allows the object list to be sorted in descending order by the last name
     */
    public static int partitionName(ArrayList<CustomerOrder> arrayList, int low, int high){
        
        String pivot = arrayList.get(high).getLastName();//Set pivot to arrayList size - 1 (high)
        int j = (low - 1); //For index of smaller objects
        for (int i = low; i < high; i++){
            String object = arrayList.get(i).getLastName();
            if(object.compareTo(pivot) >= 0){
                j++;
                //swap
                Collections.swap(arrayList, i, j);
            }
            else {continue;}
        }
        //swap arrayList[j + 1] and array[high]
        Collections.swap(arrayList, high, j+1);
        return j + 1;
    }    
     /*
     * Main sort method
     */
    public static void sortName(ArrayList<CustomerOrder> arrayList, int low, int high){
        if (low < high){
            //arrayList[partitionIndex] at the correct position
            int partitionIndex = partitionName(arrayList, low, high);
            //Using recursive calls to sort object before and after the partition
            sortName(arrayList, low, partitionIndex - 1);
            sortName(arrayList, partitionIndex + 1, high);

        }
    }

     /*
     * partition takes the last element as pivot
     * and places the pivot element at its correct position
     * in the sorted array, then places all smaller than pivot
     * objects to the right of pivot, and all the greater objects
     * to the left of pivot.
     * This allows the object list to be sorted in descending order by the order number
     */
    public static int partitionID(ArrayList<CustomerOrder> arrayList, int low, int high){
        
        int pivot = arrayList.get(high).getOrderNumber();//Set pivot to arrayList size - 1 (high)
        int j = (low - 1); //For index of smaller objects
        for (int i = low; i < high; i++){
            int object = arrayList.get(i).getOrderNumber();
            if(object >= pivot){
                j++;
                //swap
                Collections.swap(arrayList, i, j);//swap i j
            }
            else {continue;}
        }
        //swap arrayList[j + 1] and array[high]
        Collections.swap(arrayList, high, j+1);
        return j + 1;
    }    
     /*
     * Main sort method
     */
    public static void sortID(ArrayList<CustomerOrder> arrayList, int low, int high){
        if (low < high){
            //arrayList[partitionIndex] at the correct position
            int partitionIndex = partitionID(arrayList, low, high);
            //Using recursive calls to sort object before and after the partition
            sortID(arrayList, low, partitionIndex - 1);
            sortID(arrayList, partitionIndex + 1, high);

        }
    }
}
