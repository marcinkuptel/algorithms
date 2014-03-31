#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <list>
#include <memory>
#include <string>

using namespace std;

template<class T>
class HashTable {
    private:
        uint32_t size;
        list<pair<string, T> > **elems;
        
        uint32_t hash(const char*, int);
        
    public:  
        HashTable(uint32_t);
        ~HashTable();
        
        shared_ptr<T> getItem(string);
        void putItem(T, string);
        void printContents();
};

#include "hashtable.ipp"

#endif