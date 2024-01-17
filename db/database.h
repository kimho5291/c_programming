#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "filesystem.h"
#include "struct.h"

extern myDB* selDatabase;

void showDatabase();

int useDatabase(char* cmd);

void createDatabase(char* name);
int createDatabase(char* cmd);