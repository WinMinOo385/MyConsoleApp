//User Management System Version 2
//fixed some bugs
//Added some features
#include <stdio.h>

#define MAX_USERS 5

struct UserDB {
    char userName[20];
    char userEmail[20];
    char userPassword[20];
    int id;

};

//declare Function
int areStringsEqual(char str1[], char str2[]);
int getId(struct UserDB userdb[], char inputUsername[], int user_count);
void userSession(struct UserDB userdb[],int user_id);
int userLogin(struct UserDB userdb[],char inputUsername[],char inputPassword[]);
int passwordCheck(char password[]);

int userSingup(struct UserDB userdb[], int user_count){
    if (user_count >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return 0;
    }
        struct UserDB newuser;
        printf("\nName = ");
        scanf("%s", &newuser.userName );
        printf("\nEmail = ");
        scanf("%s", &newuser.userEmail );
        printf("\nPassword = ");
        scanf("%s", &newuser.userPassword );


        int ispasswordStrong = passwordCheck(newuser.userPassword);
        if(!ispasswordStrong){
            printf("Password is Not Strong!!!!\nmust be contain \nPassphrase Length is least six\nAt least One Upper and Lower Letter, Number and Special Charter");
            return 0;
        }

        //username & email check
        for(int i = 0; i < user_count; i++){
            if(areStringsEqual(newuser.userName ,userdb[i].userName)) {
                printf("Username already exists. Please choose a different username.\n");
                return 0;
            } else if(areStringsEqual(newuser.userEmail, userdb[i].userEmail)) {
                printf("Email already exists. Please choose a different email.\n");
                return 0;
            }
        }
        newuser.id = user_count + 1;
        userdb[user_count] = newuser;
        printf("User Add Successfull.");
        return 1;
}

void userSession(struct UserDB userdb[],int user_id){
    int choice = 0;
    int isSession = 1;
    while(isSession){
        printf("\t\tWelcome Sir. \n1. Logout\n2. Profile\nInput Here : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                isSession = 0;
                printf("GoodBy Sir...\tLogouted\n");
                break;
            case 2:
                printf("\t\tProfile Information\nId -> %d\nUserName -> %s\n", user_id,userdb[user_id - 1].userName);
                break;
            default:
                printf("Worng Choice ,Try Again Mr.%se...\n\n", userdb[user_id - 1].userName);

        }
    }


}

int userLogin(struct UserDB userdb[],char inputUsername[],char inputPassword[]){
    //user input user & pass
    printf("Username -> ");
    scanf("%s", inputUsername);
    printf("Password -> ");
    scanf("%s", inputPassword);

    //username & password check
    for(int i = 0; i < MAX_USERS; i++){
        if(areStringsEqual(inputUsername, userdb[i].userName) && areStringsEqual(inputPassword, userdb[i].userPassword)){
            printf("Login successfull\n\n");
            return 1; //Login pass
        }
    }
    return 0; //Login fail


}

int areStringsEqual(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0;  // Strings are not equal
        }
        i++;
    }
    return str1[i] == '\0' && str2[i] == '\0';
}

int getId(struct UserDB userdb[], char inputUsername[], int user_count){
    for(int i = 0; i < user_count; i++){
        if(areStringsEqual(inputUsername, userdb[i].userName)){
            return i+1;
        };
    }
}

int passwordCheck(char password[]){
    int length = 0;
    while(password[length] != '\0'){
        length++;
    };
    if(length < 6){
        return 0;
    }
    int hasDigit = 0, hasSpecialChar = 0, hasUpperCase = 0, hasLowerCase = 0;

    for (int i = 0; i < length; i++) {
        if (password[i] >= '0' && password[i] <= '9') {
            hasDigit = 1;
        } else if (password[i] >= 'a' && password[i] <= 'z') {
            hasLowerCase = 1;
        } else if (password[i] >= 'A' && password[i] <= 'Z') {
            hasUpperCase = 1;
        } else if ((password[i] >= 33 && password[i] <= 47) || (password[i] >= 58 && password[i] <= 64) || (password[i] >= 91 && password[i] <= 96) || (password[i] >= 123 && password[i] <= 126)) {
            hasSpecialChar = 1;
        }
    }
    return hasDigit && hasSpecialChar && hasUpperCase && hasLowerCase;


}




int main(){
    char inputUsername[20];
    char inputPassword[20];
    int exit = 1;
    int user_count = 0;
    struct UserDB userdb[MAX_USERS];

    while(exit){
        int user_choice = 0;

        printf("\n\tUser Management System Menu: \n1. Sing Up\n2. Login\n3. Exit\nYour Choice : ");
        scanf("%d", &user_choice);

        switch (user_choice) {
            case 1:
                if(userSingup(userdb, user_count)){
                    user_count++;//If User Create Pass
                };
                break;
            case 2:
                if(userLogin(userdb,inputUsername,inputPassword)){
                    int user_id = getId(userdb, inputUsername, user_count);
                    userSession(userdb,user_id);
                }else{
                    printf("Login Fail...\nUsername & Password is Wrong\n");
                }
                break;
            case 3:
                exit = 0;
                break;
            default:
                printf("Wrong Choice.Try Again");
                break;
        }
    }
    return 0;
}