#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "quickSort.h"

int numSwaps = 0;
int numComps = 0;
int n;
int flag = 0;

void swap(int [], int , int);
int comp(int,int);
int partition(int [],int, int);
int randPartition(int arr[], int left, int right); 
int randSelect(int [], int, int, int);
void printArray(int [], int);

int main(int argc, char **argv)
{
    srand(time(NULL));
    
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

    int statisticPosition;

    if(n < 50){
        flag = 1;
        
        printf("Poczatkowy stan tablicy: ");
        printArray(array,n);

        statisticPosition = randSelect(array,0,n-1,k);
        
        printf("Koncowy stan tablicy:    ");
        printArray(array,n);

        printf("Szukana statystyka pozycyjna na numerze %d: %d\n",k, statisticPosition);
    
        quickSort(array,0, n-1,n);
        printf("Posortowana tablica:\n");
        printArray(array,n);

    }

    else {
        statisticPosition = randSelect(array,0,n-1,k);
    }

    printf("Liczba porownan:%d\n", numComps);
    printf("Liczba swapow:%d\n",numSwaps);

    return 0;
}


int partition(int arr[], int left, int right) { 
    int i = left;
    for (int j = left + 1; j <= right; j++) {
        if(comp(arr[j], arr[left])) {
            i++;
            swap(arr, i, j);
        }

    }
    swap(arr, i, left);
    return i;
}

int randPartition(int arr[], int left, int right) { // losowo zamienia pierwszy element z innym, a nastepnie wywoluje zwykla partycje
    int i = (rand()%(right - left + 1)) + left;

    swap(arr, left, i);
    
    if(flag){
        printArray(arr,n);
    }

    return partition(arr, left, right);

}

int randSelect(int arr[], int left, int right, int i) {
    if (left == right)
        return arr[left];
    
    if(flag){
        printArray(arr,n);
    }

    int p = randPartition(arr, left, right);
    int elems = p - left + 1; // liczba elementow w partycji
    if (i == elems) // element ktorego szuakmy
        return arr[p];
    if (i < elems) // element znajduje sie dolnej partycji
        return randSelect(arr, left, p - 1, i);
    else
        return randSelect(arr, p + 1, right, i - elems); // element znajduje sie w gornej partycji na pozycji wzglednej (i-elems)
}

void printArray(int arr[], int n) {
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