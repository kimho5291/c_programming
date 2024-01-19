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

    if(oper >= opINSERT && oper <= opSELECT) return tpTABLE;
    if(oper == opDESC) return tpTABLE;

    return -1;
}

int checkSyntex(int oper, int type, char* cmd){
    if(oper == -1) return -1;

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

int countChar(char* cmd, char ch){
    int count = 0;
    for(int i=0; i<strlen(cmd); i++){
        if(cmd[i] == ch) count++;
    }
    return count;
}