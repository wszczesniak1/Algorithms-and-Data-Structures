#include <stdio.h>

int counterSwap = 0;
int counterComp = 0;

void swap(int* a, int* b) {
    counterSwap++;
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
        counterComp++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int main() {
    printf("Quick Sort\n");
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
	quickSort(table, 0, n - 1);
	printf("Posortowana tablica: \n");
	for (int i = 0; i < n; i++)
		printf("%d ", table[i]);
	printf("\n");
    printf("Liczba swapów: %d \n", counterSwap);
    printf("Liczba porównań: %d \n", counterComp);



	return 0;
}
