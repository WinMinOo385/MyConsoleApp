#ifndef C_GENERAL_H
#define C_GENERAL_H

#include "stdio.h"
#include "admin.h"

#define MAX_USERS 20

struct tranRecord {
    char tranHistory[200];
};

typedef struct  {
    char userName[20];
    char userEmail[20];
    char userPassword[20];
    int id;
    int cryptoCurrency;
    int tranCount;
    struct tranRecord tran[100];
    int isBanned; // Flag to indicate if the user is banned (1 for banned, 0 for not banned)
    int isSuspended;
    float userPhone;

}UserDB;

//Global Structure
UserDB userdb[MAX_USERS];

//declare Global Variable
int user_count;
char FileDB[12] = "database.txt";

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
void tranHistory(int id);
void adminAccCreate(const char file[]);
char* getCurrentTime();
int flength(float value);
int spaceDetect(char str[]);

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

int clength(char str[]){//char length
    int length = 0;
    while(str[length] != '\0'){
        length++;
    };
    return length;
}

int flength(float num) {
    int length = 0;
    char str[100];
    sprintf(str, "%.0f", num);

    int i = 0;
    while (str[i] != '\0' && str[i] != '.') {
        length++;
        i++;
    }

    return length;
}

int cspaceDetect(char str[]){
    int i;
    while( str[i] != '\0'){
        if(str[i] == ' '){
            return 0;//fail
        }
        i++;
    }
    return 1;//pass
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

int emailCheck(char Email[]){//email Valid Check
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
    FILE *fptr;
    fptr = fopen(file, "r");
    if(fptr == NULL){
        perror("Database File Is Not Have\nSo. Created New Database File.\n");
        adminAccCreate(file);
        user_count = fline_count(FileDB);//global user Count
    }
    fptr = fopen(file, "r");
    while ( i < user_count){
        fscanf(fptr, "%d %s %s %s %f %d %d %d %d", &userdb[i].id, &userdb[i].userName, &userdb[i].userEmail, &userdb[i].userPassword, &userdb[i].userPhone, &userdb[i].cryptoCurrency, &userdb[i].tranCount, &userdb[i].isBanned, &userdb[i].isSuspended);
        for (int e = 0;e < userdb[i].tranCount;e++){
            fscanf(fptr, "%s", &userdb[i].tran[e].tranHistory);
        }
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
            fprintf(fptr, "%d %s %s %s %f %d %d %d %d", userdb[i].id, userdb[i].userName,userdb[i].userEmail, userdb[i].userPassword, userdb[i].userPhone, userdb[i].cryptoCurrency, userdb[i].tranCount, userdb[i].isBanned, userdb[i].isSuspended);
            for(int a=0; a<userdb[i].tranCount; a++){
                fprintf(fptr,"%c%s",' ',userdb[i].tran[a].tranHistory);
            }
            fprintf(fptr,"%c",'\n');
        }
        fclose(fptr);
    }
    return 0;
}

char* getCurrentTime() {
    // Open a pipe to execute the date command and read its output
    FILE *pipe = popen("date", "r");
    if (pipe == NULL) {
        printf("Error: Failed to open pipe.\n");
        return NULL;
    }


    //Read the output of the date command.
    static char buffer[128]; // Make the buffer static so it persists after the function returns
    fgets(buffer, sizeof(buffer), pipe);

    //Extract the day, month, date, time, year, and timezone from the output
    char day[4], month[4], date[3], time[10], ampm[3], timezone[8], year[5];
    sscanf(buffer, "%s %s %s %s %s %s %s %s", day, month, date, time, ampm, timezone, year);

    //Format the time into the buffer
    snprintf(buffer, sizeof(buffer), "%s-%s-%s-%s%s-%s-%s", day, month, date, time, ampm, timezone, year);

    //Close
    pclose(pipe);

    //Return the formatted time
    return buffer;
}

int isValidPhoneNumber(float phonenumber) {
    //length Check
    int PhoneLength = flength(phonenumber);
    if(PhoneLength < 14 && PhoneLength > 4){
        return 1;//is vaild
    }
    return 0;//not vaild

}

#endif //C_GENERAL_H
