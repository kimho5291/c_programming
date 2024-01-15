#include "filesystem.h"

bool createDF(char* path, int type){

    if(type == TYPE_D){

        if(mkdir(path, 0755) == -1 && errno != EEXIST){
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

char* readFile(char* path){
    FILE* fp= fopen(path, "r");

    char str[10000] = {'\0', };
    char line[1000] = {'\0', };
    while (fgets(line, sizeof(line), fp) != NULL ) {
		printf("%s", str);
        sprintf(str, "%s%s", str, line);
	}

    fclose(fp);

    return str;
}

void writeFile(char* path, char* content){
    FILE* fp = fopen(path,"w");
    fputs(content,fp);
    fclose(fp);
}