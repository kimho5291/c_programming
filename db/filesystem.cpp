#include "filesystem.h"

bool createDF(char* path, int type){

    if(type == DIR){

        if(mkdir(path, 755) == -1 && errno != EEXIST){
            printf("## Directory Create Erorr: %d\n", errno);
            return false;
        }
        return true;

    }else{
        FILE* ffff = fopen(path, "a+");

        if(ffff == NULL){
            printf("## File Create Error !!\n");
            return false;
        }

        fclose(ffff);
        return true;

    }


}