#include <iostream>
#include <fstream>
#include "priority_queue.hpp"

using namespace std;

template<class T>
MaxPQ<T>::MaxPQ(int maxN)
{
    pq = new T[maxN + 1];
    maxSize = maxN;
}

template<class T>
MaxPQ<T>::~MaxPQ()
{
    delete [] pq;
}

template<class T>
bool MaxPQ<T>::less(int i, int j)
{
    return (pq[i] < pq[j]);    
}

template<class T>
void MaxPQ<T>::exch(int i, int j)
{
    T object = pq[i];
    pq[i] = pq[j];
    pq[j] = object;
}

template<class T>
void MaxPQ<T>::swim(int k)
{
    while(k > 1 && less(k/2, k))
    {
        exch(k/2, k);
        k = k/2;
    }
}

template<class T>
void MaxPQ<T>::sink(int k)
{
    while(2*k <= N)
    {
        int j = 2*k;
        if(j < N && less(j, j+1)) j++;
        if(!less(k, j)) break;
        exch(k, j);
        k = j;
    }
}

template<class T>
bool MaxPQ<T>::isEmpty()
{
    return N == 0;
}

template<class T>
int MaxPQ<T>::size()
{
    return N;
}

template<class T>
void MaxPQ<T>::resize(int max)
{
    T *newArray = new T[max + 1];
    for(int i = 1; i <= N; i++){
        newArray[i] = pq[i];
    }
    delete [] pq;
    pq = newArray;
    maxSize = max;
}

template<class T>
void MaxPQ<T>::insert(T v)
{
    if(N == maxSize) resize(2*maxSize);
    pq[++N] = v;
    swim(N);
}

template<class T>
T MaxPQ<T>::delMax()
{
    T max = pq[1];
    exch(1, N--);
    pq[N + 1] = NULL;
    sink(1);
    if(N > 0 && N == maxSize/4) resize(maxSize/2);
    return max;
}

template<class T>
void MaxPQ<T>::printContents()
{
    for(int i = 0; i <= maxSize; i++){
            cout<<"["<<i<<"]\t";
    }
    
    cout<<endl;
    
    for(int i = 0; i <= maxSize; i++){
        cout<<pq[i]<<"\t";
    }
}



int main(int argc, char *argv[]) 
{
//    int numberOfParams = 3;
//    
//    if(argc != numberOfParams){
//        cout<<"Wrong number of parameters "<<argc<<". Should be "<<numberOfParams;
//        return -1;
//    }
//    int lines = atoi(argv[2]);
//    
//    cout<<"Filename: "<<argv[1]<<endl;
//    cout<<"Lines: "<<lines<<endl<<endl;
//    
//    ifstream myFile(argv[1]);;
//    string line;
//    
//    while(getline(myFile, line)){
//        cout<<line<<endl;
//    }
//    
//    myFile.close();

    MaxPQ<int> queue = MaxPQ<int>(10);
    queue.insert(20);
    queue.insert(2);
    queue.insert(25);
    queue.insert(1);
    queue.insert(9);
    queue.insert(199);
    queue.insert(19);
    queue.insert(12);
    queue.insert(16);
    queue.insert(9);
    queue.insert(78);
    queue.printContents();
}