#include "table.h"

myUser* tbUser = NULL;
myDB* tbDatabase = NULL;


void initTBUser(myUser* user){
    tbUser = user;
}

void initTBDatabase(myDB* db){
    tbDatabase = db;

    // 파일 읽기

}

void showTables(){
    myTB* now = tbDatabase->table;
    int idx = 0;
    printf("## ----- Table List -----\n");
    while(now != NULL){
        printf("[%d] %s\n", idx++, now->name);
        now = now->next;
    }
    printf("## ----- Table List -----\n");
}

void createTB(char* name){

    char* temp = (char*)malloc(sizeof(char) * strlen(name));
    strcpy(temp, name);

    myTB* tb = (myTB*)malloc(sizeof(myTB));
    memset(tb, 0, sizeof(myTB));
    tb->name= temp;
    tb->next = NULL;
    tb->column = NULL;

    myTB* tbHead = tbDatabase->table;
    if(tbHead == NULL){
        tbDatabase->table = tb;
    }else{
        myTB* temp = tbHead;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = tb;
    }
}

int createTBCmd(char* cmd){
    char temp[100] = {'\0', };
    strcpy(temp, cmd);

    // ex: create table [table name] //[column info]
    char* ptr = strtok(temp, " ");
    ptr = strtok(NULL, " ");

    ptr = strtok(NULL, " ");
    char name[100] = {'\0', };
    strcpy(name, ptr);

    myTB* tb = (myTB*)malloc(sizeof(myTB));
    memset(tb, 0, sizeof(myTB));
    tb->name= name;
    tb->next = NULL;
    tb->column = NULL;

    myTB* tbHead = tbDatabase->table;
    if(tbHead == NULL){
        tbDatabase->table = tb;
    }else{
        myTB* temp = tbHead;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = tb;
    }

    //writeDBFile();
    //createDBDir(name);

    printf("## TABLE [%s] CREATE !!\n", name);
    return 1;
}

void createTBFile(char* cmd){
    char temp[100] = {'\0', };
    strcpy(temp, cmd);

    // ex: create database kkk
    char* ptr = strtok(temp, " ");
    ptr = strtok(NULL, " ");

    ptr = strtok(NULL, " "); // db name

    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s/%s/%s", BASIC_DIR_PATH, tbUser->id, ptr, TABLE_FILE_NAME);

    //printf("path : %s\n", path);

    bool re = createDF(path, TYPE_F);
    // printf("## UserFile : %d\n", re);
}