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