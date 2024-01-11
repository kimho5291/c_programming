#include "main.h"

pthread_t recvThread, sendThread;
void* threadReturn;

void openClient(int port, char* destIP, int descPort){
    
    int sock = createSock(TCP);
    if(sock < 0) errorHandler((char*)"creaetSock", sock);

    int bind = bindSock(sock, port);
    if(bind < 0) errorHandler((char*)"bindSock", bind);

    int conn = connServer(sock, destIP, descPort);
    if(conn < 0) errorHandler((char*)"connServer", conn);

    pthread_create(&sendThread, NULL, sendMsg2Server, (void*)&sock);
    pthread_create(&recvThread, NULL, recvMsg, (void*)&sock);
    pthread_join(sendThread, &threadReturn);
    pthread_join(recvThread, &threadReturn);

    close(sock);
}

int connServer(int sock, char* destIP, int descPort){
    struct sockaddr_in serv_addr; 
    memset(&serv_addr, 0, sizeof(serv_addr)); // 메모리 초기화
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(destIP);
    serv_addr.sin_port = htons(descPort);
    
    // suc: 0, fail: -1
    return connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
}

void* recvMsg(void* arg){

    int sock=*((int*)arg);
    char msg[BUF_SIZE];
 
    while(1)
    {
        int len=read(sock, msg, BUF_SIZE-1);
        if (len <= 0) return (void*)-1;

        msg[len] = '\0';
        printf("[Recv][%d] : %s\n", len, msg);
    }

    return NULL;
}

void* sendMsg2Server(void* arg){

    int sock=*((int*)arg);
    char* msg;

    while(1){
        msg = getString();

        if (!strcmp(msg, "q") || !strcmp(msg, "Q"))
        {
            
            close(sock);
            exit(0);
        }

        write(sock, msg, strlen(msg));
        //printf("[Send][%lu] : %s\n", strlen(msg), msg);

        free(msg);
    }

    return NULL;
}

char* getString(){

    char temp[BUF_SIZE] = {'\0', };
    char ch = NULL;
    int idx = 0;

    do{
        ch = getchar();
        if(ch != '\n'){
            temp[idx++] = ch;
        }
    }while(ch != '\n');

    char* array = (char*)malloc(sizeof(char) * idx);
    strncpy(array, temp, idx);

    return array;
}
