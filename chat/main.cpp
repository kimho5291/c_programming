#include "main.h"


int main(int argc, char* argv[]){


    if(argc < 3) {
        printf("## Usage: %s [Type] [myPort]\n", argv[0]);
        printf("## Type is 'server' or 'client'\n");
        errorHandler((char*)"argc empty", argc);
    }

    int type = ERRTYPE;
    if(strcmp(argv[1], "client") == 0) type = CLIENT;
    else if(strcmp(argv[1], "server") == 0) type = SERVER;
    else errorHandler((char*)"Argv[1] TYPE", type);

    int port = DEFAULT_PORT;
    int argvPort = atoi(argv[2]);
    if(argvPort >= 0 && argvPort <= 65535) port = argvPort;
    else errorHandler((char*)"Argv[2] PORT", argvPort);

    if(type == SERVER) openServer(port);
    else {

        if(argc != 5) {
            printf("## Usage: %s [Type] [myPort] [Dest IP] [Dest Port]\n", argv[0]);
            printf("## Type is 'server' or 'client'\n");
            errorHandler((char*)"Client Argc", argc);
        }

        char* destIP = argv[3];

        int destPort = atoi(argv[4]);
        if(!(destPort >= 0 && destPort <= 65535)) 
            errorHandler((char*)"Argv[5] PORT", destPort);

        openClient(port, destIP, destPort);

    }
    
    return 0;
}

void errorHandler(char* name, int errCode){
    printf("%s Error:: [ %d ] \n", name, errCode);
    exit(1);
}

