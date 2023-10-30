void quickSort(int [], int, int, int);
int lomutoPartition(int [], int, int, int);
void swapOnly(int [],int,int);

void quickSort(int arr [], int p, int q, int n){
    if(p < q){
        int r = lomutoPartition(arr, p, q, n);
        quickSort(arr,p,r-1,n);
        quickSort(arr,r+1,q,n);
    }
}

int lomutoPartition(int arr[], int p, int q, int n){
    int pivot = arr[p];
    int i = p;

    for(int j = p+1; j <= q; j++){
        if(arr[j] <= pivot){
            i++;
            swapOnly(arr,i, j);
        }
    }
    swapOnly(arr,i, p);
    
    return i;
}

void swapOnly(int arr[], int a, int b) {
 if (arr[a] == arr[b])
        return;
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}