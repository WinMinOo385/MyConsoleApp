//User Management System Version 4.0
//fixed some bugs
//Added some features -> File DB, Email Valid, User Transcation Record and Admin User

#include <stdio.h>

#define MAX_USERS 20



struct UserDB {
    char userName[20];
    char userEmail[20];
    char userPassword[20];
    int id;
    int cryptoCurrency;

};

//Global Structure
struct UserDB userdb[MAX_USERS];

//declare Global Variable
int user_count;
char FileDB[12] = "database.txt";
char transcation_file[21] = "transcationRecord.txt";

//declare Function
int areStringsEqual(char str1[], char str2[]);
int username2Id( char inputUsername[]);
void userSession(int user_id);
int userLogin(char inputUsername[],char inputPassword[]);
int passwordCheck(char password[]);
int currencyTransfer( int senderID, int amountASM, char reciverAddress[]);
int email2Id( char inputEmail[]);
int id2index(int id);
int fline_count(const char file[]);
int emailCheck(char Email[]);
int importData(const char file[]);
int exportData(const char file[]);
int tranHistory(int id);



int userSingup(){
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
            printf("Password is Not Strong!!!!\nmust be contain \nPassphrase Length is least six\nAt least One Upper and Lower Letter, Number and Special Charater");
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
            } else if(emailCheck(newuser.userEmail)){
                printf("Invalid Email Address");
                return 0;
            }
        }
        newuser.id = user_count + 1;
        newuser.cryptoCurrency = 100;
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
                scanf("%s", &reciverAddress);
                printf("\nAmount To Transfer Point : ");
                scanf("%d", &amount2send);
                if(currencyTransfer(user_id,amount2send,reciverAddress)){
                    printf("Transaction Complete.\n");
                    exportData(FileDB);
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

void adminSession(int user_id){
    int choice = 0;
    int isSession = 1;
    while(isSession){
        printf("Welcome %s.\n1. User Account Management\n2. Transaction Record\n3. Logout\nInput Here : ", userdb[id2index(user_id)].userName);
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Comming Soon!");
                break;
            case 2:
                printf("Comming Soon!");
                break;
            case 3:
                isSession = 0;
                break;
            default:
                printf("Worng Choice ,Try Again Mr.%se...\n\n", userdb[id2index(user_id)].userName);
        }
    }
}

