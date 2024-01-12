#include<stdio.h>
#include<stdlib.h>


struct myCL{
    char* name;
    int type;
    myDB* next;
} typedef myCL;

struct myTB{
    char* name;
    myTB* next;
} typedef myTB;

struct myDB{
    char* name;
    myDB* next;
    myTB* tables;
} typedef myDB;