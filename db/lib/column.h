#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include "module/filesystem.h"
#include "struct.h"
#include "module/parser.h"

void showColumns(myTB* table);

int createCL(myTB* table, char* cmd);

int insertData(myTB* table, char* cmd);



int deleteAllCL(myCL* column);


void createCLFile(myUser* user, myDB* db, myTB* tb);
void removeCLFile(myUser* user, myDB* db, myTB* tb);
