#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <vector>

template<class T>
class MaxPQ 
{
    private:
        T *pq;
        int N = 0;
        int maxSize;
    
        bool less(int i, int j);
        void exch(int i, int j);
        void swim(int k);
        void sink(int k);
        void resize(int max);
    
    public:
        MaxPQ();
        MaxPQ(int maxN);
        ~MaxPQ();
        void insert(T v);
        T max();
        T delMax();
        bool isEmpty();
        int size();
        void printContents();
};

#endif