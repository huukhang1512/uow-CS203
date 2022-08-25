#ifndef BUCKET_H
#define BUCKET_H
#include "KeyValueEntry.h"
#include "String.h"
class CharArrayBucket {
    private: 
        KeyValueEntry *begin, *end; //head and tail of the linkedlist
    public: 
        CharArrayBucket(){
            begin = nullptr;
            end = nullptr;
        }

        KeyValueEntry* getEntry(const char* key){
            KeyValueEntry * keyVal = begin;
            while(keyVal != nullptr){
                if(isEqual(keyVal->getKey(), key)){
                    return keyVal;
                }
                keyVal = keyVal->next;
            }
            return nullptr;
        };

        KeyValueEntry * addEntry(const char* key, int value){
            KeyValueEntry * keyVal = new KeyValueEntry(key,value);
            if(begin == nullptr){ // Linked List is empty
                begin = keyVal;
                end = keyVal;
            } else {
                end->next = keyVal;
                end = end->next;
            }
            return keyVal;
        }
};
#endif
