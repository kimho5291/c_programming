#include "calculator.h"

int valueStack[100] = {'\0', };
int valueIdx = -1;

int calculate(char* array){

    char* vPoint = NULL;
    int len = 0;

    for(int i=0; i<strlen(array); i++){

        if(array[i] >= '0' && array[i] <= '9'){
            ++len;
            if(vPoint == NULL) vPoint = &array[i];
        }else{

            if(vPoint != NULL) valuePush(atoi(vPoint, len));
            particalCalc(array[i]);
            vPoint = NULL;
            len = 0;
        }
    }

    return valuePop();
}

void particalCalc(char oper){
    if(oper == ' ') return;

    int b = valuePop();
    int a = valuePop();

    printf("part %d %c %d\n", a, oper, b);

    if(oper == '*') valuePush(a * b);
    if(oper == '/') valuePush(a / b);
    if(oper == '+') valuePush(a + b);
    if(oper == '-') valuePush(a - b);
}

int atoi(const char* value, const int len){
    int temp = 0;
    for(int i=0; i<len; i++){
        temp = temp * 10 + (value[i] - '0');
    }
    return temp;
}

void valuePush(int value){

    valueStack[++valueIdx] = value;
    // printStack(valueStack, valueIdx, VALUE);
}

int valuePop(){
    int temp = valueStack[valueIdx];
    valueStack[valueIdx--] = '\0';
    // printStack(valueStack, valueIdx, VALUE);
    return temp;
}