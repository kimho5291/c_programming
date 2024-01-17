#include "user.h"

myUser* selUser = NULL;
myUser* uHead = NULL;

void showUser(){
    myUser* now = uHead;
    int idx = 0;
    printf("## ----- USER List -----\n");
    while(now != NULL){
        printf("[%d] %s %s\n", idx++, now->id, now->pw);
        now = now->next;
    }
    printf("## ----- USER List -----\n");
}


bool checkUser(char* id, char* pw){
    myUser* now = uHead;
    bool flag = false;

    while(now != NULL){
        if(strcmp(now->id, id) == 0 && strcmp(now->pw, pw) == 0){
            flag = true;
            selUser = now;
            break;
        }
        now = now->next;
    }

    return flag;
}

void createUser(char* id, char* pw){

    myUser* user = (myUser*)malloc(sizeof(myUser));
    memset(user, 0, sizeof(myUser));
    user->id = (char*)malloc(sizeof(char) * strlen(id));
    user->pw = (char*)malloc(sizeof(char) * strlen(pw));
    strcpy(user->id, id);
    strcpy(user->pw, pw);
    user->next = NULL;

    if(uHead == NULL){
        uHead = user;
    }else{
        myUser* temp = uHead;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = user;
    }

    // writeUserFile();
    //printf("## USER [%s | %s] INSERT !!\n", id, pw);
}

int createUserCmd(char* cmd){

    // ex: create user kim 1234\n
    char temp[100] = {'\0', };
    strcpy(temp, cmd);

    char* ptr = strtok(temp, " ");
    ptr = strtok(NULL, " ");

    ptr = strtok(NULL, " ");
    char* id = (char*)malloc(sizeof(char) * strlen(ptr));
    strcpy(id, ptr);

    ptr = strtok(NULL, " ");
    char* pw = (char*)malloc(sizeof(char) * strlen(ptr));
    strcpy(pw, ptr);

    myUser* user = (myUser*)malloc(sizeof(myUser));
    memset(user, 0, sizeof(myUser));
    user->id = id;
    user->pw = pw;
    user->next = NULL;

    if(uHead == NULL){
        uHead = user;
    }else{
        myUser* pre = uHead;
        myUser* temp = uHead;
        while(temp != NULL){
            if(strcmp(temp->id, id)==0){
                free(user);
                free(id);
                free(pw);
                return -1;
            }
            pre = temp;
            temp = temp->next;
        };
        pre->next = user;
    }

    writeUserFile();
    createUserDir(id);
    printf("## USER [%s | %s] CREATE !!\n", id, pw);
    return 1;
}

void deleteUser(char* id, char* pw){
    myUser* pre = uHead;
    myUser* now = uHead;
    bool flag = false;

    while(now != NULL){
        if(strcmp(now->id, id) == 0 && strcmp(now->pw, pw) == 0){
            flag = true;
            break;
        }
        pre = now;
        now = now->next;
    }

    if(flag){
        printf("## USER [%s] DROP !!\n", id);
        pre->next = now->next;
        free(now->id);
        free(now->pw);
        free(now);
    }else{
        printf("## USER [%s] NOT FOUND !!\n", id);
    }
    writeUserFile();
}

int deleteUser(char* cmd){

    // ex: drop user kim 1234\n
    char temp[100] = {'\0', };
    strcpy(temp, cmd);

    char* ptr = strtok(temp, " ");
    ptr = strtok(NULL, " ");

    ptr = strtok(NULL, " ");
    char* id = (char*)malloc(sizeof(char) * strlen(ptr));
    strcpy(id, ptr);

    ptr = strtok(NULL, " ");
    char* pw = (char*)malloc(sizeof(char) * strlen(ptr));
    strcpy(pw, ptr);

    if(strcmp((char*)"root", id) == 0){
        return -3;
    }

    myUser* pre = uHead;
    myUser* now = uHead;

    while(now != NULL){
        if(strcmp(now->id, id) == 0 && strcmp(now->pw, pw) == 0){
            pre->next = now->next;
            printf("## USER [%s] DELETE !!\n", id);
            writeUserFile();
            deleteUserDir(id);

            free(now);
            free(id);
            free(pw);
            return 1;
        }
        pre = now;
        now = now->next;
    }

    return -2;
}


void initUser(){
    createBasicDir();
    createUserFile();

    initUserFile();
}

void createUserFile(){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s", BASIC_DIR_PATH, USER_FILE_PATH);
    bool re = createDF(path, TYPE_F);
    // printf("## UserFile : %d\n", re);
}

void initUserFile(){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s", BASIC_DIR_PATH, USER_FILE_PATH);
    
    int idx = 0;
    char line[100] = {'\0', };

    FILE* fp= fopen(path, "r");
    while (fgets(line, sizeof(line), fp) != NULL ) {
        idx++;
        break;
	}
    fclose(fp);

    if(idx == 0){
        createUserCmd((char*)"create user root 1234");
    }

}

void createBasicDir(){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s", BASIC_DIR_PATH);
    bool re = createDF(path, TYPE_D);
    // printf("## UserDir : %d\n", re);
}

void createUserDir(char* id){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s", BASIC_DIR_PATH, id);
    bool re = createDF(path, TYPE_D);
    // printf("## UserDir : %d\n", re);
}

void deleteUserDir(char* id){

    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s", BASIC_DIR_PATH, id);
    bool re = dirAllDel(path);
    //printf("## deleteUserDir : %d\n", re);
}

void readUserFile(){

    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s", BASIC_DIR_PATH, USER_FILE_PATH);

    FILE* fp= fopen(path, "r");

    char line[100] = {'\0', };
    while (fgets(line, sizeof(line), fp) != NULL ) {

        char* ptr = strtok(line, " ");
        char* id = ptr;
        ptr = strtok(NULL, "\n");
        char* pw = ptr;

		createUser(id, pw);
	}

    fclose(fp);
}

void writeUserFile(){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s", BASIC_DIR_PATH, USER_FILE_PATH);

    FILE* fp = fopen(path,"w");

    myUser* now = uHead;
    while(now != NULL){
        char temp[100] = {'\0', };
        snprintf(temp, 100, "%s %s\n", now->id, now->pw);
        fputs(temp,fp);
        now = now->next;
    }

    fclose(fp);
}

