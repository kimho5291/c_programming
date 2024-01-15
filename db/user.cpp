#include "user.h"

User* u_head = NULL;

bool checkUser(char* id, char* pw){
    User* now = u_head;
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

    User* user = (User*)malloc(sizeof(User));
    memset(user, 0, sizeof(User));
    user->id = (char*)malloc(sizeof(char) * strlen(id));
    user->pw = (char*)malloc(sizeof(char) * strlen(pw));
    strcpy(user->id, id);
    strcpy(user->pw, pw);
    user->next = NULL;

    if(u_head == NULL){
        u_head = user;
    }else{
        User* temp = u_head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = user;
    }

    printf("## USER [%s | %s] INSERT !!\n", id, pw);

}

void deleteUser(char* id, char* pw){
    User* pre = u_head;
    User* now = u_head;
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
    sprintf(path, "%s/%s", USER_DIR_PATH, USER_FILE_PATH);
    bool re = createDF(path, TYPE_F);
    printf("## UserFile : %d\n", re);
}

void createUserDir(){
    bool re = createDF(USER_DIR_PATH, TYPE_D);
    printf("## UserDir : %d\n", re);
}

void readUserFile(){

    char path[100] = {'\0', };
    sprintf(path, "%s/%s", USER_DIR_PATH, USER_FILE_PATH);

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
    sprintf(path, "%s/%s", USER_DIR_PATH, USER_FILE_PATH);

    FILE* fp = fopen(path,"w");

    User* now = u_head;
    while(now != NULL){
        char temp[100] = {'\0', };
        sprintf(temp,"%s %s\n", now->id, now->pw);
        fputs(temp,fp);
        now = now->next;
    }

    fclose(fp);
}

