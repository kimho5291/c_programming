#include "user.h"


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

    //printf("## USER [%s | %s] INSERT !!\n", id, pw);
}

void createUser(char* cmd){

    // ex: create user kim 1234;\n
    printf("cmd : %s\n", cmd);
    char* temp = NULL;
    char* ptr = strtok_r(cmd, " ", &temp);
    printf("ptr1 : %s\n", ptr);

    ptr = strtok_r(NULL, " ", &temp);
    printf("ptr2 : %s\n", ptr);

    ptr = strtok(NULL, " ");
    printf("ptr3 : %s\n", ptr);
    char* id = (char*)malloc(sizeof(char) * strlen(ptr));
    strcpy(id, ptr);

    ptr = strtok(NULL, " ");
    printf("ptr4 : %s\n", ptr);
    char* pw = (char*)malloc(sizeof(char) * strlen(ptr));
    strcpy(pw, ptr);

    printf("id : %s\n", id);
    printf("pw : %s\n", pw);

    myUser* user = (myUser*)malloc(sizeof(myUser));
    memset(user, 0, sizeof(myUser));
    user->id = id;
    user->pw = pw;
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

    writeUserFile();
    printf("## USER [%s | %s] INSERT !!\n", id, pw);
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
        printf("## USER [%s] DELETE !!\n", id);
        pre->next = now->next;
        free(now);
    }else{
        printf("## USER [%s] NOT FOUND !!\n", id);
    }
}

void createUserFile(){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s", USER_DIR_PATH, USER_FILE_PATH);
    bool re = createDF(path, TYPE_F);
    printf("## UserFile : %d\n", re);
}

void createUserDir(){
    char path[100] = {'\0', };
    snprintf(path, 100, "%s", USER_DIR_PATH);
    bool re = createDF(path, TYPE_D);
    printf("## UserDir : %d\n", re);
}

void readUserFile(){

    char path[100] = {'\0', };
    snprintf(path, 100, "%s/%s", USER_DIR_PATH, USER_FILE_PATH);

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
    snprintf(path, 100, "%s/%s", USER_DIR_PATH, USER_FILE_PATH);

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

