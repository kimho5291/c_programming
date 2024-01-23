#include "parser.h"


int judgeOper(char* cmd){
    char temp[100] = {'\0', };
    strcpy(temp, cmd);

    char* ptr = strtok(temp, " ");
    
    if(strcasecmp("SHOW", ptr) == 0) return opSHOW;
    if(strcasecmp("USE", ptr) == 0) return opUSE;
    if(strcasecmp("CREATE", ptr) == 0) return opCREATE;
    if(strcasecmp("DROP", ptr) == 0) return opDROP;
    if(strcasecmp("INSERT", ptr) == 0) return opINSERT;
    if(strcasecmp("UPDATE", ptr) == 0) return opUPDATE;
    if(strcasecmp("DELETE", ptr) == 0) return opDELETE;
    if(strcasecmp("SELECT", ptr) == 0) return opSELECT;
    if(strcasecmp("DESC", ptr) == 0) return opDESC;
    if(strcasecmp("EXIT", ptr) == 0) return opEXIT;

    return -1;
}

int judgeType(int oper, char* cmd){
    if(oper == opEXIT) return 0;

    char temp[100] = {'\0', };
    strcpy(temp, cmd);

    char* ptr = strtok(temp, " ");
    ptr = strtok(NULL, " ");

    if(oper == opSHOW){
        if(strcasecmp("USERS", ptr) == 0) return tpUSER;
        if(strcasecmp("DATABASES", ptr) == 0) return tpDATABASE;
        if(strcasecmp("TABLES", ptr) == 0) return tpTABLE;
    }

    if(oper == opUSE) return tpDATABASE;

    if(oper >= opCREATE && oper <= opDROP){
        if(strcasecmp("USER", ptr) == 0) return tpUSER;
        if(strcasecmp("DATABASE", ptr) == 0) return tpDATABASE;
        if(strcasecmp("TABLE", ptr) == 0) return tpTABLE;
    }

    if(oper >= opINSERT && oper <= opSELECT) {
        if(strcasecmp("TABLE", ptr) == 0) return tpTABLE;
    }
    if(oper == opDESC) {
        if(strcasecmp("TABLE", ptr) == 0) return tpTABLE;
    }

    return -1;
}

int checkSyntex(int oper, int type, char* cmd){
    if(oper == -1) return -1;
    if(type == -1) return -1;

    if(oper == opSHOW){
        if(countChar(cmd, ' ') != 1) return -1;
    }

    if(oper >= opCREATE && oper <= opDROP){
        if(type == tpUSER && countChar(cmd, ' ') != 3) return -1;
        else if(type == tpDATABASE && countChar(cmd, ' ') != 2) return -1;
        //if(type == tpTABLE) return tpTABLE;
    }

    return 0;
}

condition* parseWhere(char* cmd){
    condition* head = NULL;
    int logical = opNONE;
    // name=kims and age>=10
    char* ptr = strtok(cmd, " ");
    char* next = NULL;

    int idx = -1;
    while(ptr != NULL){
        // increase index
        ++idx;

        // printf("ptr : %s\n" ,ptr);

        // copy current cmd
        char temp[100] = {'\0', };
        strcpy(temp, ptr);

        // save next cmd
        next = strtok(NULL, "\n");

        // printf("idx : %d\n", idx);

        // check logical operator // if idx is odd number
        if(idx % 2 == 1){
            if(strcasecmp(ptr, "AND") == 0) logical = opAND;
            if(strcasecmp(ptr, "OR") == 0) logical = opOR;

            // printf("logical : [%d] %s\n", logical, ptr);

            if(logical == opNONE){
                deleteAllCondition(head);
                return NULL;
            }
            ptr = strtok(next, " ");
            continue;
        }

        // check relational operator
        int relational = checkOperator(ptr);
        // printf("relational : %d\n", relational);
        if(relational == NN) {
            deleteAllCondition(head);
            return NULL;
        };

        condition* newNode = (condition*)malloc(sizeof(condition));
        memset(newNode, 0, sizeof(condition));
        newNode->oper = relational;
        newNode->nextOr = NULL;
        newNode->nextOr = NULL;

        char* pptr = NULL;
        // column name
        if(relational == GT || relational == GE) pptr = strtok(temp, ">");
        if(relational == LT || relational == LE) pptr = strtok(temp, "<");
        if(relational == EQ) pptr = strtok(temp, "=");
        if(relational == NE) pptr = strtok(temp, "!");
        // printf("column name : %s\n", pptr);
        strcpy(newNode->col, pptr); // ex: name

        // skip relational operator and value
        if(relational >= NE && relational <= LE) pptr = strtok(NULL, "=");
        else pptr = strtok(NULL, " "); // ex: kims
        // printf("value : %s\n", pptr);
        strcpy(newNode->val, pptr);

        if(head == NULL){
            head = newNode;
        }else{
            condition* now = head;

            // find last orNode
            while(now->nextOr != NULL){
                now = now->nextOr;
            }

            if(logical == opOR){
                now->nextOr = newNode;
            }
            else if(logical == opAND){
                // find last and Node
                while(now->nextAnd != NULL){
                    now = now->nextAnd;
                }
                now->nextAnd = newNode;
            }

            logical = opNONE;
        }

        ptr = strtok(next, " ");
    }

    return head;
}

void printConditions(condition* node){
    if(node == NULL) return;
    printf("===================\n");
    printf("col : %s\n", node->col);
    printf("val : %s\n", node->val);
    printf("oper : %d\n", node->oper);
    printf("and : %p\n", node->nextAnd);
    printf("or : %p\n", node->nextOr);

    printConditions(node->nextAnd);
    printConditions(node->nextOr);
}

void deleteAllCondition(condition* node){
    if(node == NULL) return;
    deleteAllCondition(node->nextOr);
    deleteAllCondition(node->nextAnd);

    free(node);
    return;
}

int checkOperator(char* cmd){
    int eq = countChar(cmd, '=');
    int gt = countChar(cmd, '>');
    int lt = countChar(cmd, '<');
    int nt = countChar(cmd, '!');

    // kind of operator
    // =, !=, >, <, >=, <=

    if(eq > 0){
        if(nt > 0) return NE;
        if(gt > 0) return GE;
        if(lt > 0) return LE;
        return EQ;
    }

    if(gt > 0) return GT;
    if(lt > 0) return LT;

    return NN;
}

int countChar(char* cmd, char ch){
    int count = 0;
    for(int i=0; i<strlen(cmd); i++){
        if(cmd[i] == ch) count++;
    }
    return count;
}