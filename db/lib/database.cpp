#include "database.h"

myDB* selDatabase = NULL;
myUser* sUser = NULL;
tbDelFunction tbCallback = NULL;

void setTBDelCallback(tbDelFunction cb){
    tbCallback = cb;
}

void initDatabase(myUser* selUser){
    sUser = selUser;


    readDBFile();

}


void showDatabase(){
    myDB* now = sUser->db;
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

    myDB* dbHead = sUser->db;

    myDB* now = dbHead;
    while(now != NULL){
        if(strcmp(now->name, name) == 0){
            selDatabase = now;
            printf("## USE [%s] DATABASE  !! \n", name);
            free(name);
            return 1;
        }
        now = now->next;
    }
    free(name);
    return -4;

}

void createDatabase(char* name){

    char* temp = (char*)malloc(sizeof(char) * strlen(name));
    strcpy(temp, name);

    myDB* db = (myDB*)malloc(sizeof(myDB));
    memset(db, 0, sizeof(myDB));
    db->name = temp;
    db->next = NULL;
    db->table = NULL;

    myDB* dbHead = sUser->db;
    if(dbHead == NULL){
        sUser->db = db;
    }else{
        myDB* temp = dbHead;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = db;
    }

    //printf("## DB [%s] CREATE !!\n", name);
}


int createDatabaseCmd(char* cmd){

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

    myDB* dbHead = sUser->db;
    if(dbHead == NULL){
        sUser->db = db;
    }else{
        myDB* pre = dbHead;
        myDB* temp = dbHead;
        while(temp != NULL){
            if(strcmp(temp->name, name) == 0){
                free(db);
                free(name);
                return -1;
            }
            pre = temp;
            temp = temp->next;
        }
        pre->next = db;
    }


    writeDBFile();
    createDBDir(name);

    printf("## DB [%s] CREATE !!\n", name);
    return 1;
}

int deleteDBCmd(char* cmd){

    char temp[100] = {'\0', };
    strcpy(temp, cmd);

    // ex: drop database [database name]
    char* ptr = strtok(temp, " ");
    ptr = strtok(NULL, " ");

    ptr = strtok(NULL, " ");
    char* name = (char*)malloc(sizeof(char) * strlen(ptr));
    strcpy(name, ptr);

    myDB* pre = sUser->db;
    myDB* now = sUser->db;

    while(now != NULL){
        if(strcmp(now->name, name) == 0){
            if(pre == sUser->db) sUser->db = now->next;
            else pre->next = now->next;

            if(tbCallback != NULL)  tbCallback(now->table);

            writeDBFile();
            deleteDBDir(name);
            printf("## DATABASE [%s] DELETE !!\n", name);

            now->table = NULL;
            free(name);
            free(now->name);
            free(now);
            

            return 1;
        }
        pre = now;
        now = now->next;
    }

    free(name);

    return -4;
}


int deleteDBAll(myDB* node){

    if(node == NULL) return 1;
    int re = deleteDBAll(node->next);

    tbCallback(node->table);

    writeDBFile();
    deleteDBDir(node->name);
    // printf("## DATABASE [%s] DELETE !!\n", node->name);

    node->table = NULL;
    free(node->name);
    free(node);

    return 1;
}

void createDBDir(char* name){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s/%s", BASIC_DIR_PATH, sUser->id, name);

    bool re = createDF(path, TYPE_D);
    // printf("## UserFile : %d\n", re);
}

void createDBFile(char* cmd){

    char temp[100] = {'\0', };
    strcpy(temp, cmd);

    // ex: create user kkk 1234
    char* ptr = strtok(temp, " ");
    ptr = strtok(NULL, " ");

    ptr = strtok(NULL, " ");

    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s/%s", BASIC_DIR_PATH, ptr, DATABASE_FILE_NAME);

    bool re = createDF(path, TYPE_F);
    // printf("## UserFile : %d\n", re);
}

void deleteDBDir(char* name){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s/%s", BASIC_DIR_PATH, sUser->id, name);
    bool re = dirAllDel(path);
    //printf("## UserDir : %d\n", re);
}


void writeDBFile(){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s/%s", BASIC_DIR_PATH, sUser->id, DATABASE_FILE_NAME);

    FILE* fp = fopen(path,"w");

    myDB* now = sUser->db;
    while(now != NULL){
        char temp[100] = {'\0', };
        snprintf(temp, 100, "%s\n", now->name);
        fputs(temp,fp);
        now = now->next;
    }

    fclose(fp);
}

void readDBFile(){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s/%s", BASIC_DIR_PATH, sUser->id, DATABASE_FILE_NAME);

    FILE* fp= fopen(path, "r");

    char line[100] = {'\0', };
    while (fgets(line, sizeof(line), fp) != NULL ) {

        char* ptr = strtok(line, "\n");
        char* name = ptr;

		createDatabase(name);
	}

    fclose(fp);
}