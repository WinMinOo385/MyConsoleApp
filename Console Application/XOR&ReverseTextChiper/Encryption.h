#ifndef C_ENCRYPTION_H
#define C_ENCRYPTION_H

#include <stdio.h>

int cLength(char str[]);

char * EncryptData( char *str1,  char *str2){
    static char c[100];
    int index = 0;
    int lofa = cLength(str1);
    int lofb = cLength(str2);

    //XOR Algorithm
    for(int i = 0; i < lofa; i++){
        for(int k = 0; k < lofb; k++){
            if(str1[i] != str2[k]){
                c[index] = str1[i] ^ str2[k];
            }else{
                c[index] = str1[i];
            }
            index++;
        }

    }

    //Reverse Algorithm
    int lofc = cLength(c);
    static char c1[100];
    int k = 0;
    for(int i = lofc - 1; i >= 0;i--){
        c1[k] = c[i];
        k++;
    }
    return c1;
}

int cLength(char str[]){
    int i = 0;
    while( str[i] != '\00'){
        i++;
    }
    return i;
}
#endif //C_ENCRYPTION_H
