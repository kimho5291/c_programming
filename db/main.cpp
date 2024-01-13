#include "main.h"

int main(int argc, char* argv[]){

    printf("-- DB START -- \n");

    

    printf("-- DB END -- \n");
    
    return 0;
};

char* getString(){

    char temp[BUF_SIZE] = {'\0', };
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