int userLogin(char inputUsername[],char inputPassword[]){
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


int username2Id( char inputUsername[]){
    for(int i = 0; i < user_count; i++){
        if(areStringsEqual(inputUsername, userdb[i].userName)){
            return userdb[i].id;
        };
    }
    return -1;//error code nothing
}

int email2Id( char inputEmail[]){
    for(int i = 0; i <= user_count; i++){
        if(areStringsEqual(inputEmail, userdb[i].userEmail)){
            return userdb[i].id;
        };
    }
    return -1;//error code nothing
}

int id2index(int id){
    for(int i = 0; i <= user_count; i++){
        if(id == userdb[i].id){
            return i;
        };
    }
    return -1;//error code nothing
}

int clength(char str[]){
    int length = 0;
    while(str[length] != '\0'){
        length++;
    };
    return length;
}

int passwordCheck(char password[]){
    int length = clength(password);

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
int emailCheck(char Email[]){
    int atCount = 0;
    int dotCount = 0;
    int index = 0;
    int elength = clength(Email);
    char email_first_part[20];
    char email_second_part[20];

    //Initialize all values  to '\0'
    for (int i = 0; i < sizeof(email_first_part); ++i) {
        email_first_part[i] = '\0';
        email_second_part[i] = '\0';

    }

    //Special Charater Check
    for(int i = 0; Email[i] != '\0'; i++){
        if(Email[i] == '.' ){
            dotCount++;
        }else if(Email[i] == '@') {
            atCount++;
        }else if((Email[i] >= 33 && Email[i] <= 47) || (Email[i] >= 58 && Email[i] <= 64) || (Email[i] >= 91 && Email[i] <= 96) || (Email[i] >= 123 && Email[i] <= 126)){
            return 1;
        }
    }

    //Allowed domain-mail data
    char gmail[11]={'@','g','m','a','i','l','.','c','o','m'};
    char yahoo[11]={'@','y','a','h','o','o','.','c','o','m'};
    char outlook[13]={'@','o','u','t','l','o','o','k','.','c','o','m'};
    char apple[11]={'@','a','p','p','l','e','.','c','o','m'};
    char n1c[11]={'@','n','1','c','.','c','o','m'};


    //email split
    for(index; Email[index] != '\0'; index++){
        if(Email[index] != '@'){
            email_first_part[index] = Email[index];
        }else{
            break;
        }
    }
    for(int i = 0; index < elength; i++, index++){
        email_second_part[i] = Email[index];
    }

    //Allowed email-domain check
    int g = areStringsEqual(email_second_part,gmail);
    int y = areStringsEqual(email_second_part,yahoo);
    int o = areStringsEqual(email_second_part,outlook);
    int a = areStringsEqual(email_second_part,apple);
    int n = areStringsEqual(email_second_part,n1c);

    if(atCount == 1 ) {
        if(g|y|o|a|n){
            return 0;
        }else{
            return 1;
        }
    }else{
        return 1;
    }
    //1 is invalid
    //0 is valid
}

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

    //transaction Record;
    FILE *fptr;
    fptr = fopen(transcation_file, "a");
    if(fptr == NULL){
        fptr = fopen(transcation_file, "w");
    }
    fprintf(fptr,"%s is transfered %d ASM to %s\n", userdb[id2index(senderID)].userName, amountASM, userdb[id2index(reciverID)].userName);
    fprintf(fptr,"%s is recived %d ASM from %s\n", userdb[id2index(reciverID)].userName, amountASM, userdb[id2index(senderID)].userName);
    fclose(fptr);
    return 1;
}

//File Handling Part
void adminAccCreate(const char file[]){
    FILE *fptr;
    fptr = fopen(file, "w");
    fprintf(fptr,"%d %s %s %s %d\n", 1 , "Administrator", "admin@gmail.com", "R0tartsinimda", 0);
    fprintf(fptr,"%d %s %s %s %d\n", 2 , "owner", "owner@n1c.com", "0wN3rR", 0);
    fprintf(fptr,"%d %s %s %s %d\n", 3 , "soc", "soc@gmail.com", "qwert1234@A", 0);
    fclose(fptr);
}
int fline_count(const char file[]){
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL) {
        return 0;
    }
    char line[256]; // Assuming a fixed maximum length for each line
    int lineNumber = 0;

    while (fgets(line, sizeof(line), fptr) != NULL) {
        lineNumber++;
    }
    fclose(fptr);
    return lineNumber;
}

int importData(const char file[]){
    int i = 0;
    struct UserDB importuser;
    FILE *fptr;
    fptr = fopen(file, "r");
    if(fptr == NULL){
        perror("Database File Is Not Have\nSo. Created New Database File.\n");
        adminAccCreate(file);
        user_count = fline_count(FileDB);//global user Count
    }
    fptr = fopen(file, "r");
    while ( i < user_count){
        fscanf(fptr, "%d %s %s %s %d", &importuser.id, &importuser.userName, &importuser.userEmail, &importuser.userPassword, &importuser.cryptoCurrency);
        userdb[i] = importuser;
        i++;
    }
    fclose(fptr);
    return 0;
}

int exportData(const char file[]){
    FILE *fptr;
    fptr = fopen(file, "w");
    if(fptr == NULL){
        perror("File openning fail!");
        return -1;
    } else {
        for(int i = 0; i < user_count; i++){
            fprintf(fptr, "%d %s %s %s %d\n", userdb[i].id, userdb[i].userName,userdb[i].userEmail, userdb[i].userPassword, userdb[i].cryptoCurrency);
        }
        fclose(fptr);
    }
    return 0;
}

int tranHistory(int id){
    int userindex = id2index(id);

    FILE *fptr;
    fptr = fopen(transcation_file, "r");
    char line[100];  // Assume each line is at most 100 characters
    if(fptr == NULL){
        fptr = fopen(transcation_file, "w");
        fclose(fptr);
        return 0;
    }
    while (fgets(line, sizeof(line), fptr) != NULL) {
        int i = 0;
        char userName[20];

        //clearing userName variable
        for(int i = 0; i < sizeof(userName); i++){
            userName[i] = '\0';
        }

        while(line[i] != ' '){
            userName[i] = line[i];
            i++;
        }
        //output only session user
        if(areStringsEqual(userName, userdb[userindex].userName)){
            printf("%s", line);
        }
    }

}



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
                exit = 0;
                break;
            default:
                printf("Wrong Choice.Try Again");
                break;
        }
    }
    return 0;
}