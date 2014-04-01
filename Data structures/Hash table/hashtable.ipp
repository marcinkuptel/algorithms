#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include "hashfunction.hpp"
#include "hashtable.hpp"

//public
template <class T>
HashTable<T>::HashTable(uint32_t size)
{
    this->size = size; 
    this->elems = new list<pair<string, T> >*[size];
    for(int i = 0; i < size; i++){
        this->elems[i] = nullptr;
    }
}

template<class T>
HashTable<T>::~HashTable(){
    delete [] this->elems;
}

template<class T>
shared_ptr<T> HashTable<T>::getItem(string str)
{    
    const char * const_str = str.c_str();
    uint32_t hash = SuperFastHash(const_str, str.size()) % this->size;
    
    list<pair<string, T> > *bucket = this->elems[hash];
    if(bucket != nullptr){
        for(typename list<pair<string, T> >::iterator it = bucket->begin(); it != bucket->end(); it++){
            pair<string, T> p = *it;
            if(p.first.compare(str) == 0){
                return shared_ptr<T>(new T(p.second));
            }
        }
        return shared_ptr<T>();
        
    }else{
        return shared_ptr<T>();
    }
}

template<class T>
void HashTable<T>::putItem(T value, string str)
{
    const char * const_str = str.c_str();
    uint32_t hash = SuperFastHash(const_str, str.size()) % this->size;
    list<pair<string, T> > *bucket = this->elems[hash];
    if(bucket != nullptr){
        
        bool modified = false;
        
        for(typename list<pair<string, T> >::iterator it = bucket->begin(); it != bucket->end(); it++){
            pair<string, T> p = *it;
            if(p.first.compare(str) == 0){
                (*it) = pair<string, T>(str, value);
                modified = true;
                break;
            }
        }
        
        if(!modified){
            bucket->push_back(pair<string, T>(str, value));   
        }
        
    }else{
        bucket = new list<pair<string, T> >();
        bucket->push_back(pair<string, T>(str, value));
        this->elems[hash] = bucket;
    }
}

template<class T>
void HashTable<T>::printContents()
{
    for(int i = 0; i < this->size; i++){
        
        cout<<i<<".";
        
        list<pair<string, T> > *bucket = this->elems[i];
        if(bucket != nullptr){
            
            for(typename list<pair<string, T> >::iterator it = bucket->begin(); it != bucket->end(); it++){
                pair<string, T> p = *it;
                cout<<"["<<p.first<<"] = "<<p.second<<", "<<flush;
            }
            
            cout<<endl;
            
        }else{
            cout<<endl;
        }
    }
}