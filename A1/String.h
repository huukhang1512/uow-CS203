#ifndef STRING_H
#define STRING_H
int strlen(const char* str){
    int count = 0;
    while(*str!='\0') // while the current char is not the null terminator
    {
        count++;
        str++;
    }
    return count;
}
bool isEqual(const char* str1, const char* str2){
    int str1Size = strlen(str1);
    int str2Size = strlen(str2);
    if(str1Size != str2Size){
        return false;
    }
    for(int i = 0;i < str1Size;i++){
        if(str1[i] != str2[i]){
            return false;
        }
    }
    return true;
}

/**
 * @brief 
 * This function will compare two char arrays by their ascii value in each character
 * @param str1 
 * @param str2 
 * @return int 
 * 1: str1 > str2
 * -1: str1 < str2
 * 0: str1 == str2
 */
int compare(const char* str1, const char* str2){
    int str1Len = strlen(str1);
    int str2Len = strlen(str2);
    int shorterLength = str1Len < str2Len ? str1Len : str2Len;
    
    for(int i = 0; i < shorterLength; i++){
        if(str1[i] < str2[i]){
            return -1;
        } else if (str1[i] > str2[i]){
            return 1;
        } 
    }
    return 0;
}
#endif