#ifndef __PARSER__
#define __PARSER__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

enum{
    opSHOW = 0,
    opUSE,
    opCREATE,
    opDROP,
    opINSERT,
    opUPDATE,
    opDELETE,
    opSELECT,
    opDESC,
    opEXIT
};

enum{
    tpUSER = 0,
    tpDATABASE,
    tpTABLE
};

enum{
    opAND = 0,
    opOR,
    opNONE
};

enum{
    EQ = 0, // =
    NE, // !=
    GE, // >=
    LE, // <=
    GT, // >
    LT, // <
    NN
};

typedef struct condition{
    char col[100];
    char val[100];
    int oper;
    condition* nextAnd;
    condition* nextOr;
}condition;

int judgeOper(char* cmd);
int judgeType(int oper, char* cmd);
int checkSyntex(int oper, int type, char* cmd);

condition* parseWhere(char* cmd);
void deleteAllCondition(condition* node);
int checkOperator(char* cmd);

void printConditions(condition* node);

int countChar(char* cmd, char ch);

#endif