#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define DEFAULT_PORT 9091
#define DEFAULT_LENGTH 20
#define BUF_SIZE 100

enum{
    TCP = 1,
    UDP = 2,
    SERVER = 3,
    CLIENT = 4,
    ERRTYPE = 5
};

// common
void errorHandler(char* name, int errCode);
int createSock(int type);
int bindSock(int sock, int serv_addr);

// Server
void openServer(int port);
int listenSock(int sock);
void acceptSock(int sock);
void* clientHandler(void* arg);
void sendMsg(char* msg, int len);

// Client
void openClient(int port, char* destIP, int descPort);
int connServer(int sock, char* destIP, int descPort);
void* recvMsg(void* arg);
void* sendMsg2Server(void* arg);
char* getString();

