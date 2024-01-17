#include "process.h"

void sysInit(){

    // file init
    initUser();

    // read file
    readUserFile();

}

bool login(char* id, char* pw){
    return checkUser(id, pw);
}


void process(){
    char* cmd = NULL;
    int type = -1, oper = -1;
    int re = 0;

    do{
        re = 0;
        free(cmd);
        cmd = getString();
        oper = judgeOper(cmd);
        type = judgeType(oper, cmd);

        if(checkSyntex(oper, type, cmd) < 0){
            printf("## Please check Command : %s\n", cmd);
            continue;
        }

        if(oper == opSHOW){
            if(type == tpUSER) showUser();
        }

        if(oper == opCREATE){
            if(type == tpUSER) re = createUser(cmd);
        }

        if(oper == opDROP){
            if(type == tpUSER) re = deleteUser(cmd);
        }

        if(re < 0){
            if(re == -1) printf("## The ID already exists : %s\n", cmd);
            if(re == -2) printf("## Please Check Id & PW : %s\n", cmd);
            if(re == -3) printf("## can't remove root : %s\n", cmd);
        }

    }while(oper != opEXIT);
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
