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
    int dataCount = 0;
    while(ptr != NULL){
        dataCount++;

        char* tempChar = (char*)malloc(sizeof(strlen(ptr)));
        strcpy(tempChar, ptr);
        myDt* temp = (myDt*)malloc(sizeof(myDt));
        temp->data.c_value = tempChar;
        temp->next = NULL;

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
    int columnCount = 0;
    while(now!=NULL){
        columnCount++;
        now = now->next;
    }

    if(dataCount != columnCount){
        while(tempHead != NULL){
            myDt* temp = tempHead;
            tempHead = tempHead->next;
            free(temp);
        }
        return -9;
    }

    now = table->column;
    myDt* nowDt = tempHead;
    while(now!=NULL){

        if(strcasecmp(now->type, "char") == 0 ){
            //printf("char : %s\n", nowDt->data->data.c_value);
        }
        else if(strcasecmp(now->type, "int") == 0 ){
            if(strlen(nowDt->data.c_value) > now->size){
                return -11;
            }
            int temp = atoi(nowDt->data.c_value);
            if(isnan(temp)){
                return -11;
            }

            free(nowDt->data.c_value);
            nowDt->data.i_value = temp;
            //printf("int : %d\n", nowDt->data->data.i_value);
        }
        else if(strcasecmp(now->type, "float") == 0 ){
            if(strlen(nowDt->data.c_value) > now->size){
                return -11;
            }

            double temp = atof(nowDt->data.c_value);
            if(isnan(temp)){
                return -11;
            }

            free(nowDt->data.c_value);
            nowDt->data.d_value = temp;
            //printf("double : %f\n", nowDt->data->data.d_value);
        }
        else{
            return -11;
        }

        myDt* tempDT = now->data;
        now->data = nowDt;

        nowDt = nowDt->next;

        now->data->next = tempDT;
        now = now->next;
    }

    printf("## TABLE [%s] INSERT SUC !!\n", table->name);

    // testPrintData(table);

    return 1;
}

int deleteData(myTB* table, char* cmd){

    // cmd ex: where name=kims or(and) name=kkk
    char line[100] = {'\0', };

    if(cmd != NULL){
        strcpy(line, cmd);
    }

    if(cmd == NULL || strlen(line) < 5){
        myCL* now = table->column;
        while(now != NULL){
            int re = deleteAllDT(now->data);
            now->data = NULL;

            now = now->next;
        }
    }else{
        printf("line : %s\n", line);
        char* ptr = strtok(line, " "); // where
        if(strcasecmp(ptr, "where") != 0) return -12;

        // parse conditions
        ptr = strtok(NULL, "\n");
        condition* condHead = parseWhere(ptr);

        // printConditions(condHead);

        // delete the data after finding data that meets the conditions
        myCL* nowCL = table->column;
        while(nowCL != NULL){

            int index = 0;
            myDt* nowDT = nowCL->data;
            while(nowDT != NULL){

                // check condition

                
                ++index;
                nowDT = nowDT->next;
            }

            nowCL = nowCL->next;
        }

    }

    printf("## TABLE [%s] DELETE SUC !!\n", table->name);

    return 1;
}

int deleteRow(myCL* column, int index){
    if(column->data == NULL) return -1;

    if(index == 0){
        myDt* now = column->data;
        column->data->next = now->next;
        free(now);

    }else{
        myDt* now = column->data;
        myDt* pre = column->data; 
        int tempIndex = 0;
        while(now != NULL || tempIndex != index){
            pre = now;
            now = now->next;
            ++tempIndex;
        }
        if(tempIndex != index) return -2;

        pre->next = now->next;
        free(now);
    }

    return 1;
}

int deleteAllCL(myCL* node){
    if(node == NULL) return 1;
    int re = deleteAllCL(node->next);

    // delete all data
    re = deleteAllDT(node->data);

    node->data = NULL;
    node->next = NULL;
    free(node->name);
    free(node);

    return 1;
}

