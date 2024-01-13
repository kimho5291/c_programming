#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct user{
    char* id;
    char* pw;
    User next;
}User;

User* u_head = NULL;

bool checkUser(char* id, char* pw);
void createUser(char* id, char* pw);
void deleteUser(char* id, char* pw);