#include "stdio.h"
#include "Encryption.h"
#include "Decryption.h"


int main(){
    char text[50];
    char secret[50];

    printf("\tXOR And Reverse Text Algorithm\n");

    printf("Enter A Text To Encrypt : ");
    scanf(" %[^\n]", &text);

    do{
        printf("Enter Passphrase To Encrypt Data : ");
        scanf(" %[^\n]", &secret);
    }while((cLength(secret) <= 1) ? printf("Passphrase Length Must be  least 2\n") : 0);


    char* e = EncryptData(text,secret);
    printf(": Encrypted Data is :\n%s\n",e);
    char * d = DecryptData(e, secret);
    printf(": Decrypted Data is :\n%s\n", d);

    return 0;
}