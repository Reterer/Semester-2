#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *readArray(int *n){
    scanf("%d", n);
    
    int *arr = malloc(sizeof(int)*(*n));
    for(int i = 0; i < *n; i++){
        scanf("%d", &arr[i]);
    }

    return arr;
}

void printArray(int *arr, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int c = 0;
void insertionSort(int *arr, int n){
    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j >= 1; j--){
            c++;
            if(arr[j] >= arr[j-1]){
                break;
            }
            int t = arr[j-1];
            arr[j-1] = arr[j];
            arr[j] = t;
        }
    }
}

void selectionSort(int *arr, int n){
    for(int i = 0; i < n; i++){
        int min = arr[i];
        int minPos = i;
        for(int j = i; j < n; j++){
            c++;
            if(min > arr[j]){
                min = arr[j];
                minPos = j;
            }
        }
        int t = arr[i];
        arr[i] = arr[minPos];
        arr[minPos] = t;
    }
}

void bubbleSort(int *arr, int n){
    for(int i = n-1; i >= 0; i--){
        int idx = 0;
        for(int j = 0; j < i; j++){
            c++;
            if(arr[j] > arr[j+1]){
                idx = j+1;
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t; 
            }
        }
        i = idx;
    }
}

void shakerSort(int *arr, int n){
    int l = 0;
    int r = n-1;
    while(l < r) {
        int idx = l;
        for(int i = l; i < r; i++){
            c++;
            if(arr[i] > arr[i+1]){
                int t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                idx = i+1;
            }
        }
        r = idx;
        for(int i = r; i > l; i--){
            c++;
            if(arr[i] < arr[i-1]){
                int t = arr[i];
                arr[i] = arr[i-1];
                arr[i-1] = t;
                idx = i-1;
            }
        }
        l = idx;
    }
}

void combSort(int *arr, int n){
    double f = 1.247;
    double k = n-1;
    while(k > 0){
        for(int i = 0; i < n-(int)k; i++){
            c++;
            if(arr[i] > arr[i+(int)k]){
                int t = arr[i];
                arr[i] = arr[i+(int)k];
                arr[i+(int)k] = t;
            }
        }
        k /= f;
    }
    bubbleSort(arr, n);
}

void shellSort(int *arr, int n){
    for(int step = n/2; step > 0; step /= 2){
        for(int i = step; i < n; i++){
            for(int j = i - step; j >= 0 && arr[j] > arr[j + step]; j -= step){
                c++;
                int tmp = arr[j];
                arr[j] = arr[j+step];
                arr[j+step] = tmp;
            }
        }
    }
}

int getPivot(int *arr, int n){
    return (arr[0] + arr[n/2] + arr[n-1]) / 3;
}

int partition(int *arr, int n){
    int p  = getPivot(arr, n);
    int i = 0;
    int j = n-1;

    while(i < j){
        while(arr[i] < p && i < j)
            i++;
        while(arr[j] > p && i < j)
            j--;

        if(i < j){
            int t = arr[j];
            arr[j] = arr[i];
            arr[i] = t;
            i++;
            j--;
        }
    }
    return j;
}

void quickSort(int *arr, int n){
    if (n <= 1)
        return;
    int p = partition(arr, n);
    printArray(arr, n);
    quickSort(arr, p);
    quickSort(arr+p+1, n-p-1);
}

void countingSort(int *arr, int n){
    int maxElem = arr[0];
    for(int i = 0; i < n; i++){
        if(arr[i] > maxElem)
            maxElem = arr[i];
    }
    int *countArr = malloc(sizeof(int)*(maxElem+1));
    for(int i = 0; i <= maxElem; i++)
        countArr[i] = 0;

    for(int i = 0; i < n; i++)
        countArr[arr[i]]++;

    int j = 0;
    for(int i = 0; i < n; i++){
        while(countArr[j] == 0)
            j++;

        arr[i] = j;
        countArr[j]--;
    }
    free(countArr);
}


void merge(int *buf, int* l, int ln, int* r, int rn){
    int i = 0;
    int j = 0;

    while(i < ln && j < rn){
        if(l[i] < r[j]){
            buf[i+j] = l[i];
            i++; 
        } else {
            buf[i+j] = r[j];
            j++;
        }
    }

    if(i == ln){
        for(;j < rn; j++)
            buf[i+j] = r[j]; 
    }
    else if(j == rn){
        for(;i < ln; i++)
            buf[i+j] = l[i]; 
    }
}

void _mergeSort(int *arr, int *buf, int n){
    if(n <= 1){
        buf[0] = arr[0];
        return;
    }

    int mid = n/2;
    _mergeSort(arr, buf, mid);
    _mergeSort(arr+mid, buf+mid, n-mid);
    merge(buf, arr, mid, arr+mid, n-mid);
    for(int i = 0; i < n; i++){
        arr[i] = buf[i];
    }
    printArray(arr, n);
}

void mergeSort(int *arr, int n){
    int *buf = malloc(sizeof(int)*n);
    _mergeSort(arr, buf, n);
    free(buf);
}

int main(){
    int n;
    int *arr = readArray(&n);
    // insertionSort(arr, n);
    // selectionSort(arr, n);
    // bubbleSort(arr, n);
    // shakerSort(arr, n);
    // combSort(arr, n);
    // shellSort(arr, n);
    // quickSort(arr, n);
    // countingSort(arr, n);
    // mergeSort(arr, n);
    printArray(arr, n);
    printf("%d\n",c);
    free(arr);
    return 0;
}
