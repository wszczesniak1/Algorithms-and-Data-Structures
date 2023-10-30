#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "quickSort.h"

int K = 9;

int numComps = 0;
int numSwaps = 0;
int n;
int *arrayPtr;
int flag = 0;

void swap(int [], int , int);
int comp(int,int);
void printArray(int [], int);
int partition(int [],int, int,int);
int findMed(int [], int , int);
int selectAlg(int [], int , int, int);

int main(int argc, char ** argv){
    char *line =NULL;
    size_t len = 0;
    ssize_t lineSize = 0;
    lineSize = getline(&line, &len, stdin);
    
    n = atoi(line);
    int array[n];

    lineSize = getline(&line, &len, stdin);
    int k = atoi(line)-1;     
    
    for(int i = 0; i < n; i++){
        lineSize = getline(&line, &len, stdin);
        array[i] = atoi(line);            
    }
    free(line);
    
    arrayPtr = array;
    int statisticPosition;

    clock_t t;

    if(n < 50){
        flag = 1;
        
        printf("Poczatkowy stan tablicy: ");
        printArray(array,n);

        t = clock();
        statisticPosition = selectAlg(array,0,n-1,k);
        t = clock() - t;
        
        printf("Koncowy stan tablicy:    ");
        printArray(array,n);

        printf("Szukana statystyka pozycyjna na numerze %d: %d\n",k, statisticPosition);
    
        quickSort(array,0, n-1,n);
        printf("Posortowana tablica:\n");
        printArray(array,n);

    }

    else {
        t = clock();
        statisticPosition = selectAlg(array,0,n-1,k);
        t = clock() - t;
    }

    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("Liczba porownan:%d\n", numComps);
    printf("Liczba swapow:%d\n",numSwaps);
    printf("Czas wykonania:%F\n",time_taken);
    

    return 0;
}

int selectAlgorytm(int arr [], int left, int right, int i) {
   
    if(left == right)
        return arr[left];
    
    int num = right - left + 1; 
    int median [(num+K-1)/K]; // tablica przechowujaca mediany kazdej z grup, liczba grup to sufit z n/K
    int groupIndex = 0;

    while (groupIndex < num / K) { // szukanie mediany dla kazdej z pelnych grup K elem.
        int m = findMed(arr, left + groupIndex * K, K);
        median[groupIndex] = m;
        groupIndex++;
    }

    if (groupIndex * K < num) { // przypdaek jesli zostaly jeszcze jakies elementy
        int m = findMed(arr, left + groupIndex * K, num % K);
        median[groupIndex] = m;
        groupIndex++;

    }


    int totalMed;
    if (groupIndex == 1) // jesli byla tylko jedna grupa, nie ma potrzeby na wywolanie rekurencyjne
        totalMed = median[groupIndex - 1];
    else
        totalMed = selectAlg(median, 0, groupIndex - 1, (groupIndex) / 2); // liczenie mediany median
    
    int p = partition(arr, left, right, totalMed);
    int elems = p - left + 1; // liczba elementow w partycji
    
    if (elems == i) // to jest element ktorego szukamy
        return arr[p];
    if (i < elems) // element znajduje sie w dolnej partycji
        return selectAlg(arr, left, p - 1, i);
    else
        return selectAlg(arr, p + 1, right, i - elems); // element znajduje sie w gornej partycji na pozycji wzglednej (i - elems)

}


int findMed(int arr [], int left, int numElems) {
    int right = left + numElems;

    for (int i = left; i < right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && comp(key, arr[j])) {
            numSwaps++;
            arr[j + 1] = arr[j];
            j--;

        }
        arr[j + 1] = key;
    }
    
    if (numElems % 2 == 0)
        return arr[(left + right + 1) / 2];
    else
        return arr[(left + right) / 2];
}

int partition(int arr[], int left, int right, int pivot) {
    
    int i;
    for (i = left; i <= right; i++) { // znalezienie indeksu mediany median
        if (arr[i] == pivot)
            break;
    }
    swap(arr, i, left);

    i = left;
    for (int j = left + 1; j <= right; j++) {
        if (comp(arr[j], arr[left])) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i, left);

    if(flag){
        printArray(arrayPtr,n);
    }
    return i;
}

void printArray(int arr [], int n) {
    printf("|");
    
    for(int i = 0; i < n-1; i++){
        if(arr[i] < 10){
            printf("0%d,", arr[i]);
        }
        else{
            printf("%d,", arr[i]);
        }
    }
    
    if(arr[n-1] < 10){
        printf("0%d |\n", arr[n-1]);
    }
    else{
        printf("%d |\n", arr[n-1]);
    }
}

int comp(int a, int b) {
    numComps++;
    return a <= b;
}

void swap(int arr[], int a, int b) {
    if (arr[a] == arr[b])
        return;
    numSwaps++;
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}
