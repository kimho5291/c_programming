#include "database.h"

myDB* selDatabase = NULL;


void showDatabase(){
    myDB* now = selUser->db;
    int idx = 0;
    printf("## ----- DB List -----\n");
    while(now != NULL){
        printf("[%d] %s\n", idx++, now->name);
        now = now->next;
    }
    printf("## ----- DB List -----\n");
}

int useDatabase(char* cmd){
    char temp[100] = {'\0', };
    strcpy(temp, cmd);

    // ex: use [database name]
    char* ptr = strtok(temp, " ");
    ptr = strtok(NULL, " ");

    char* name = (char*)malloc(sizeof(char) * strlen(ptr));
    strcpy(name, ptr);

    myDB* dbHead = selUser->db;
    myDB* now = dbHead;
    while(now != NULL){
        if(strcmp(now->name, name) == 0){
            selDatabase = now;
            return 1;
        }
        now = now->next;
    }

    return -1;

}

void createDatabase(char* name){

    char* temp = (char*)malloc(sizeof(char) * strlen(name));
    strcpy(temp, name);

    myDB* db = (myDB*)malloc(sizeof(myDB));
    memset(db, 0, sizeof(myDB));
    db->name = temp;
    db->next = NULL;
    db->table = NULL;

    myDB* dbHead = selUser->db;
    if(dbHead == NULL){
        dbHead = db;
    }else{
        myDB* temp = dbHead;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = db;
    }

    //printf("## DB [%s] CREATE !!\n", name);
}


int createDatabase(char* cmd){
    char temp[100] = {'\0', };
    strcpy(temp, cmd);

    // ex: create database [database name]
    char* ptr = strtok(temp, " ");
    ptr = strtok(NULL, " ");

    ptr = strtok(NULL, " ");
    char* name = (char*)malloc(sizeof(char) * strlen(ptr));
    strcpy(name, ptr);

    myDB* db = (myDB*)malloc(sizeof(myDB));
    memset(db, 0, sizeof(myDB));
    db->name = name;
    db->next = NULL;
    db->table = NULL;

    myDB* dbHead = selUser->db;
    if(dbHead == NULL){
        dbHead = db;
    }else{
        myDB* temp = dbHead;
        do{
            if(strcmp(temp->name, name) == 0){
                free(db);
                free(name);
                return -1;
            }
            temp = temp->next;
        }while(temp->next != NULL);
        temp->next = db;
    }

    printf("## DB [%s] CREATE !!\n", name);
    return 1;
}