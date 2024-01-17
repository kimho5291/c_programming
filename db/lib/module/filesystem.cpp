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

bool removeDF(char* path){

    int re = remove(path);
    return re == 0 ? true : false;

}

int dirAllDel(char* path){

    DIR *dir;
    struct dirent *ent;
    dir = opendir (path);
    if (dir != NULL) {
 
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {

            char* ptr = strchr(ent->d_name, '.');
            if(ptr == NULL){
                char temp[100] = {'\0', };
                snprintf(temp, 100, "%s/%s", path, ent->d_name);
                dirAllDel(temp);
            }

            if(strcmp(ent->d_name, ".") == 0) continue;
            if(strcmp(ent->d_name, "..") == 0) continue;

            //printf ("%s\n", ent->d_name);

            char temp[100] = {'\0', };
            snprintf(temp, 100, "%s/%s", path, ent->d_name);
            removeDF(temp);

        }
        closedir (dir);

        removeDF(path);

        return 1;

    } else {
         /* could not open directory */
         perror ("");
         return -1;
    }

}

// char* readFile(char* path){
//     FILE* fp= fopen(path, "r");

//     char str[10000] = {'\0', };
//     char line[1000] = {'\0', };
//     while (fgets(line, sizeof(line), fp) != NULL ) {
// 		printf("%s", str);
//         sprintf(str, "%s%s", str, line);
// 	}

//     fclose(fp);

//     return str;
// }

// void writeFile(char* path, char* content){
//     FILE* fp = fopen(path,"w");
//     fputs(content,fp);
//     fclose(fp);
// }

