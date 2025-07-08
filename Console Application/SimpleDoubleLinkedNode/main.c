#include "stdio.h"
#include "stdlib.h"


struct Node{
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node* creaateNode(int data);
void linkNode(struct Node** head,int data);
void printNodefroward(struct Node* node);
void printNodeBackward(struct Node* node);
void deleNode(struct Node** head, int key);

struct Node * createNode(int data){
    struct Node* temp;
    temp = (struct Node*) malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;

}

void linkNode(struct Node** head,int data){
    struct Node*linkNode = createNode(data);
    linkNode->next = *head;
    if( *head != NULL){
        (*head)->prev = linkNode;
    }
    *head = linkNode;
}

void printNodefroward(struct Node* node){
    while( node != NULL){
        printf("DATA Forward : %d\n",node->data);
        node = node->next;
    }
}

void printNodeBackward(struct Node* node){
    struct Node* edon;
    while(node != NULL){
        edon = node;
        node = node->next;
    }
    while(edon != NULL){
        printf("DATA Backward : %d\n",edon->data);
        edon = edon->prev;
    }
}
void deleNode(struct Node** head, int key){
    struct Node * temp, *prev;
    temp = *head;

    if( temp != NULL && temp->data == key){
        temp->next->prev = NULL;
        *head = temp->next;
        free(temp);
        return;
    }

    while( temp != NULL && temp->data != key){
        prev = temp;
        temp = temp->next;
    }

    if( temp == NULL)return;

    prev->next = temp->next;
    temp->next->prev = temp->prev;


}

int main(){
    struct Node *head;
    int exit = 1;
    while(exit){
        int choice = 0;
        printf("\t\tSimple Double Linked Node Program\n1. Insert Data\n2. Data Print Forward\n3. Data Print Backward\n4. Delete Data\n5. Exit\nEnter Option [1-5] : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:;
                int count = 0;
                printf("Data Count : ");
                scanf("%d", &count);
                for(int i = 0; i < count;i++){
                    int number = 0;
                    printf("Enter A Number : ");
                    scanf("%d", &number);
                    linkNode(&head,number);
                }
                break;
            case 2:
                printNodefroward(head);
                break;
            case 3:
                printNodeBackward(head);
                break;
            case 4:;
                int toDelete = 0;
                printf("Enter Data To Delete : ");
                scanf("%d", &toDelete);
                deleNode(&head,toDelete);
                break;
            case 5:
                printf("Good Bye, See Ya!");
                exit = 0;
                break;
            default:
                printf("Wrong Option Choice!\n");
        }
    }
    return 0;
}