#include<stdio.h>
#include<string.h>

enum{
    opSHOW = 0,
    opUSE,
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

int judgeOper(char* cmd);
int judgeType(int oper, char* cmd);
int checkSyntex(int oper, int type, char* cmd);

int countChar(char* cmd, char ch);