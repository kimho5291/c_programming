#include "calculator.h"

int main(){

    printf("Main Start -- \n");

    char* array = getString();
    printf("init : %s\n", array);

    array = changePrefix(array);
    printf("prefix : %s\n", array);

    int answer = calculate(array);
    printf("answer : %d\n", answer);

    free(array);
    printf("Main End -- \n");
    
    return 0;
}

char* getString(){

    char temp[1000] = {'\0', };
    char ch = NULL;
    int idx = 0;

    do{
        ch = getchar();
        if(ch != '\n'){
            temp[idx++] = ch;
        }
    }while(ch != '\n');

    char* array = (char*)malloc(sizeof(char) * idx);
    strncpy(array, temp, idx);

    return array;
}

void printStack(const void* array, const int idx, int type){
    printf("print stack [ ");
    if(type == 1){
        char* temp = (char*) array;
        for(int i=0; i<=idx; i++){
            printf("%c ", temp[i]);
        }
    }else if(type == 2){
        int* temp = (int*) array;
        for(int i=0; i<=idx; i++){
            printf("%d ", temp[i]);
        }
    }
    printf("] \n");
}