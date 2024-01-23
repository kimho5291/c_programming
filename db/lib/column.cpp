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
        int total = 0;
        condition* now = condHead;
        while(now != NULL){
            int array1[ARRAYMAX] = {'\0', };
            int array2[ARRAYMAX] = {'\0', };
            int arrIdx1 = 0, arrIdx2 = 0;

            condition* nowAnd = now;
            while(nowAnd != NULL){
                if(arrIdx1 == 0){
                    arrIdx1 = findIndex(array1, table, nowAnd);
                    printf("arrIdx1 : %d\n", arrIdx1);
                    if(arrIdx1 < 0) {
                        deleteAllCondition(condHead);
                        return -13;
                    }
                }else{
                    arrIdx2 = findIndex(array2, table, nowAnd);
                    if(arrIdx2 < 0) {
                        deleteAllCondition(condHead);
                        return -13;
                    }

                    arrIdx1 = intersection(array1, arrIdx1, array2, arrIdx2);

                    // memset(array2, 0, MAX); // index가 있어서 필요 없음
                    arrIdx2 = 0;
                }

                for(int i=0; i<arrIdx1; i++){
                    printf("11array[%d] : %d\n", i, array1[i]);
                }
                // reverse
                reverseArr(array1, arrIdx1);

                for(int i=0; i<arrIdx1; i++){
                    printf("22array[%d] : %d\n", i, array1[i]);
                }

                // row delete
                int re = 0;
                for(int i=0; i<arrIdx1; i++){
                    printf("array[%d] : %d\n", i, array1[i]);
                    re = deleteRow(table->column, array1[i]);
                    if(re < 0) {
                        printf("where delete error : [%d]\n", re);
                        deleteAllCondition(condHead);
                        return -13;
                    }
                }
                total += arrIdx1;

                nowAnd = nowAnd->nextAnd;
            }

            now = now->nextOr;
        }
        
        printf("## TABLE DELETE SUC [%d] !!\n", total);
    }

    printf("## TABLE [%s] DELETE SUC !!\n", table->name);

    return 1;
}

int findIndex(int* array, myTB* table, condition* node){
    int arrIndex = 0;

    int flag = 0;
    myCL* now = table->column;
    while(now != NULL){
        if(strcasecmp(now->name, node->col) == 0){
            flag = 1;

            // check data size
            if(strlen(node->val) > now->size){
                return -1;
            }
            // check data type
            if(strcasecmp(now->type, "char") == 0){
                if(node->oper >= GE && node->oper <= LT){
                    return -1;
                }
            }

            int tempIndex = 0;
            myDt* nowDT = now->data;
            while(nowDT != NULL){
                
                // check data type
                if(strcasecmp(now->type, "char") == 0){
                    //printf("[%d] %s==%s = %D\n", tempIndex, nowDT->data.c_value, node->val, strcasecmp(nowDT->data.c_value, node->val));
                    if(node->oper == EQ && strcasecmp(nowDT->data.c_value, node->val) == 0) array[arrIndex++] = tempIndex;
                    if(node->oper == NE && strcasecmp(nowDT->data.c_value, node->val) != 0) array[arrIndex++] = tempIndex;
                }else if(strcasecmp(now->type, "int") == 0){
                    int temp = atoi(nowDT->data.c_value);
                    if(isnan(temp)){
                        return -1;
                    }

                    if(node->oper == EQ && nowDT->data.i_value == atoi(node->val)) array[arrIndex++] = tempIndex;
                    if(node->oper == NE && nowDT->data.i_value != atoi(node->val)) array[arrIndex++] = tempIndex;
                    if(node->oper == GE && nowDT->data.i_value >= atoi(node->val)) array[arrIndex++] = tempIndex;
                    if(node->oper == LE && nowDT->data.i_value <= atoi(node->val)) array[arrIndex++] = tempIndex;
                    if(node->oper == GT && nowDT->data.i_value > atoi(node->val)) array[arrIndex++] = tempIndex;
                    if(node->oper == LT && nowDT->data.i_value < atoi(node->val)) array[arrIndex++] = tempIndex;
                }else{ // double
                    int temp = atoi(nowDT->data.c_value);
                    if(isnan(temp)){
                        return -1;
                    }
                    if(node->oper == EQ && nowDT->data.d_value == atof(node->val)) array[arrIndex++] = tempIndex;
                    if(node->oper == NE && nowDT->data.d_value != atof(node->val)) array[arrIndex++] = tempIndex;
                    if(node->oper == GE && nowDT->data.d_value >= atof(node->val)) array[arrIndex++] = tempIndex;
                    if(node->oper == LE && nowDT->data.d_value <= atof(node->val)) array[arrIndex++] = tempIndex;
                    if(node->oper == GT && nowDT->data.d_value > atof(node->val)) array[arrIndex++] = tempIndex;
                    if(node->oper == LT && nowDT->data.d_value < atof(node->val)) array[arrIndex++] = tempIndex;
                }

                ++tempIndex;
                nowDT = nowDT->next;
            }

        }
        now = now->next;
    }

    if(flag == 0) return -1;
    
    return arrIndex;
}

int intersection(int* array1, int arrIdx1, int* array2, int arrIdx2){

    int temp[1000] = {'\0', };
    int tempIdx = arrIdx1;
    for(int i=0; i<arrIdx1; i++){
        temp[i] = array1[i];
    }
    memset(array1, 0, ARRAYMAX);
    arrIdx1 = 0;

    for(int i=0; i<tempIdx; i++){
        for(int j=0; j<arrIdx2; j++){
            if(temp[i] == array2[j]) array1[arrIdx1++] = temp[i];
            break;
        }
    }

    return arrIdx1;
}

void reverseArr(int* array, int arrIdx){
    int mid = arrIdx/2;
    for(int i=0; i<mid; i++){
        int temp = array[i];
        array[i] = array[(arrIdx-1)-i];
        array[(arrIdx-1)-i] = temp;
    }
}

int deleteRow(myCL* column, int index){
    if(column == NULL) return 1;

    int re = deleteRow(column->next, index);
    if(re < 0) return re;

    if(column->data == NULL) return -1;

    if(index == 0){
        myDt* now = column->data;
        column->data = now->next;
        free(now);

    }else{
        myDt* now = column->data;
        myDt* pre = column->data; 
        int tempIndex = 0;
        while(now != NULL && tempIndex != index){
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