#include "process.h"

void sysInit(){

    // file init
    initUser();

    // read file
    readUserFile();

    setDBDelCallback(deleteDBAll);
    setTBDelCallback(dropAllTB);

}

bool login(char* id, char* pw){

    bool re = checkUser(id, pw);
    if(re) {
        initDatabase(selUser);
        initTBUser(selUser);
    }
    
    return re;
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

        // printf("oper: %d | type : %d\n", oper, type);

        if(checkSyntex(oper, type, cmd) < 0){
            printf("## Please check Command : %s\n", cmd);
            continue;
        }

        if(oper == opSHOW){
            if(type == tpUSER) showUser();
            if(type == tpDATABASE) showDatabase();
            if(type == tpTABLE) re = showTables();
        }

        if(oper == opUSE){
            if(type == tpDATABASE) {
                re = useDatabase(cmd);
                if(re > 0) initTBDatabase(selDatabase);
            }
        }

        if(oper == opCREATE){

            if(type == tpUSER) {
                re = createUserCmd(cmd);
                if(re > 0) createDBFile(cmd);
            }
            if(type == tpDATABASE) {
                re = createDatabaseCmd(cmd);
                if(re > 0) createTBFile(cmd);
            }
            if(type == tpTABLE) {
                re = createTBCmd(cmd);
            }
        }

        if(oper == opDROP){
            if(type == tpUSER) re = deleteUserCmd(cmd);
            if(type == tpDATABASE) re = deleteDBCmd(cmd);
            if(type == tpTABLE) re = dropTableCmd(cmd);
        }

        if(oper == opDESC && type == tpTABLE){
            re = descTable(cmd);
        }

        if(re < 0){
            if(re == -1) printf("## The ID already exists : %s\n", cmd);
            if(re == -2) printf("## Please Check ID & PW : %s\n", cmd);
            if(re == -3) printf("## can't remove root : %s\n", cmd);
            if(re == -4) printf("## Please Check DB Name : %s\n", cmd);
            if(re == -5) printf("## can't remove yourself : %s\n", cmd);
            if(re == -6) printf("## The Table already exists : %s\n", cmd);
            if(re == -7) printf("## Please Check Table Name : %s\n", cmd);
            if(re == -8) printf("## Please Check Columns Name : %s\n", cmd);
            if(re == -10) printf("## The CMD can used after DATABASE Select : %s\n", cmd);
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
