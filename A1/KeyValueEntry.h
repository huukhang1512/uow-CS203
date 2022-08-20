#ifndef KeyValueEntry_H
#define KeyValueEntry_H
#include <iostream>
using std::cout;
using std::endl;
class KeyValueEntry {
    private:
        const char* key;
        int value;
    public:
        KeyValueEntry* next;
        KeyValueEntry(){}
        KeyValueEntry(const char* _key, int _value){
            key = _key;
            value = _value;
            next = nullptr;
        }
        KeyValueEntry(const KeyValueEntry& keyVal){
            key = keyVal.key;
            value = keyVal.value;
            next = keyVal.next;
        }

        void setEntry(const char* _key, int _value){
            value = _value;
            key = _key;
        }
        void setKey(const char* _key){
            this->key = _key;
        }
        void setValue(int value){
            this->value = value;
        }
        int getValue(){
            return value;
        }
        const char* getKey(){
            return key;
        }
};
#endif