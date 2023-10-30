// C program to implement dual pivot QuickSort
#include <stdio.h>

int partition(int* arr, int low, int high, int* lp);
int counterSwap = 0;
int counterComp = 0;
int toLeft = 0;
int toRight = 0;

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
    counterSwap++;
}

void DualPivotQuickSort(int* arr, int low, int high) {
	if (low < high) {
		// lp means left pivot, and rp means right pivot.
		int lp, rp;
		rp = partition(arr, low, high, &lp);
		DualPivotQuickSort(arr, low, lp - 1);
		DualPivotQuickSort(arr, lp + 1, rp - 1);
		DualPivotQuickSort(arr, rp + 1, high);
	}
}

int partition(int* arr, int low, int high, int* lp) {
	if (arr[low] > arr[high])
		swap(&arr[low], &arr[high]);
	// p is the left pivot, and q is the right pivot.
	int j = low + 1;
	int g = high - 1, k = low + 1, p = arr[low], q = arr[high];
	while (k <= g) {

        if(toLeft < toRight) {
            // if elements are less than the left pivot
		    if (arr[k] < p) {
			    swap(&arr[k], &arr[j]);
			    j++;
                counterComp++;
		    }

		    // if elements are greater than or equal
		    // to the right pivot
		    else if (arr[k] >= q) {
			    while (arr[g] > q && k < g)
				    g--;
			    swap(&arr[k], &arr[g]);
			    g--;
			    if (arr[k] < p) {
				    swap(&arr[k], &arr[j]);
				    j++;
			    }   
                counterComp++;
		    }
		    k++;
        }
        else if(toRight >= toLeft) {
            
		    // if elements are greater than or equal
		    // to the right pivot
		    if (arr[k] >= q) {
			    while (arr[g] > q && k < g)
				    g--;
			    swap(&arr[k], &arr[g]);
			    g--;
			    if (arr[k] < p) {
				    swap(&arr[k], &arr[j]);
				    j++;
			    }   
                counterComp++;
		    }
            // if elements are less than the left pivot
		    else if (arr[k] < p) {
			    swap(&arr[k], &arr[j]);
			    j++;
                counterComp++;
		    }
		    k++;
        }
        
	}
	j--;
	g++;

	// bring pivots to their appropriate positions.
	swap(&arr[low], &arr[j]);
	swap(&arr[high], &arr[g]);

	// returning the indices of the pivots.
	*lp = j; // because we cannot return two elements
	// from a function.

	return g;
}

// Driver code
int main() {
	printf("DualPivotSort\n");
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
	DualPivotQuickSort(table, 0, n);
	printf("Posortowana tablica: \n");
	for (int i = 0; i < n; i++)
		printf("%d ", table[i]);
	printf("\n");
    printf("Liczba swapów: %d \n", counterSwap);
    printf("Liczba porównań: %d \n", counterComp);
	return 0;
}
