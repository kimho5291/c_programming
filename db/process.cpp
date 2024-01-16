#include "process.h"

void sysInit(){

    // read file
    readUserFile();

}

bool login(char* id, char* pw){
    return checkUser(id, pw);
}


void process(){
    char* cmd = NULL;
    int type = -1, oper = -1;
    do{
        free(cmd);
        cmd = getString();
        //printf("cmd : %s\n", cmd);
        oper = judgeOper(cmd);
        //printf("oper : %d\n", oper);
        type = judgeType(oper, cmd);
        //printf("type : %d\n", type);

        if(oper == -1){
            printf("## Please check Command : %s\n", cmd);
            continue;
        }

        if(oper == opSHOW){
            if(type == tpUSER) showUser();
        }

        if(oper == opCREATE){
            if(type == tpUSER) createUser(cmd);
        }

    }while(oper != opEXIT);
}

int judgeOper(char* cmd){
    char* ptr = strtok(cmd, " ");
    
    if(strcasecmp("SHOW", ptr) == 0) return opSHOW;
    if(strcasecmp("CREATE", ptr) == 0) return opCREATE;
    if(strcasecmp("DROP", ptr) == 0) return opDROP;
    if(strcasecmp("INSERT", ptr) == 0) return opINSERT;
    if(strcasecmp("UPDATE", ptr) == 0) return opUPDATE;
    if(strcasecmp("DELETE", ptr) == 0) return opDELETE;
    if(strcasecmp("SELECT", ptr) == 0) return opSELECT;
    if(strcasecmp("EXIT", ptr) == 0) return opEXIT;

    return -1;
}

int judgeType(int oper, char* cmd){
    if(oper == opEXIT) return 0;

    char* temp = NULL;
    char* ptr = strtok_r(cmd, " ", &temp);
    ptr = strtok(NULL, " ");

    if(oper == opSHOW){
        if(strcasecmp("USERS", ptr) == 0) return tpUSER;
        if(strcasecmp("DATABASES", ptr) == 0) return tpDATABASE;
        if(strcasecmp("TABLES", ptr) == 0) return tpTABLE;
    }

    if(oper >= opCREATE && oper <= opDROP){
        if(strcasecmp("USER", ptr) == 0) return tpUSER;
        if(strcasecmp("DATABASE", ptr) == 0) return tpDATABASE;
        if(strcasecmp("TABLE", ptr) == 0) return tpTABLE;
    }

    if(oper >= opINSERT && oper <= opSELECT) return tpTABLE;

    return -1;
}



char* getString(){

    char temp[BUF_SIZE] = {'\0', };
    char ch = NULL;
    int idx = 0;

    do{
        ch = getchar();
        if(ch != '\n'){
            temp[idx++] = ch;
        }
    }while(ch != '\n' || idx == 0);

    char* array = (char*)malloc(sizeof(char) * idx);
    strncpy(array, temp, idx);

    return array;
}