int deleteAllDT(myDt* data){
    if(data == NULL) return 1;
    int re = deleteAllDT(data->next);

    // free(data->data.c_value);
    data->next = NULL;

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

void writeDTFile(myUser* user, myDB* db, myTB* tb){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s/%s/%s", BASIC_DIR_PATH, user->id, db->name, tb->name);

    FILE* fp = fopen(path,"w");

    myCL* nowCL = tb->column;

    while(nowCL != NULL){

        myDt* nowDt = nowCL->data;
        while(nowDt != NULL){
            char temp[200] = {'\0', };
            if(strcasecmp(nowCL->type,"char") == 0){
                snprintf(temp, 200, "%s%s ", temp, nowDt->data.c_value);
            }
            else if(strcasecmp(nowCL->type, "int") == 0 ){
                snprintf(temp, 200, "%s%d ", temp, nowDt->data.i_value);
            }
            else if(strcasecmp(nowCL->type, "int") == 0 ){
                snprintf(temp, 200, "%s%f ", temp, nowDt->data.d_value);
            }
            fputs(temp,fp);

            nowDt = nowDt->next;
        }
        fputs("\n",fp);

        nowCL = nowCL->next;
    }

    fclose(fp);
}

void readDTFile(myUser* user, myDB* db){

    myTB* tb = db->table;
    while(tb != NULL){

        char path[100] = {'\0', };
        snprintf(path, 100, "%s/%s/%s/%s", BASIC_DIR_PATH, user->id, db->name, tb->name);

        FILE* fp= fopen(path, "r");

        char line[2000] = {'\0', };
        myCL* nowCL = tb->column;
        myDt* preDT = NULL;
        myDt* nowDT = NULL;
        while (fgets(line, sizeof(line), fp) != NULL ) {
            char* ptr = strtok(line, " ");
            //printf("ptr : %s \n", ptr);

            while(ptr != NULL && ptr[0] != '\0' && ptr[0] != '\n'){
                nowDT = (myDt*)malloc(sizeof(myDt));
                nowDT->next = NULL;
                if(strcasecmp(nowCL->type,"char") == 0){
                    char* temp = (char*)malloc(strlen(ptr));
                    strcpy(temp, ptr);
                    nowDT->data.c_value = temp;
                    // printf("[char]data: %s\n", nowDT->data.c_value);
                }
                else if(strcasecmp(nowCL->type, "int") == 0 ){
                    nowDT->data.i_value = atoi(ptr);
                    // printf("[int]data: %d\n", nowDT->data.i_value);
                }
                else if(strcasecmp(nowCL->type, "int") == 0 ){
                    nowDT->data.d_value = atof(ptr);
                    // printf("[double]data: %f\n", nowDT->data.d_value);
                }

                if(nowCL->data == NULL) {
                    nowCL->data = nowDT;
                    preDT = nowDT;
                }
                else preDT->next = nowDT;

                preDT = nowDT;
                ptr = strtok(NULL, " ");
            }
            nowCL = nowCL->next;
        }

        fclose(fp);

        tb = tb->next;
    }
}


void testPrintData(myTB* table){
    printf("## TEST Print START ------- ##\n");
    myCL* printCL = table->column;
    while(printCL != NULL){
        myDt* printDT = printCL->data;
        while(printDT != NULL){
            char temp[200] = {'\0', };
            printf("printCL->type : %s\n", printCL->type);
            if(strcmp(printCL->type, "char") == 0){
                printf("[char] ");
                snprintf(temp, 200, "%s %s", temp, printDT->data.c_value);
            }
            else if(strcmp(printCL->type, "int") == 0 ){
                printf("[int] ");
                snprintf(temp, 200, "%s %d", temp, printDT->data.i_value);
            }
            else if(strcmp(printCL->type, "double") == 0 ){
                printf("[double] ");
                snprintf(temp, 200, "%s %f", temp, printDT->data.d_value);
            }
            printf("data: %s\n", temp);
            printDT = printDT->next;
        }
        printCL = printCL->next;
    }
    printf("## TEST Print END ------- ##\n");
}