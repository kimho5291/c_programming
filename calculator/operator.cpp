#include "calculator.h"

char operStack[100] = {'\0', };
int operIdx = -1;


char* changePrefix(char* array){
    char* tempArray = (char*)malloc(sizeof(char) * strlen(array) * 2);
    int idx = 0;

    for(int i=0; i<strlen(array); i++){

        if(array[i] >= '0' && array[i] <= '9'){
            tempArray[idx++] = array[i]; 
            continue;
        }

        tempArray[idx++] = ' ';
        char temp = addOper(array[i]);
        if(temp == ')'){
            char temp = NULL;
            do{
                temp = operPop();
                if(temp != '(') tempArray[idx++] = temp;
            }while(temp != '(');
        }
        else if(temp != NULL){
            tempArray[idx++] = temp;
            continue;
        }
    }

    while(operIdx != -1){
        char temp = operPop();
        tempArray[idx++] = temp;
        tempArray[idx++] = ' ';
    }
    free(array);

    return tempArray;
}

char addOper(char oper){

    if(operPeriority(oper) == 3){
        return ')';
    }

    if(operIdx == -1 || operPeriority(oper) == 0){
        operPush(oper);
        return NULL;
    }

    char temp = operStack[operIdx];
    if(operPeriority(oper) > operPeriority(temp)){
        operPush(oper);
        return NULL;
    }

    temp = operPop();
    operPush(oper);
    return temp;
}

void operPush(char oper){
    operStack[++operIdx] = oper;
    //printStack(operStack, operIdx, OPER);
}

char operPop(){
    char temp = operStack[operIdx];
    operStack[operIdx--] = '\0';
    //printStack(operStack, operIdx, OPER);
    return temp;
}

int operPeriority(char oper){
    if(oper == ')') return 3;
    if(oper == '*' || oper == '/') return 2;
    if(oper == '+' || oper == '-') return 1;
    if(oper == '(') return 0;
}




