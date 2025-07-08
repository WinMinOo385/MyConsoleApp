#ifndef C_USER_H
#define C_USER_H
#include "stdio.h"
#include "general.h"
#include "transcation.h"

int userSingup(){

    if (user_count >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return 0;
    }
    UserDB newuser;

    //username check
    while(1){
        int exit = 1;
        printf("\nName = ");
        scanf(" %[^\n]", &newuser.userName);
        for(int i = 0; i < user_count; i++){
            if(areStringsEqual(newuser.userName ,userdb[i].userName)) {
                printf("Username already exists. Please choose a different username.\n");
                exit = 0;
                break;
            }else if(!cspaceDetect(newuser.userName)){
                printf("Username can't allow Space!");
                exit = 0;
                break;
            }
        }
        if(exit){
            break;
        }
    }

    //email check
    while(1){
        int exit = 1;
        printf("\nEmail = ");
        scanf(" %[^\n]", &newuser.userEmail);
        for(int i = 0; i < user_count; i++){
            if(!cspaceDetect(newuser.userEmail)){
                printf("Email  can't allow Space!");
                exit = 0;
                break;
            }else if(areStringsEqual(newuser.userEmail, userdb[i].userEmail)) {
                printf("Email already exists. Please choose a different email.\n");
                exit = 0;
                break;
            }else if(emailCheck(newuser.userEmail)) {
                printf("Invalid Email Address");
                exit = 0;
                break;
            }
        }
        if(exit){
            break;
        }
    }



    //password Check
    while(1){
        printf("\nPassword = ");
        scanf(" %[^\n]", &newuser.userPassword );
        int ispasswordStrong = passwordCheck(newuser.userPassword);
        if(!ispasswordStrong){
            printf("Password is Not Strong!!!!\nmust be contain \nPassphrase Length is least six\nAt least One Upper and Lower Letter, Number and Special Charater");
        }else if(!cspaceDetect(newuser.userPassword)){
            printf("Password can't allow Space!");
        }else{
            break;
        }
    }
    //phone number check
    while(1){
        printf("\nPhoneNumber = ");
        scanf(" %f",&newuser.userPhone);
        if(isValidPhoneNumber(newuser.userPhone)){
            break;
        }
        printf("Invalid Phone Number!\n");
        printf("At Least 13 Max & 5 Min");
    }


    newuser.id = user_count + 1;
    newuser.cryptoCurrency = 100;
    newuser.tranCount = 0;
    newuser.isBanned = 0;
    newuser.isSuspended = 0;
    userdb[user_count] = newuser;
    printf("User Add Successfull.");
    return 1;
}

void userSession(int user_id){

    int choice = 0;
    int isSession = 1;
    int uindex = id2index(user_id);
    while(isSession){
        printf("\t\tWelcome Sir. \n1. My Information\n2. Send ASM\n3. Transcation History\n4. Logout\nInput Here : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\t\tProfile Information\nId -> %d\nUserName -> %s\n", user_id,userdb[uindex].userName);
                printf("Point Balance-> %d ASM\n", userdb[uindex].cryptoCurrency);
                break;
            case 2:
                printf("Point Balance-> %d ASM", userdb[uindex].cryptoCurrency);
                char reciverAddress[20];
                int amount2send;
                printf("\nAddress To Send Point. Name OR Email : ");
                scanf(" %[^\n]", &reciverAddress);
                printf("\nAmount To Transfer Point : ");
                scanf("%d", &amount2send);
                if(currencyTransfer(user_id,amount2send,reciverAddress)){
                    printf("Transaction Complete.\n");
//                    exportData(FileDB);
                }else{
                    printf("Transaction Fail....\n");
                };
                break;
            case 3:
                printf("\t\tTranscation History\n");
                tranHistory(user_id);
                break;
            case 4:
                isSession = 0;
                printf("GoodBy Sir...\tLogouted\n");
                break;
            default:
                printf("Worng Choice ,Try Again Mr.%se...\n\n", userdb[uindex].userName);

        }
    }
}

int userLogin(char inputUsername[],char inputPassword[]){


    //user input user & pass
    printf("Username -> ");
    scanf(" %[^\n]", inputUsername);
    printf("Password -> ");
    scanf(" %[^\n]", inputPassword);

    //is Ban or Suspend Check
    int userIndex = id2index(username2Id(inputUsername));
    if(userdb[userIndex].isBanned == 1){
        printf("This User is Banned From Administrator Team\n");
        return 0;
    }
    if(userdb[userIndex].isSuspended == 1){
        printf("This User is Suspend From Administrator Team\n");
        return 0;
    }

    //username & password check
    for(int i = 0; i < MAX_USERS; i++){
        if(areStringsEqual(inputUsername, userdb[i].userName) && areStringsEqual(inputPassword, userdb[i].userPassword)){
            printf("Login successfull\n\n");
            return 1; //Login pass
        }
    }
    return 0; //Login fail


}

#endif //C_USER_H
