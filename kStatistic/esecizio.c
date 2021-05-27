#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct{
    int heapsize;
    int maxSize;
    int *array;
}Heap;

void scambia(int* a, int* b){
    int tmp;
    tmp = *b;
    *b = *a;
    *a = tmp;
}

int randPartition(int array[], int p, int r){
    int s = p + rand()%(r + 1 - p);
    int x, i, j;
    x = array[s];
    i = p - 1;
    scambia(&array[s], &array[r]);
    for(j = p; j < r; j++){
        if(array[j] <= x){
            i++;
            scambia(&array[i], &array[j]);
        }
    }
    scambia(&array[i+1], &array[r]);
    return i + 1;
    
}

void randomizeQuicksort(int array[], int p, int r){
    int q;
    if(p < r){
        q = randPartition(array, p, r);
        randomizeQuicksort(array, p, q-1);
        randomizeQuicksort(array, q+1, r);
    }
}

int kPartiton(int array[], int p, int r, int k){
    int pivot;
    if(p < r){
        pivot = randPartition(array, p, r);
        if(pivot == k){
            return array[pivot];
        }
        else if(pivot < k){
            return kPartiton(array, pivot, r, k);
        }
        else{
            return kPartiton(array, p, pivot - 1, k);
        }
    }

}

int left(int i){
    return 2*i+1;
}
int right(int i){
    return 2*i+2;
}
int parent(int i){
    return (int)floor((i-1)/2);
}


void minHeapify(Heap *heap, int i){
    int l = left(i), r = right(i), min = i;

    if(l < heap -> heapsize && heap -> array[l] <= heap -> array[i]){
        min = l;
    }
    if(r < heap -> heapsize && heap -> array[r] <= heap -> array[min]){
        min = r;
    }
    if(min != i){
        scambia(&(heap -> array[min]), &(heap -> array[i]));
        minHeapify(heap, min);
    }
}

void buildMinHeap(Heap *heap){
    int i;
    for(i = (int)floor((heap -> heapsize)/2 - 1); i >= 0; i--){
        minHeapify(heap, i);
    }
}

void maxHeapify(Heap *heap, int i){
    int l = left(i), r = right(i), max = i;
    if(l < heap -> heapsize && heap -> array[l] >= heap -> array[i]){
        max = l;
    }
    if(r < heap -> heapsize && heap -> array[r] >= heap -> array[max]){
        max = r;
    }
    if(max != i){
        scambia(&(heap -> array[i]), &(heap -> array[max]));
        maxHeapify(heap, max);
    }
}


void buildMaxHeap(Heap *heap){
    int i;
    for(i = (int)floor(heap -> heapsize/2 - 1); i >= 0; i--){
        maxHeapify(heap, i);
    }
}


int extractMin(Heap *heap){
    int min;
    if((heap -> heapsize) < 0){
        return -1;
    }
    min = heap -> array[0];
    heap -> array[0] = heap -> array[(heap -> heapsize) - 1];
    (heap -> heapsize)--;
    minHeapify(heap, 0);
    return min;
}

void generaArray(int* array, int dim){
    int i;
    for(i = 0; i < dim; i++){
        *(array + i) = rand()%5000;
    }
}

void decreaseKey(Heap *heap, int i, int priority){
    if(priority > heap -> array[i]){
        return;
    }
    heap -> array[i] = priority;
    maxHeapify(heap, 0);
    while(i > 0 && heap -> array[parent(i)] > heap -> array[i]){
        scambia(&(heap -> array[i]), &(heap -> array[parent(i)]));
        i = parent(i);
        i--;
    }
}

int kMaxHeap(Heap *heap, int k){
    Heap *b = malloc(sizeof(Heap));
    b -> array = malloc(sizeof(int) * k);
    b -> heapsize = k;
    int i, ritorno;

    for(i = 0; i < k; i++){
        b -> array[i] = heap -> array[i];
    }

    buildMaxHeap(b);

    for(i = k; i < heap -> heapsize; i++){
        if(heap -> array[i] < b -> array[0]){
           decreaseKey(b, 0, heap -> array[i]);
        }
    }
    ritorno = b -> array[0];
    free(b);
    return ritorno;
}

int kN(int dim){
    int k, low;
    low = 0.5 * dim;
    k = low + rand()%(dim -low);
    return k;
}

int klogN(int dim){
    double l = log((double)dim);
    int low = (int)l * 0.5;
    int high = (int)l * 50;
    int k = low + rand()%(high - low);
    return k;  
}

