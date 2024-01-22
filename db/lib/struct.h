#ifndef __STRUCT__
#define __STRUCT__

typedef union data{
    char* c_value;
    int i_value;
    double d_value;
}Data;

typedef struct myDt{
    Data data;
    myDt* next;
} myDt;

typedef struct myCL{
    char* name;
    char type[6];
    int size;
    myCL* next;
    myDt* data;
} myCL;

typedef struct myTB{
    char* name;
    myTB* next;
    myCL* column;
} myTB;

typedef struct myDB{
    char* name;
    myDB* next;
    myTB* table;
} myDB;

typedef struct myUser{
    char* id;
    char* pw;
    myUser* next;
    myDB* db;
}myUser;

#endif