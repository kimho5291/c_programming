#include "main.h"

int main(int argc, char* argv[]){

    printf("-- DB START -- \n");

    createUser((char*)"kim", (char*)"1234");
    createUser((char*)"young", (char*)"aaaa");
    createUser((char*)"ho", (char*)"bbbb");

    char* id = argv[1];
    char* pw = argv[2];

    if(checkUser(id, pw)){
        printf("## USER [%s] WELCOME !!\n", id);


    }else{
        printf("## USER [%s] NOT FOUND !!\n", id);
        printf("## please check ID & PW !!\n");
    }



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