int kMinHeap(Heap *heap, int k){
    int i;
    buildMinHeap(heap);
    for(i = 1; i < k; i++){
        extractMin(heap);
    }
    return extractMin(heap);
}

int main(int argc, char** argv){

    FILE* f;
    int dim, prove, k, *array;
    double media;
    clock_t inizio;
/*    
///////////////////////PRIMO ALGORITMO/////////////////////////////
    f = fopen("tempiQS.txt", "w");
    
    //k costante
    k = 50;

    //esperimento
    for(dim = 100; dim < 5000; dim += 100){
        media = 0;
        for(prove = 0; prove < 10; prove++){
            array = malloc(sizeof(int) * dim);
            generaArray(array, dim);
            inizio = clock();
            randomizeQuicksort(array, 0, dim - 1);
            media += (double) clock() - inizio;
            free(array); 
        }
        media /= prove;
        fprintf(f, "%d\t%f\n", dim, media);
    }

    fprintf(f, "\n");

    //k crescente linearmente
    //esperimento
    for(dim = 100; dim < 5000; dim += 100){
        k = kN(dim);
        media = 0;
        for(prove = 0; prove < 10; prove++){
            array = malloc(sizeof(int) * dim);
            generaArray(array, dim);
            inizio = clock();
            randomizeQuicksort(array, 0, dim - 1);
            media += (double) clock() - inizio; 
            free(array);
        }
        media /= prove;
        fprintf(f, "%d\t%f\n", dim, media);
    }

    fprintf(f, "\n");

    //k crescente logaritmicamente
    //esperimento

    for(dim = 100; dim < 5000; dim += 100){
        k = klogN(dim);
        media = 0;
        for(prove = 0; prove < 10; prove++){
            array = malloc(sizeof(int) * dim);
            generaArray(array, dim);
            inizio = clock();
            randomizeQuicksort(array, 0, dim - 1);
            media += (double) clock() - inizio; 
            free(array);
        }
        media /= prove;
        fprintf(f, "%d\t%f\n", dim, media);
    }

    
    fclose(f);

//////////////////////////////////////////////////////////////////

//////////////SECONDO ALGORITMO///////////////////////////////////

    f = fopen("tempiPartition.txt", "w");

    //k costante
    k = 20;

    //esperimento
    for(dim = 100; dim < 5000; dim += 100){
        media = 0;
        for(prove = 0; prove < 10; prove++){
            array = malloc(sizeof(int) * dim);
            generaArray(array, dim);
            inizio = clock();
            kPartiton(array, 0, dim - 1, k);
            media += (double) clock() - inizio;
            free(array);
        }
        media /= prove;
        fprintf(f, "%d\t%f\n", dim, media);
    }

    fprintf(f, "\n");

    //k crescente linearmente
    //esperimento
    for(dim = 100; dim < 5000; dim += 100){
        k = kN(dim);
        media = 0;
        for(prove = 0; prove < 10; prove++){
            array = malloc(sizeof(int) * dim);
            generaArray(array, dim);
            inizio = clock();
            kPartiton(array, 0, dim - 1, k);
            media += (double) clock() - inizio;
            free(array);
        }
        media /= prove;
        fprintf(f, "%d\t%f\n", dim, media);
    }

    fprintf(f, "\n");

    //k crescente logaritmicamente
    //esperimento
    for(dim = 100; dim < 5000; dim += 100){
        k = klogN(dim);
        media = 0;
        for(prove = 0; prove < 10; prove++){
            array = malloc(sizeof(int) * dim);
            generaArray(array, dim);
            inizio = clock();
            kPartiton(array, 0, dim - 1, k);
            media += (double) clock() - inizio;
            free(array);
        }
        media /= prove;
        fprintf(f, "%d\t%f\n", dim, media);
    }

    fclose(f);
    
//////////////////////////////////////////////////////////////////

////////////TERZO ALGORITMO/////////////////////////////////////

    int i;
    Heap *heap = malloc(sizeof(Heap));
    f = fopen("tempiMinHeap.txt", "w");
    
    //k costante

    k = 50;

    //esperimento
    for(dim = 100; dim < 5000; dim += 100){
        media = 0;
        for(prove = 0; prove < 10; prove++){
            heap -> array = malloc(sizeof(int) * dim);
            generaArray(heap -> array, dim);
            inizio = clock();
            heap -> heapsize = heap -> maxSize = dim;
            kMinHeap(heap, k);
            media = (double) clock() - inizio;
            free(heap -> array);
        }
        media /= prove;
        fprintf(f, "%d\t%f\n", dim, media);
    }

    fprintf(f, "\n");
    
    //k cresc lin
    //esperimento
    for(dim = 100; dim < 5000; dim += 100){
        k = kN(dim);
        media = 0;
        for(prove = 0; prove < 10; prove++){
            heap -> array = malloc(sizeof(int) * dim);
            heap -> heapsize = heap -> maxSize = dim;
            generaArray(heap -> array, dim);
            inizio = clock();
            kMinHeap(heap, k);
            media = (double) clock() - inizio;
            free(heap -> array);
        }
        media /= prove;
        fprintf(f, "%d\t%f\n", dim, media);
    }

    fprintf(f, "\n");

    for(dim = 100; dim < 5000; dim += 100){
        k = klogN(dim);
        media = 0;
        for(prove = 0; prove < 10; prove++){
            heap -> array = malloc(sizeof(int) * dim);
            heap -> heapsize = heap -> maxSize = dim;
            generaArray(heap -> array, dim);
            inizio = clock();
            kMinHeap(heap, k);
            media = (double) clock() - inizio;
            free(heap -> array);
        }
        media /= prove;
        fprintf(f, "%d\t%f\n", dim, media);
    }

    fclose(f);
////////////////////////////////////////////////////////////

////////////////QUARTO ALGORITMO///////////////////////////
    f = fopen("tempiMaxHeap.txt", "w");
    //k costante
    k = 50;

    //esperimento
    for(dim = 100; dim < 5000; dim += 100){
        media = 0;
        for(prove = 0; prove < 10; prove++){
            heap -> array = malloc(sizeof(int) * dim);
            heap -> heapsize = heap -> maxSize = dim;
            generaArray(heap -> array, dim);
            inizio = clock();
            kMaxHeap(heap, k);
            media += (double) clock() - inizio;
            free(heap -> array);
        }
        media /= prove;
        fprintf(f, "%d\t%f\n", dim, media);          
    }

    fprintf(f, "\n");

    for(dim = 100; dim < 5000; dim += 100){
        k = kN(dim);
        media = 0;
        for(prove = 0; prove < 10; prove++){
            heap -> array = malloc(sizeof(int) * dim);
            heap -> heapsize = heap -> maxSize = dim;
            generaArray(heap -> array, dim);
            inizio = clock();
            kMaxHeap(heap, k);
            media += (double) clock() - inizio;
            free(heap -> array);
        }
        media /= prove;
        fprintf(f, "%d\t%f\n", dim, media);          
    }

    fprintf(f, "\n");

    for(dim = 100; dim < 5000; dim += 100){
        k = klogN(dim);
        media = 0;
        for(prove = 0; prove < 10; prove++){
            heap -> array = malloc(sizeof(int) * dim);
            heap -> heapsize = heap -> maxSize = dim;
            generaArray(heap -> array, dim);
            inizio = clock();
            kMaxHeap(heap, k);
            media += (double) clock() - inizio;
            free(heap -> array);
        }
        media /= prove;
        fprintf(f, "%d\t%f\n", dim, media);          
    }

    fclose(f);
*/
///////////////////////////////////////////////////////////
    dim = 100;
    k = 40;
    int i;
    int *tmp = malloc(sizeof(int) * dim);
    array = malloc(sizeof(int) * dim);
    
    generaArray(tmp, dim);
    for(i = 0; i < dim; i++){
        array[i] = tmp[i];
    }

    randomizeQuicksort(array, 0, dim - 1);
    printf("quicksort: %d\n", array[k - 1]);

    for(i = 0; i < dim; i++){
        array[i] = tmp[i];
    }

    printf("kpartiton: %d\n", kPartiton(array, 0, dim - 1, k));

    free(array);

    Heap *heap = malloc(sizeof(Heap));
    heap -> array = malloc(sizeof(int) * dim);
    heap -> heapsize = heap -> maxSize = dim;

    for(i = 0; i < dim; i++){
        heap -> array[i] = tmp[i];
    }

    printf("kminheap: %d\n", kMinHeap(heap, k));

    heap -> heapsize = heap -> maxSize = dim;
    for(i = 0; i < dim; i++){
        heap -> array[i] = tmp[i];
    }

    printf("kmaxheap: %d\n", kMaxHeap(heap, k));

    free(heap -> array);
    free(heap);

    return 0;
}