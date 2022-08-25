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
        KeyValueEntry* nextItr;
        KeyValueEntry* next;

        KeyValueEntry(){}
        KeyValueEntry(const char* _key, int _value){
            key = _key;
            value = _value;
            nextItr = nullptr;
            next = nullptr;
        }

        void setEntry(const char* _key, int _value){
            key = _key;
            value = _value;
        }

        void setValue(int _value){
            value = _value;
        }

        int getValue(){
            return value;
        }

        const char* getKey(){
            return key;
        }
};
#endif
