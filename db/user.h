#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct User{
    char* id;
    char* pw;
    User* next;
}User;



bool checkUser(char* id, char* pw);
void createUser(char* id, char* pw);
void deleteUser(char* id, char* pw);