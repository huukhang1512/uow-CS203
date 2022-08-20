#ifndef BUCKET_H
#define BUCKET_H
#include "KeyValueEntry.h"
#include "String.h"
class CharArrayBucket {
    private: 
        const static int CAPACITY = 10;
        KeyValueEntry entries [CAPACITY];
        int size = 0;
    public: 
        CharArrayBucket(){}
        KeyValueEntry* getEntry(const char* key){
            for(int i=0; i < size; i++){
                if(isEqual(entries[i].getKey(), key)){
                    return &entries[i];
                }
            }
            return nullptr;
        };
        int getSize(){
            return size;
        }
        KeyValueEntry * addEntry(const char* key, int value){
            entries[size].setKey(key);
            entries[size].setValue(value);
            size++;
            return &entries[size-1];
        }
        void removeEntry(KeyValueEntry entry){
            for(int i=0; i < size; i++){
                if(isEqual(entries[i].getKey(), entry.getKey())){
                    for(int j = 0; j < size; j++){
                        entries[j] = entries[j+1];
                    }
                    break;
                }
            }
        }
};
#endif