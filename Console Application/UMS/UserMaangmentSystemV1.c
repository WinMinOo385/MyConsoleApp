#include <stdio.h>

#define MAX_USERS 5


int areStringsEqual(char str1[], char str2[]);

struct UserDB {
    char userName[20];
    char userEmail[20];
    char userPassword[20];
    int id;

};

void userSingup(struct UserDB userdb[], int user_count){
        struct UserDB newuser;
        printf("\nName = ");
        scanf("%s", &newuser.userName );
        printf("\nEmail = ");
        scanf("%s", &newuser.userEmail );
        printf("\nPassword = ");
        scanf("%s", &newuser.userPassword );

        //username & email check
        for(int i = 0; i < user_count; i++){
            if(areStringsEqual(newuser.userName ,userdb[i].userName)) {
                printf("Username already exists. Please choose a different username.\n");
                if (areStringsEqual(newuser.userEmail, userdb[i].userEmail)) {
                    printf("Email already exists. Please choose a different email.\n");
                    return;
                }
                return;
            }
        }
        userdb[user_count] = newuser;
        printf("User Add Successfull.");
}

void userSession(char inputUsername[], char inputPassword[]){
    int choice = 0;
    int isSession = 1;
    while(isSession){
        printf("\t\tWelcome Sir. Your Logined as %s\n1. Logout\n2. Password\nInput Here : ",inputUsername);
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                isSession = 0;
                printf("GoodBy Sir...\tLogouted\n");
                break;
            case 2:
                printf("Your password is : %s\n", inputPassword);
                break;
            default:
                printf("Worng Choice ,Try Again Mr.%se...\n\n", inputUsername);

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
    for(int i = 0; i < (MAX_USERS - 1); i++){
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
                userSingup(userdb, user_count);
                user_count++;
                break;
            case 2:
                if(userLogin(userdb,inputUsername,inputPassword)){
                   userSession(inputUsername,inputPassword);
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