//
// Created by redhoddie on 3/8/24.
//

#ifndef C_DECRYPTION_H
#define C_DECRYPTION_H
#include "stdio.h";

int cLength(char str[]);

char * DecryptData(char *str1, char *str2){
    static char d[100];
    static char d1[100];
    int index = 0;
    int k = 0;

    int lofb = cLength(str1);
    int lofc = cLength(str2);

    //Reverse Algorithm
    for(int i = lofb -1 ; i >= 0;i--){
        d[k] = str1[i];
        k++;
    }

    //XOR Algorithm
    for(int i = 0; i < lofb; i+=lofc){
        if(d[i] != str2[0]){
            d1[index] = d[i] ^ str2[0];
        }else{
            d1[index] = d[i];
        }
        index++;

    }

    return d1;
}

#endif //C_DECRYPTION_H
