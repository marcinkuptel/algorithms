#include <iostream>
#include <climits>

const int kInputSize = 10;
using namespace std;

void printArray(int array[], int length)
{
    for (int i = 0; i < length; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

void merge(int array[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int *L = new int[n1 + 1];
    int *R = new int[n2 + 1];
    
    for (int i = 0; i < n1; i++) {
        L[i] = array[p + i];
    }
    
    for(int j = 0; j < n2; j++){
        R[j] = array[q + j + 1];
    }
    
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    
    int i = 0;
    int j = 0;
    
    for (int k = p; k <= r; k++) {
        if(L[i] <= R[j] ){
            array[k] = L[i];
            i++;
        }else{
            array[k] = R[j];
            j++;
        }
    }
    
    delete [] L;
    delete [] R;
}

void mergeSort(int array[], int p, int r)
{
    if(p < r){
        int q = (p + r)/2;
        mergeSort(array, p, q);
        mergeSort(array, q + 1, r);
        merge(array, p, q, r);
    }
}


int main(int argc, char *argv[]) {

    int input[kInputSize] = {2, 5, 1, 9, 11, 23, 12, 3, 9, 4};
    printArray(input, kInputSize);
    mergeSort(input, 0, kInputSize - 1);
    printArray(input, kInputSize);
    return 0;
}