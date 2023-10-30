#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "quickSort.h"

int numComps = 0;
int n;

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

int binarySearch(int arr[], int l, int r, int x) {
    numComps++;
    if (r >= l) {
        int mid = l + (r - l) / 2;
        numComps++;
        if (arr[mid] == x)
            return 1;
        numComps++;
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return 0;
}


int main(int argc, char ** argv){
   
    
    n = atoi(argv[1]);
    int array[n];    
    int searchingValue = atoi(argv[2]);
    
    for(int i = 0; i < n; i++){
        
        array[i] = i;            
    }

    clock_t t;

        
    printf("Poczatkowy stan tablicy: ");
    printArray(array,n);

    printf("Szukana wartość: %d\n",searchingValue);


    t = clock();
    if(binarySearch(array, 0, n-1 , searchingValue) == 0) {
        printf("Wartości nie ma w tablicy\n");
    }
    else {
        printf("Wartość jest w tablicy\n");
    }
        
    t = clock() - t;
    
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("Liczba porownan:%d\n", numComps);
    printf("Czas wykonania:%F\n",time_taken);
    
    return 0;
}