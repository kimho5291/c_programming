
#ifndef __FILESYSTEM__
#define __FILESYSTEM__

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define BASIC_DIR_PATH "./db"
#define USER_FILE_PATH "user.txt"
#define DATABASE_FILE_PATH "db.txt"

enum{
    TYPE_D = 0,
    TYPE_F = 1
};

bool createDF(char* path, int type);
bool removeDF(char* path);
// char* readFile(char* path);
// void writeFile(char* path, char* content);

#endif