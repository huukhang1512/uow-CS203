#ifndef CharArrayMap_H
#define CharArrayMap_H
#include "KeyValueEntry.h"
#include "Bucket.h"
#include <iostream>
class CharArrayMap {
    private:
        const static int CAPACITY = 5000;
        CharArrayBucket map[CAPACITY]; 
        int size = 0;

        unsigned long getHash(const char *str){
            // djb2 algorithm for hashing
            unsigned long hash = 5381;
            int c;

            while (c = *str++)
                hash = hash * 33 + c;
            return hash % CAPACITY;
        }

       
    public:
        KeyValueEntry* getEntry(const char* key){
            int hash = getHash(key);
            return map[hash].getEntry(key);
        }
        KeyValueEntry *begin, *end; //head and tail of the linkedlist
        CharArrayMap(){
            begin = nullptr;
            end = nullptr;
        };
        int getSize(){
            return size;
        }
        void put(const char* key, int value){
            if(containsKey(key)){
                getEntry(key)->setValue(value);
            } else {
                int hash = getHash(key);
                KeyValueEntry * keyVal = map[hash].addEntry(key,value);
                if(begin == nullptr){ // Linked List is empty
                    begin = keyVal;
                    end = keyVal;
                } else {
                    end->nextItr = keyVal;
                    end = end->nextItr;
                }
                size++;
            }
        };

        int get(const char* key){
            if(containsKey(key)){
                return getEntry(key)->getValue();
            }
            return -1;
        };
        bool containsKey(const char* key){
            return getEntry(key) != nullptr;
        }
};
#endif