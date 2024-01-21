#include "column.h"

void showColumns(myTB* table){
    myCL* now = table->column;
    int idx = 0;
    printf("## ----- DESC Columns -----\n");
    printf("      name  |  type  |   size\n");
    while(now != NULL){
        printf("[%d]  %s  |  %s  |  %d\n", idx++, now->name, now->type, now->size);
        now = now->next;
    }
    printf("## ----- DESC Columns -----\n");
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
            myCL* pre = table->column;
            myCL* now = table->column;
            while(now != NULL){
                if(strcmp(now->name, name) == 0){
                    free(name);
                    free(tempCL);
                    return -8;
                }
                pre = now;
                now = now->next;
            }
            pre->next = tempCL;
        }

        ptr = strtok(next, " ");
    }

    return 1;
}

int insertData(myTB* table, char* cmd){

    /*
    1. parse data -> check data -> data stored in list -> check number of data
    2. check number of columns in table
    3. if the number of colmuns and nimber of data match we continue, 
        otherwise an error code is returned after data memory is freed
    */

    // cmd ex: kim 20
    char line[100] = {'\0', };
    strcpy(line, cmd);

    char* ptr = strtok(line, " ");
    myDt* tempHead = NULL;
    while(ptr != NULL){
        char* tempChar = (char*)malloc(sizeof(strlen(ptr)));
        strcpy(tempChar, ptr);
        myDt* temp = (myDt*)malloc(sizeof(myDt));
        temp->data = (Data*)malloc(sizeof(Data));
        temp->data.c_value = tempChar;
        temp->nextNULL;

        if(tempHead == NULL){
            tempHead = temp;
        }else{
            myDt* now = tempHead;
            while(now->next != NULL){
                now = now->next;
            }
            now->next = temp;
        }

        ptr = strtok(NULL, " ");
    }

    // check that both column and data match
    myCL* now = table->column;
    while(now!=NULL){

        now = now->next;
    }


    return 1;
}

int deleteAllCL(myCL* node){
    if(node == NULL) return 1;
    int re = deleteAllCL(node->next);

    // delete all data

    node->data = NULL;
    node->next = NULL;
    free(node->name);
    free(node);

    return 1;
}


void createCLFile(myUser* user, myDB* db, myTB* tb){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s/%s/%s", BASIC_DIR_PATH, user->id, db->name, tb->name);

    bool re = createDF(path, TYPE_F);
}

void removeCLFile(myUser* user, myDB* db, myTB* tb){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s/%s/%s", BASIC_DIR_PATH, user->id, db->name, tb->name);
    bool re = removeDF(path);
    //printf("## UserDir : %d\n", re);
}