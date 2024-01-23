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
    char cmd[1000] = {0, };
    int type = -1, oper = -1;
    int re = 0;
    

    do{
        re = 0;
        memset(cmd, 0, 1000);
        getString(cmd);
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

        if(oper == opDESC && type == tpTABLE) re = descTable(cmd);

        if(oper == opINSERT && type == tpTABLE) re = insertTableCmd(cmd);
        // if(oper == opSELECT && type == tpTABLE) re = insertTableCmd(cmd);
        // if(oper == opUPDATE && type == tpTABLE) re = insertTableCmd(cmd);
        if(oper == opDELETE && type == tpTABLE) re = deleteTableCmd(cmd);


        if(re < 0){
            if(re == -1) printf("## The ID already exists : %s\n", cmd);
            else if(re == -2) printf("## Please Check ID & PW : %s\n", cmd);
            else if(re == -3) printf("## can't remove root : %s\n", cmd);
            else if(re == -4) printf("## Please Check DB Name : %s\n", cmd);
            else if(re == -5) printf("## can't remove yourself : %s\n", cmd);
            else if(re == -6) printf("## The Table already exists : %s\n", cmd);
            else if(re == -7) printf("## Please Check Table Name : %s\n", cmd);
            else if(re == -8) printf("## Please Check Columns Name : %s\n", cmd);
            else if(re == -9) printf("## Don't Match Columns : %s\n", cmd);
            else if(re == -10) printf("## The CMD can used after DATABASE Select : %s\n", cmd);
            else if(re == -11) printf("## Please Check Data Type : %s\n", cmd);
            else if(re == -12) printf("## Please Check Syntex : %s\n", cmd);
            else if(re == -13) printf("## Please Check Where Syntex : %s\n", cmd);
            
        }

    }while(oper != opEXIT);
}


char* getString(){

    char temp[BUF_SIZE] = {'\0', };
    char ch = '\0';
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

void getString(char* array){
    int idx = 0;
    char ch = 0;
    do{
        ch = getchar();
        if(ch != '\n'){
            array[idx++] = ch;
        }
    }while(ch != '\n' || idx == 0);
}