public class Ordinamento{
    
    private static void merge(int array[], int l, int m, int r){    
        // Find sizes of two subarrays to be merged 
        int n1 = m - l + 1; 
        int n2 = r - m; 
  
        /* Create temp arrays */
        int L[] = new int [n1]; 
        int R[] = new int [n2]; 
  
        /*Copy data to temp arrays*/
        for (int i=0; i<n1; ++i) 
            L[i] = array[l + i]; 
        for (int j=0; j<n2; ++j) 
            R[j] = array[m + 1+ j]; 
  
  
        /* Merge the temp arrays */
  
        // Initial indexes of first and second subarrays 
        int i = 0, j = 0; 
  
        // Initial index of merged subarry array 
        int k = l; 
        while (i < n1 && j < n2) 
        { 
            if (L[i] <= R[j]) 
            { 
                array[k] = L[i]; 
                i++; 
            } 
            else
            { 
                array[k] = R[j]; 
                j++; 
            } 
            k++; 
        } 
  
        /* Copy remaining elements of L[] if any */
        while (i < n1) 
        { 
            array[k] = L[i]; 
            i++; 
            k++; 
        } 
  
        /* Copy remaining elements of R[] if any */
        while (j < n2) 
        { 
            array[k] = R[j]; 
            j++; 
            k++; 
        } 
    } 
  
    // Main function that sorts array[l..r] using 
    // merge() 
    public static void mergeSort(int array[], int l, int r){ 
        if (l < r){ 
            // Find the middle point 
            int m = (l+r)/2; 
  
            // Sort first and second halves 
            mergeSort(array, l, m); 
            mergeSort(array , m+1, r); 
  
            // Merge the sorted halves 
            merge(array, l, m, r); 
        }
    }
    
    public static void insertionSort(int array[]){
        for(int i = 1; i < array.length; i++){
            int tmp = array[i];
            int j = i - 1;
            while((j > -1) && (array[j]>tmp)){
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = tmp;
        }
    }
}