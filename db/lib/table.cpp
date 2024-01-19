#include "table.h"

myUser* tbUser = NULL;
myDB* tbDatabase = NULL;


void initTBUser(myUser* user){
    tbUser = user;
}

void initTBDatabase(myDB* db){
    tbDatabase = db;

    // 파일 읽기
    readTBFile();
}

int showTables(){
    if(tbDatabase == NULL) return -10;

    myTB* now = tbDatabase->table;
    int idx = 0;
    printf("## ----- Table List -----\n");
    while(now != NULL){
        printf("[%d] %s\n", idx++, now->name);
        now = now->next;
    }
    printf("## ----- Table List -----\n");
    return 1;
}

int descTable(char* cmd){
    if(tbDatabase == NULL) return -10;

    // desc [table name]
    char* ptr = strtok(cmd, " ");
    ptr = strtok(NULL, " ");

    ptr = strtok(NULL, " ");
    myTB* now = tbDatabase->table;

    while(now != NULL){
        if(strcmp(now->name, ptr) == 0){
            showColumns(now);
            return 1;
        }
        now = now->next;
    }

    return -7;
}

void createTB(char* line){

    // ex: [table name] [columns info]
    char* ptr = strtok(line, " ");

    char* name = (char*)malloc(sizeof(char) * strlen(ptr));
    strcpy(name, ptr);


    myTB* tb = (myTB*)malloc(sizeof(myTB));
    memset(tb, 0, sizeof(myTB));
    tb->name= name;
    tb->next = NULL;

    // create columns
    ptr = strtok(NULL, "\n");
    createCL(tb, ptr);

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
    if(tbDatabase == NULL) return -10;

    char temp[100] = {'\0', };
    strcpy(temp, cmd);

    // ex: create table [table name] [column info]
    char* ptr = strtok(temp, " ");
    ptr = strtok(NULL, " ");

    ptr = strtok(NULL, " ");
    char* name = (char*)malloc(strlen(ptr));
    strcpy(name, ptr);


    myTB* tb = (myTB*)malloc(sizeof(myTB));
    memset(tb, 0, sizeof(myTB));
    tb->name= name;
    tb->next = NULL;

    // create columns
    ptr = strtok(NULL, "\n");
    int re = createCL(tb, ptr);
    if(re < 0) {
        deleteAllCL(tb->column);
        free(name);
        free(tb);
        return re;
    }

    myTB* tbHead = tbDatabase->table;
    if(tbHead == NULL){
        tbDatabase->table = tb;
    }else{
        myTB* pre = tbHead;
        myTB* temp = tbHead;
        while(temp != NULL){
            if(strcmp(temp->name, tb->name) == 0){
                deleteAllCL(tb->column);
                free(name);
                free(tb);
                return -6;
            }
            pre = temp;
            temp = temp->next;
        }
        pre->next = tb;
    }

    createCLFile(tbUser, tbDatabase, tb);
    writeTBFile();
    //createDBDir(name);

    printf("## TABLE [%s] CREATE !!\n", name);
    return 1;
}

int dropTableCmd(char* cmd){

    char temp[100] = {'\0', };
    strcpy(temp, cmd);

    // ex: drop table [table name]
    char* ptr = strtok(temp, " ");
    ptr = strtok(NULL, " ");

    ptr = strtok(NULL, " ");
    char* name = (char*)malloc(sizeof(char) * strlen(ptr));
    strcpy(name, ptr);

    myTB* pre = tbDatabase->table;
    myTB* now = tbDatabase->table;

    while(now != NULL){
        if(strcmp(now->name, name) == 0){
            if(pre == tbDatabase->table) tbDatabase->table = now->next;
            else pre->next = now->next;

            deleteAllCL(now->column);
            removeCLFile(tbUser, tbDatabase, now);

            writeTBFile();
            printf("## TABLE [%s] DELETE !!\n", name);

            now->column = NULL;
            free(now->name);
            free(now);

            return 1;
        }
        pre = now;
        now = now->next;
    }

    return -7;
}

int insertTableCmd(char* cmd){
    

    return 1;
}

int selectTableCmd(char* cmd){
    return 1;
}

int updateTableCmd(char* cmd){
    return 1;
}

int deleteTableCmd(char* cmd){
    return 1;
}


int dropAllTB(myTB* node){
    if(node == NULL) return 1;
    dropAllTB(node->next);

    deleteAllCL(node->column);

    writeTBFile();
    // printf("## TABLE [%s] DELETE !!\n", node->name);

    node->column = NULL;
    free(node->name);
    free(node);

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

void writeTBFile(){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s/%s/%s", BASIC_DIR_PATH, tbUser->id, tbDatabase->name, TABLE_FILE_NAME);

    FILE* fp = fopen(path,"w");

    myTB* now = tbDatabase->table;

    while(now != NULL){
        char temp[200] = {'\0', };

        snprintf(temp, 200, "%s", now->name);
        myCL* nowCL = now->column;
        while(nowCL != NULL){
            snprintf(temp, 200, "%s %s,%s,%d", temp, nowCL->name, nowCL->type, nowCL->size);
            nowCL = nowCL->next;
        }
        snprintf(temp, 200, "%s\n", temp);

        fputs(temp,fp);
        now = now->next;
    }

    fclose(fp);
}
void readTBFile(){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s/%s/%s", BASIC_DIR_PATH, tbUser->id, tbDatabase->name, TABLE_FILE_NAME);

    FILE* fp= fopen(path, "r");

    char line[200] = {'\0', };
    while (fgets(line, sizeof(line), fp) != NULL ) {

        // [table name] [columns info]
        createTB(line);
	}

    fclose(fp);
}