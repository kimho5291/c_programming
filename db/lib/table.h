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

int insertTableCmd(char* cmd);
int selectTableCmd(char* cmd);
int updateTableCmd(char* cmd);
int deleteTableCmd(char* cmd);

myTB* findTable(char* name);

void testPrintTable(myTB* table);


int dropTableCmd(char* cmd);
int dropAllTB(myTB* node);

void createTB(char* name);
int createTBCmd(char* cmd);

void createTBFile(char* cmd);

void writeTBFile();
void readTBFile();

