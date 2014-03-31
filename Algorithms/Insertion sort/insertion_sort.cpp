#include <iostream>
using namespace std;

const int kInputSize = 10;

void printArray(int array[], int length)
{
    for (int i = 0; i < length; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

/**
 Method sorting an array of integers.
 */
void insertionSort(int input[], int length)
{
    int key, i;
        
    for (int j = 1; j < length; j++) {
        key = input[j];
        i = j - 1;
        while (i >= 0 && input[i] > key) {
            input[i+1] = input[i];
            i--;
        }
        input[i+1] = key;
    }
}

int main(int argc, char *argv[]) {
    
    int input[kInputSize] = {2, 5, 1, 9, 11, 23, 12, 3, 9, 4};
        
    insertionSort(input, kInputSize);
    printArray(input, kInputSize);
    
    return 1;
}