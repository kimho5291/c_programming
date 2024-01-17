#include "main.h"

int main(int argc, char* argv[]){


    printf("-- DB START -- \n");

    sysInit();

    char* id = argv[1];
    char* pw = argv[2];

    if(login(id, pw)){
        printf("## USER [%s] WELCOME !!\n", id);

        // process
        process();

    }else{
        printf("## USER [%s] NOT FOUND !!\n", id);
        printf("## please check ID & PW !!\n");
    }


    printf("-- DB END -- \n");
    
    return 0;
};


