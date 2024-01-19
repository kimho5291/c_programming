#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "module/filesystem.h"
#include "struct.h"

extern myDB* selDatabase;
typedef int (*tbDelFunction)(myTB*);
void setTBDelCallback(tbDelFunction);

void initDatabase(myUser* sUser);

void showDatabase();

int useDatabase(char* cmd);

void createDatabase(char* name);
int createDatabaseCmd(char* cmd);

int deleteDBCmd(char* cmd);
int deleteDBAll(myDB* node);

void deleteDBDir(char* name);

void createDBDir(char* name);
void createDBFile(char* cmd);

void writeDBFile();
void readDBFile();