#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "struct.h"
#include "filesystem.h"

#define USER_DIR_PATH "./user"
#define USER_FILE_PATH "user.txt"

extern myUser* uHead;

void showUser();

bool checkUser(char* id, char* pw);
void createUser(char* id, char* pw);
void createUser(char* cmd);
void deleteUser(char* id, char* pw);

void createUserFile();
void createUserDir();

void readUserFile();
void writeUserFile();