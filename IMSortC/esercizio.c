#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int *array, int n) { 
    int i, key, j; 
    for (j = 1; j < n; j++) { 
        key = array[j]; 
        i = j - 1; 
        while (i >= 0 && array[i] > key) { 
            array[i + 1] = array[i]; 
            i = i - 1; 
        } 
        array[i + 1] = key; 
    } 
}
void insertionSortIbrido(int *array, int inizio, int fine) { 
    int i, key, j; 
    for (j = inizio; j < fine; j++) { 
        key = array[j]; 
        i = j - 1; 
        while (i >= inizio && array[i] > key) { 
            array[i + 1] = array[i]; 
            i = i - 1; 
        } 
        array[i + 1] = key; 
    } 
}
void stampaArray(int *array, int dim){
    int i;
    for(i = 0; i < dim; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

double eseguiOrdinamentoIS(int dim){
    int* array = malloc(sizeof(int)*dim), i;
    double tempo;
    clock_t inizio;
    for(i = 0; i < dim; i++){
        array[i] = rand()%1000;
    }
    inizio = clock();
    insertionSort(array, dim);
    tempo = (double) (clock() - inizio);
    free(array);
    return tempo;
}

void merge(int array[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int a[n1], b[n2];
    int i, j, k;
    for(i = 0 ; i < n1; i++){
        a[i] = array[p + i];
    }
    for(j = 0; j < n2; j++){
        b[j] = array[q + 1 +j];
    }

    i = j = 0;

    for(k = p; k <= r; k++){
        if(i < n1){
            if(a[i] <= b[j]||j==n2){
                array[k] = a[i];
                i++;
            }
            else{
                array[k] = b[j];
                j++;
            }
        }
        else{
            array[k] = b[j];
            k++;
        }
    }
}

void mergeSort(int array[], int p, int r) {
  int q;
  if (p < r) {
    q = (p+r)/2;
    mergeSort(array, p, q);
    mergeSort(array, q + 1, r);
    merge(array, p, q, r);
  }
}

double eseguiOrdinamentoMS(int dim){
    int* array = malloc(sizeof(int)*dim), i;
    double tempo;
    clock_t inizio;
    for(i = 0; i < dim; i++){
        array[i] = rand()%1000;
    }
    inizio = clock();
    mergeSort(array, 0, dim-1);
    tempo = (double) (clock() - inizio);
    free(array);
    return tempo;
}

void eseguiOrdinamentoIbrido(int array[], int p, int r){
    int q;
    if(p < r){
        if(r - p >= 50){
            q = (r+p)/2;
            eseguiOrdinamentoIbrido(array, p, q);
            eseguiOrdinamentoIbrido(array, q+1, r);
            merge(array, p, q, r);
        }
        else{
            insertionSortIbrido(array, p, r);
        }
    }
}

int main(int argc, char** argv){

    int i, j;
    clock_t inizio;
    double media, tempo;
    FILE* fp;
    
    fp = fopen("tempiInsertion.txt", "w");
    fprintf(fp, "lunghezza:\t\tdurata:\n");
    printf("Insertion \n");
    for(i = 1;  i <= 1000; i += 1){
        media = 0;
        for(j = 0; j < 10; j++){
            media += eseguiOrdinamentoIS(i);
        }
        media = media /10;
        fprintf(fp, "%d\t\t%f\n",i, media);
    }

    fclose(fp);

    fp = fopen("tempiMerge.txt", "w");

    printf("Merge\n");
    for(i = 1;  i <= 1000; i += 1){
        media = 0;
        for(j = 0; j < 10; j++){
            media += eseguiOrdinamentoMS(i);
        }
        media = media /10;
        fprintf(fp, "%d\t\t%f\n", i, media);
    }

    fclose(fp);

    fp = fopen("tempiIbrido.txt", "w");

    printf("ibrido\n");
    int k;

    for(i = 1;  i <= 1000; i += 1){
        int* array = malloc(sizeof(int)*i);
        for(k = 0; k < i; k++){
            array[k] = rand()%1000;
        }
        media = 0;
        for(j = 0; j < 10; j++){
            inizio = clock();
            eseguiOrdinamentoIbrido(array, 0, i-1);
            media += (double)(clock() - inizio);
        }
        media = media /10;
        fprintf(fp, "%d\t\t%f\n", i, media);
        free(array);
    }

    fclose(fp);

    return 0;
}