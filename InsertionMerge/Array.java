import java.util.*;

public class Array{
    private int[] array;
    Random rand = new Random(9832782);
    public Array(int dim){
        array = new int[dim];
    }
    public void generateArray(){
        for(int i = 0; i < array.length; i++){
            array[i] = rand.nextInt(100000);
        }
    }
    public int[] getArray(){
        return array;
    }
    public int getLenght(){
        return array.length;
    }
}