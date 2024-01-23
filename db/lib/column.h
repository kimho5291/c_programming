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
int deleteData(myTB* table, char* cmd);
int deleteRow(myCL* column, int index);


int deleteAllCL(myCL* column);
int deleteAllDT(myDt* data);


void createCLFile(myUser* user, myDB* db, myTB* tb);
void removeCLFile(myUser* user, myDB* db, myTB* tb);

void writeDTFile(myUser* user, myDB* db, myTB* tb);
void readDTFile(myUser* user, myDB* db);

void testPrintData(myTB* table);