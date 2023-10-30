#include <stdio.h>

int porownania = 0;
int swap = 0;

void merge(int arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];

	for (i = 0; i < n1; i++) {
		L[i] = arr[l + i];
    }
	for (j = 0; j < n2; j++) {
		R[j] = arr[m + 1 + j];
    }
	i = 0; 
	j = 0; 
	k = l; 
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;

		}
		else {
			arr[k] = R[j];
			j++;
		}
        porownania++;
        swap++;
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
        swap++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
        swap++;
	}

}

void insertionSort(int array [], int p, int q){
    int key, i;

    for( int j = p; j < q; j++){
        key = array[j+1];
        i = j+1;

        while (i > p && array[i-1] > key){
            array[i] = array[i-1];
            i--;
            porownania++;
            swap++;
        }
        array[i] = key;

        if(i > p){
            porownania++;
        } 
    }
}

void hybrid(int arr[], int l, int r, int n) {
	if (r - l > 20) { 
		int m = l + (r - l) / 2;
		hybrid(arr, l, m, n);
		hybrid(arr, m + 1, r, n);
		merge(arr, l, m, r);
		printf(" \n");
	}
    else { 
		insertionSort(arr, l, r);
    }
}

int main() {
    printf("Hybrid Sort\n");
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

	hybrid(table, 0, n - 1, n);

	printf("Posortowana tablica: \n");
	for (int i = 0; i < n; i++)
		printf("%d ", table[i]);
	printf("\n");
    printf("Liczba swapów: %d \n", swap);
    printf("Liczba porównań: %d \n", porownania);

	return 0;
}
