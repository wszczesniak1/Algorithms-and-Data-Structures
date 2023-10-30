#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

void insertionSort(int tablica [], int n) {
    int swaps = 0;
    int key;
    int i;
    int j;
    int porwownania = 0;
    for(j = 1; j < n; j++) {
        key = tablica[j];
        i = j - 1;
        while (i >= 0 && tablica[i] > key) {
            tablica[i+1] = tablica[i];
            i--;
            swaps++;
            porwownania++;
        }
        if(i >= 0) {
            porwownania++;
        }
        tablica[i+1] = key;
        for(int a = 0; a < n; a++) {
            printf("%d, ", tablica[a]);
        }
        printf("\n");

    }
    printf("\nPosortowana tablica ");
    for(int a = 0; a < n; a++) {
        printf("%d, ", tablica[a]);
    }
    printf("\n");
    printf("Liczba przestawień %d\n", swaps);
    printf("Liczba porownan %d\n", porwownania);
}

int main() {
    printf("Insertin sort\n");
    char *line = NULL;
    size_t length = 0;
    getline(&line, &length, stdin); 

    int n = atoi(line);
    int table [n];
    printf("Tablica wejsciowa: ");
    for(int i = 0; i < n; i++) {
        getline(&line, &length, stdin);
        table[i] = atoi(line);
        printf("%d, ", table[i]);
    }
    printf(" \n");
    insertionSort(table, n);
    return 0;
}
