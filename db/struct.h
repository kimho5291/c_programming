
typedef union data{
    char* c_value;
    int i_value;
    float f_value;
}Data;

typedef struct myDt{
    Data data;
    myDt* next;
} myDt;

typedef struct myCL{
    char* name;
    int type;
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
    myTB* tables;
} myDB;