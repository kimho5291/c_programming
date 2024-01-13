#include "user.h"


bool checkUser(char* id, char* pw){
    User* now = u_head;
    bool flag = false;

    while(now->next != NULL){
        if(strcpy(now->id, id) && strcpy(now->pw, pw)){
            flag = true;
            break;
        }
        now = now->next;
    }

    if(flag){
        printf("## USER [%s] WELCOME !!\n", id);
    }else{
        printf("## USER [%s] NOT FOUND !!\n", id);
    }

    return flag;
}

void createUser(char* id, char* pw){

    User* user = (User*)malloc(sizeof(User));
    memset(user, 0, sizeof(User));
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

    printf("## USER [%s] INSERT !!\n", id);

}

void deleteUser(char* id, char* pw){
    User* pre = u_head;
    User* now = u_head;
    bool flag = false;

    while(now->next != NULL){
        if(strcpy(now->id, id) && strcpy(now->pw, pw)){
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
