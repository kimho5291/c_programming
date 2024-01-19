#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "module/filesystem.h"
#include "struct.h"

void showColumns(myTB* table);

int createCL(myTB* table, char* cmd);

void createCLFile(myUser* user, myDB* db, myTB* tb);