import java.io.*;

public class Main{
    public static void main(String args[]) throws Exception{
        //variabili
        BufferedWriter file = null;
        int j = 100;
        Array array;
        long media, inizio;

        //apertura file
        file = new BufferedWriter(new FileWriter("tempi.txt"));
        file.write("Dimensione:\t\tDurata:");
        file.newLine();

        //esperimento
        for(int i = 0; i < 50; i++, j += 100){
            array = new Array(j);
            media = 0;
            for(int k = 0; k < 10; k++){
                array.generateArray();
                inizio = System.nanoTime();
                Ordinamento.mergeSort(array.getArray(), 0, array.getLenght()-1);
                media += System.nanoTime() - inizio;
            }
            media /= 10;
            file.write(j + "\t\t" + media);
            file.newLine();
        }

        //chiusura del file
        file.close();

    }
}