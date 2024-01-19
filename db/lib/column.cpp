#include "column.h"

void showColumns(myTB* table){
    myCL* now = table->column;
    int idx = 0;
    printf("   name \t type \t size\n");
    while(now != NULL){
        printf("[%d]%s \t %s \t %d\n", idx++, now->name, now->type, now->size);
        now = now->next;
    }
}

int createCL(myTB* table, char* cmd){

    char* ptr = strtok(cmd, " ");
    while(ptr != NULL){

        char temp[100] = {'\0', };
        strcpy(temp, ptr);

        char* next = strtok(NULL, "\n");

        myCL* tempCL = (myCL*)malloc(sizeof(myCL));
        memset(tempCL, 0, sizeof(myCL));
        tempCL->next = NULL;
        tempCL->data = NULL;

        char* colPtr = strtok(temp, ",");
        char* name = (char*)malloc(strlen(colPtr));
        strcpy(name, colPtr);
        tempCL->name = name;

        colPtr = strtok(NULL, ",");
        strcpy(tempCL->type, colPtr);

        colPtr = strtok(NULL, ",");
        tempCL->size = atoi(colPtr);

        if(table->column == NULL){
            table->column = tempCL;
        }else{
            myCL* now = table->column;
            while(now->next != NULL){
                now = now->next;
            }
            now->next = tempCL;
        }

        ptr = strtok(next, " ");
    }

    return 1;
}


void createCLFile(myUser* user, myDB* db, myTB* tb){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s/%s/%s", BASIC_DIR_PATH, user->id, db->name, tb->name);

    bool re = createDF(path, TYPE_F);
}