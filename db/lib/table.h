#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "module/filesystem.h"
#include "struct.h"

void initTBUser(myUser* user);
void initTBDatabase(myDB* db);

void showTables();

void createTBFile(char* cmd);