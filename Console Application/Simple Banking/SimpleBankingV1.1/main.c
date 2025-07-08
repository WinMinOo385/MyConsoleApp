//User Management System Version 5.0
//fixed some bugs
//Admin Panel Features

#include <stdio.h>
#include "admin.h"
#include "general.h"
#include "user.h"

int main(){
    user_count = fline_count(FileDB);//global user Count
    importData(FileDB);//import file data to struct
    char inputUsername[20];
    char inputPassword[20];
    int exit = 1;

    while(exit){
        int user_choice = 0;
        printf("\n\tUser Management System Menu: \n1. Sing Up\n2. Login\n3. Exit\nYour Choice : ");
        scanf("%d", &user_choice);

        switch (user_choice) {
            case 1:
                if (userSingup()) {
                    user_count++;//If User Create Pass
                    exportData(FileDB);
                }else{
                    printf("\nUser Create Fail........");
                }
                break;
            case 2:
                if (userLogin(inputUsername, inputPassword)) {
                    int user_id = username2Id(inputUsername);
                    if(user_id < 4){
                        adminSession(user_id);
                    }else{
                        userSession(user_id);
                    }
                } else {
                    printf("Login Fail...\nUsername & Password is Wrong\n");
                }
                break;
            case 3:
                exportData(FileDB);
                exit = 0;
                break;
            default:
                printf("Wrong Choice.Try Again");
                break;
        }
    }
    return 0;
}