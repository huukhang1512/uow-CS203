#include <iostream>
#include <fstream>
#include "Map.h"
#include "Sort.h"

using std::exception;
using std::cout;
using std::endl;
using std::ifstream;

ifstream openNewFile(char* filePath){

    cout << "Loading file from path " << filePath << "..." << endl;
    ifstream file(filePath);

    if(file.fail()){
        throw std::invalid_argument("Unable to locate the file, please make sure your file path is correct");
    }
    return file;
}

int main(int argc, char *argv[]) {
    try {
        if (argc != 2)
        {
            throw std::invalid_argument("Please provide a valid arguments stated below: \n ./main <path_to_txt_file>");
            return 1;
        }
        ifstream textFile = openNewFile(argv[1]);
        const int MAX_WORD_LENGTH = 45; // longest possible word length
        const int MAX_NUM_OF_WORDS = 50000;  // maximum constraint
        char stringPool [MAX_NUM_OF_WORDS][MAX_WORD_LENGTH];
        char text[MAX_WORD_LENGTH];
        
        int wordNum = 0;
        int curIndex = 0;
        while(textFile >> text){
            int i=0;
            while(text[i] != '\0'){
                if(isalpha(text[i])){
                    stringPool[wordNum][curIndex++] = tolower(text[i]);
                }
                i++;
            }
            stringPool[wordNum][curIndex] = '\0'; // null terminate
            wordNum++;
            curIndex = 0; 
        }
        CharArrayMap map;
        for(int i=0; i < wordNum; i++){
            if(map.containsKey(stringPool[i])){
                int count = map.get(stringPool[i]);
                map.put(stringPool[i], count+1);
            } else {
                map.put(stringPool[i], 1);
            }
        }
        KeyValueEntry * begin = map.begin;
        KeyValueEntry * entries = new KeyValueEntry[map.getSize()];

        //create an array of map items
        int i = 0;
        while(begin != nullptr){
            entries[i++].setEntry(begin->getKey(), begin->getValue());
            begin = begin->next;
        }
        mergeSort(entries, 0, map.getSize() - 1);
        int k = map.getSize() < 10 ? map.getSize() : 10; // handle the case where there are less than 10 words
        cout << "List of first 10 most frequent words:" << endl;
        for(int i = 0; i < k; i++){
            const char * key = entries[i].getKey();
            const int value = entries[i].getValue();
            cout << key << ": " << value << endl;
        }
        cout << "..." << endl;
        cout << "List of last 10 most frequent words:" << endl;
        for(int i = map.getSize() - 1; i >= map.getSize() - k; i--){
            const char * key = entries[i].getKey();
            const int value = entries[i].getValue();
            cout << key << ": " << value << endl;
        }
        cout << "..." << endl;
        cout << "List of unique words (only appear once):" << endl;
        int count = 0;
        for(int i = map.getSize() - 1; i >= 0; i--){
            const char * key = entries[i].getKey();
            const int value = entries[i].getValue();
            if(value != 1){
                break;
            }
            count++;
            cout << key << endl;
        }
        delete[] entries;
        return 0;
    }
    catch (exception &e) {
        cout << e.what() << endl;
        return 1;
    }
}