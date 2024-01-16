
#include "user.h"
#include "database.h"

#define BUF_SIZE 255

enum{
    opSHOW = 0,
    opCREATE,
    opDROP,
    opINSERT,
    opUPDATE,
    opDELETE,
    opSELECT,
    opEXIT
};

enum{
    tpUSER = 0,
    tpDATABASE,
    tpTABLE
};


void sysInit();
bool login(char* id, char* pw);

void process();
int judgeOper(char* cmd);
int judgeType(int oper, char* cmd);

char* getString();
