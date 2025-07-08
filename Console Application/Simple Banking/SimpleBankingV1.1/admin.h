#ifndef C_ADMIN_H
#define C_ADMIN_H
#include "stdio.h"
#include "general.h"
#include "transcation.h"


void adminSession(int user_id);
int userManagement(int id);


void adminAccCreate(const char file[]){
    FILE *fptr;
    fptr = fopen(file, "w");
    fprintf(fptr,"%d %s %s %s %d %d %d %d %d\n", 1 , "Administrator", "admin@gmail.com", "R0tartsinimda", 0, 0, 0, 0, 0);
    fprintf(fptr,"%d %s %s %s %d %d %d %d %d\n", 2 , "owner", "owner@n1c.com", "0wN3rR", 0, 0, 0, 0, 0);
    fprintf(fptr,"%d %s %s %s %d %d %d %d %d\n", 3 , "soc", "soc@gmail.com", "qwert1234@A", 0, 0, 0, 0, 0);
    fclose(fptr);
}

void adminSession(int user_id){//admin privilege
    int choice = 0;
    int isSession = 1;
    while(isSession){
        printf("Welcome %s.\n1. User Account Management\n2. Transaction Record\n3. Logout\nInput Here : ", userdb[id2index(user_id)].userName);
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Name OR Email of Target : ");
                char target[20];
                scanf("%s", &target);
                int targetId = username2Id(target);
                if( targetId < 3){
                    int targetId = email2Id(target);
                    if(targetId < 3){
                        printf("\nThis User Not Have\n");
                        break;
                    }
                }
                userManagement(targetId);
                break;
            case 2:
                allTranHistory();
                break;
            case 3:
                isSession = 0;
                break;
            default:
                printf("Worng Choice ,Try Again Mr.%se...\n\n", userdb[id2index(user_id)].userName);
        }
    }
}

int userManagement(int id){
    int choice;
    printf("\t\tUAM Settings\n1. Reset Password\n2. Ban or Not\n3. Suspend or Not\n4. Back\nEnter Your Choice [1-4] : ");
    scanf("%d", &choice);
    int userIndex = id2index(id);
    switch(choice){
        case 1:;
            char password[20];
            printf("Enter New Password For %s -> ", userdb[userIndex].userName);
            scanf(" %[^\n]", &userdb[userIndex].userPassword);
            printf("Password Is Changed Successfully..\n");
            break;
        case 2:;
            int ban;
            printf("1.Ban\n2.Not\nEnter Your Choice [1-2] :");
            scanf("%d", &ban);
            if( ban == 1){
                userdb[userIndex].isBanned = 1;
            }else if( ban == 2){
                userdb[userIndex].isBanned = 0;
            }else{
                printf("Wrong Choice.");
            }
            break;
        case 3:;
            int suspend;
            printf("1.Suspend\n2.Not\nEnter Your Choice [1-2] :");
            scanf("%d", &ban);
            if( suspend == 1){
                userdb[userIndex].isSuspended = 1;
            }else if( suspend == 2){
                userdb[userIndex].isSuspended = 0;
            }else{
                printf("Wrong Choice.");
            }
            break;
        case 4:
            break;
        default:
            printf("Worng Choice,Try Again");
    }
}


#endif //C_ADMIN_H
