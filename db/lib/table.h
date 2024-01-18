#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "module/filesystem.h"
#include "struct.h"

void initTBUser(myUser* user);
void initTBDatabase(myDB* db);

void showTables();

void createTB(char* name);
int createTBCmd(char* cmd);

void createTBFile(char* cmd);

