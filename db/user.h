#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "filesystem.h"

#define USER_DIR_PATH "./user"
#define USER_FILE_PATH "user.txt"

typedef struct User{
    char* id;
    char* pw;
    User* next;
}User;



bool checkUser(char* id, char* pw);
void createUser(char* id, char* pw);
void deleteUser(char* id, char* pw);

void createUserFile();
void createUserDir();

void readUserFile();
void writeUserFile();