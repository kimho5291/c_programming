#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "filesystem.h"
#include "struct.h"

extern myDB* selDatabase;

void initDatabase(myUser* sUser);

void showDatabase();

int useDatabase(char* cmd);

void createDatabase(char* name);
int createDatabaseCmd(char* cmd);

void deleteDBDir(char* name);

void createDBDir(char* name);
void createDBFile(char* cmd);

void writeDBFile();
void readDBFile();