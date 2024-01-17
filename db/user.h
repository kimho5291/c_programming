#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "struct.h"
#include "filesystem.h"

#define USER_DIR_PATH "./db"
#define USER_FILE_PATH "user.txt"

extern myUser* uHead;
extern myUser* selUser;

void showUser();

bool checkUser(char* id, char* pw);
void createUser(char* id, char* pw);
int createUser(char* cmd);

void deleteUser(char* id, char* pw);
int deleteUser(char* cmd);

void initUser();

void initUserFile();
void createBasicDir();
void createUserFile();
void createUserDir(char* id);


void readUserFile();
void writeUserFile();