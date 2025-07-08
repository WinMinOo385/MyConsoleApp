#ifndef C_TRANSCATION_H
#define C_TRANSCATION_H
#include "stdio.h";
#include "general.h"


int currencyTransfer(int senderID, int amountASM, char reciverAddress[]){

    //Reciver Address check having or not?
    int senderIndex = id2index(senderID);
    int reciverID = -1;
    if(reciverID < 0){
        reciverID = username2Id(reciverAddress);
        if(reciverID < 0){
            reciverID = email2Id(reciverAddress);
            if(reciverID < 0){
                printf("This Reciver Address is not exist.\tSo not Send ASM Point!!\n");
                return 0;
            }
        }
    }
    int reciverIndex = id2index(reciverID);


    //is Banned or Suspend?
    if(userdb[reciverIndex].isBanned == 1){
        printf("This User is Banned From Administrator Team\n");
        return 0;
    }
    if(userdb[reciverIndex].isSuspended == 1){
        printf("This User is Suspend From Administrator Team\n");
        return 0;
    }

    //Sender & Reciver Must not be Same
    if(senderID == reciverID){
        printf("Your Cannot Send Yourself Sir\n");
        return 0;
    }else if(reciverID < 4){
        printf("This Reciver Address is not exist.\tSo not Send ASM Point!!\n");
        return 0;
    }

    if(amountASM > 0 && userdb[senderIndex].cryptoCurrency >= amountASM){
        //Subtracting ASM point From Sender
        userdb[senderIndex].cryptoCurrency -= amountASM;
        //Adding ASM point to Reciver
        userdb[id2index(reciverID)].cryptoCurrency += amountASM;
    }else{
        printf("You Have Only %d Balance....\n", userdb[senderIndex].cryptoCurrency);
        return 0;
    }
    userdb[senderIndex].tranCount++;
    userdb[reciverIndex].tranCount++;

    int senderTC = userdb[senderIndex].tranCount - 1;
    int reciverTC = userdb[reciverIndex].tranCount - 1;

    //transaction Record;
    sprintf(userdb[senderIndex].tran[senderTC].tranHistory,"%s-is-transfered-%d-ASM-to-%s-at-%s", userdb[senderIndex].userName,amountASM,userdb[reciverIndex].userName, getCurrentTime());
    sprintf(userdb[reciverIndex].tran[reciverTC].tranHistory,"%s-is-recived-%d-ASM-from-%s-at-%s", userdb[reciverIndex].userName,amountASM,userdb[senderIndex].userName, getCurrentTime());
    return 1;
}

//Transcation History
void tranHistory(int id){
    int userIndex = id2index(id);
    for(int i = 0; i < userdb[userIndex].tranCount; i++){
        printf("%s\n", userdb[userIndex].tran[i].tranHistory);
    }
}

void allTranHistory(){
    for(int i = 0; i < user_count;i++){
        for(int k = 0; k < userdb[i].tranCount; k++)
        printf("%s\n", userdb[i].tran[k].tranHistory);
    }
}

#endif //C_TRANSCATION_H
