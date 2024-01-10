#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum{
    OPER = 1,
    VALUE = 2
};


char* getString();

char* changePrefix(char*);
char addOper(char);
void operPush(char);
char operPop();
int operPeriority(char);

int calculate(char*);
int atoi(const char* value, const int len);
void particalCalc(char);
void valuePush(int);
int valuePop();


void printStack(const void* array, const int idx, int type);