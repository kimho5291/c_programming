#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

enum{
    DIR = 0,
    FILE = 1
};

bool createDF(char* path, int type);