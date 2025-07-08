#include <stdio.h>

int main(){
    //creating Variable
    int i,j,k = 0;
    int num = 10;

    for(i = 0; i < num; i++){

        //First Triangle
        for(j = num; j > i; j--){
            printf(" ");
        }
        for(k = 0; k < (i * 2) - 1; k++){
            printf("*");
        }

        //Second triangle
        for(j = num*2; j > i*2; j--){
            printf(" ");
        }
        for(k = 0; k < (i * 2) - 1; k++){
            printf("*");
        }

        //Adding new Line
        printf("\n");
    }

    return 0;
}