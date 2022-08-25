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
        // Read File and construct string pool
        ifstream textFile = openNewFile(argv[1]);
        const int MAX_WORD_LENGTH = 45; // longest possible word length
        const int MAX_NUM_OF_WORDS = 50000;  // maximum constraint
        const int MAX_NUM_OF_CHAR = 100000;

        char stringPool[MAX_NUM_OF_CHAR];
        int length[MAX_NUM_OF_WORDS];
        char text[MAX_WORD_LENGTH];
        
        int wordNum = 0;
        int curStringPoolIndex = 0;
        while(textFile >> text){
            int i = 0;
            int textLength = 0;
            while(text[i] != '\0'){
                if(isalpha(text[i])){
                    stringPool[curStringPoolIndex++] = tolower(text[i]);
                    textLength++;
                }
                i++;
            }
            length[wordNum++] = textLength;
        }

        // Create a Map to store the occurence of words
        CharArrayMap map;
        int start = 0;
        for(int i=0; i < wordNum; i++){
            char * curString = new char[length[i]];
            for(int j = 0; j < length[i]; j++){
                curString[j] =  stringPool[start + j];
            }
            // get the start of the next word
            start += length[i]; 

            // update the count of the string in the hashmap.
            if(map.containsKey(curString)){
                int count = map.get(curString);
                map.put(curString, count+1);
            } else {
                map.put(curString, 1); // create a new entry in the hashmap
            }
        }
        KeyValueEntry * begin = map.begin;
        KeyValueEntry * entries = new KeyValueEntry[map.getSize()];

        // Create an array of map items
        int i = 0;
        while(begin != nullptr){
            entries[i++].setEntry(begin->getKey(), begin->getValue());
            begin = begin->nextItr;
        }

        // Sort
        mergeSort(entries, 0, map.getSize() - 1);

        int k = map.getSize() < 10 ? map.getSize() : 10; // handle the edge case where there are less than 10 words

        cout << "Number of words: " << wordNum << endl;
        cout << "List of first 10 words in the sorted list:" << endl;
        for(int i = 0; i < k; i++){
            const char * key = entries[i].getKey();
            const int value = entries[i].getValue();
            cout << key << ": " << value << endl;
        }

        cout << "..." << endl;
        cout << "List of 10 last words in the sorted list:" << endl;
        for(int i = map.getSize() - k; i < map.getSize(); i++){
            const char * key = entries[i].getKey();
            const int value = entries[i].getValue();
            cout << key << ": " << value << endl;
        }
        cout << "..." << endl;
        cout << "List of unique words (only appear once):" << endl;
        for(int i = map.getSize() - 1; entries[i].getValue() == 1 ; i--){
            const char * key = entries[i].getKey();
            cout << key;
            if(i-1 >= 0 && entries[i-1].getValue() == 1){
                cout << ", ";
            }
        }
        cout << endl;
        delete[] entries;
        return 0;
    }
    catch (exception &e) {
        cout << e.what() << endl;
        return 1;
    }
}
