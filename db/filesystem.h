#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

enum{
    TYPE_D = 0,
    TYPE_F = 1
};

bool createDF(char* path, int type);
char* readFile(char* path);
void writeFile(char* path, char* content);