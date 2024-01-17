#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "struct.h"
#include "filesystem.h"




extern myUser* uHead;
extern myUser* selUser;

void showUser();

bool checkUser(char* id, char* pw);
void createUser(char* id, char* pw);
int createUserCmd(char* cmd);

void deleteUser(char* id, char* pw);
int deleteUser(char* cmd);

void initUser();

void initUserFile();
void createBasicDir();
void createUserFile();
void createUserDir(char* id);

void deleteUserDir(char* name);


void readUserFile();
void writeUserFile();