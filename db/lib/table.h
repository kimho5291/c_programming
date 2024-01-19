#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "module/filesystem.h"
#include "struct.h"
#include "column.h"

void initTBUser(myUser* user);
void initTBDatabase(myDB* db);

int showTables();
int descTable(char* cmd);

void createTB(char* name);
int createTBCmd(char* cmd);

void createTBFile(char* cmd);

void writeTBFile();
void readTBFile();

