#include "main.h"

int clientList[DEFAULT_LENGTH] = {0, };
int clientIdx=0;
pthread_mutex_t mutx;
pthread_t thread;


void openServer(int port){

    int sock = createSock(TCP);
    if(sock < 0) errorHandler((char*)"creaetSock", sock);

    int bind = bindSock(sock, port);
    if(bind < 0) errorHandler((char*)"bindSock", bind);

    int listen = listenSock(sock);
    if(listen < 0) errorHandler((char*)"listenSock", listen);

    printf("-- SERVER OPEN [ %d ] -- \n", port);

    acceptSock(sock);

    close(sock);
}


int createSock(int type){
    int temp = 0;

    // PF = Protocal family
    // AF = Address family
    // 리눅스에서는 차이가 없다.
    if(type == TCP){
        temp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }else if(type == UDP){
        temp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }else{
        temp = -2;
    }

    // suc: file descriptor, fail: -1, unknown: -2
    return temp;
}

int bindSock(int sock, int port){
    if(port == 0) port = DEFAULT_PORT;

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    // suc: 0, fail: -1
    return bind(sock, (struct sockaddr*)&servAddr, sizeof(servAddr));
}

int listenSock(int sock){

    // suc: 0, fail: -1
    return listen(sock, 5);
}

void acceptSock(int sock){
    while(1){
        struct sockaddr_in clientAddr;
        int addrSize = sizeof(clientAddr);
        int clientSock = accept(sock, (struct sockaddr*)&clientAddr, (socklen_t*)&addrSize);
        
        pthread_mutex_lock(&mutx);
        clientList[clientIdx++]=clientSock;
        pthread_mutex_unlock(&mutx);

        pthread_create(&thread, NULL, clientHandler, (void*)&clientSock);
        pthread_detach(thread);

        printf(" Connceted Client IP : %s ", inet_ntoa(clientAddr.sin_addr));
        printf(" Chat Room [ %d / %d ]\n", clientIdx, DEFAULT_LENGTH);

        char* joinMsg = (char*)"## Someone Joined the Chat !!";
        sendMsg(joinMsg, strlen(joinMsg));

    }
}

void* clientHandler(void* arg){
    int clientSock=*((int*)arg);
    int len=0;
    char msg[BUF_SIZE];

    while((len=read(clientSock, msg, sizeof(msg)))!=0){
        sendMsg(msg, len);
    }

    pthread_mutex_lock(&mutx);
    for (int i=0; i<clientIdx; i++)
    {
        if (clientSock==clientList[i])
        {
            while(i<clientIdx-1){
                clientList[i]=clientList[i+1];
                i++;
            }
            break;
        }
    }
    clientIdx--;
    pthread_mutex_unlock(&mutx);

    printf(" Chat Room [ %d / %d ]\n", clientIdx+1, DEFAULT_LENGTH);
    printf(" Disconnceted Client");

    char* exitMsg = (char*)"## Someone Exited the Chat !!";
    sendMsg(exitMsg, strlen(exitMsg));

    close(clientSock);
    return NULL;
}

void sendMsg(char* msg, int len){
    pthread_mutex_lock(&mutx);
    for (int i=0; i<clientIdx; i++){
        write(clientList[i], msg, len);
    }
    pthread_mutex_unlock(&mutx);
}