#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define MAX_CLIENTS 32
#define MAX_BUFFER 256

typedef struct {
    int socket;
    char* name;
    char* buffer;
    int nbytes;
} Client;

typedef struct _ClientStoreage {
    Client client;
    Client* next;
    Client* prev;
} ClientStorage;

typedef struct _Server {
    struct sockaddr_in sa;

    struct addrinfo *servinfo;
    struct addrinfo validConnection;

    struct sockaddr_in validAddr;

    int status;

    int listener;

    fd_set master;
    fd_set read;
    int fdMax;

    int numClients;
    ClientStorage* clients;
    ClientStorage* freeClient;

    void (*onClient)(struct _Server *, Client *);
    void (*onData)(struct _Server *, Client *);
} Server;

int createServer(Server**, const char*, void (*onClient)(Server*, Client*), void (*onData)(Server *, Client *));
int destroyServer(Server*);

int doSelect(Server*);

int createClient(Client**, Server*, int, char*);
int destroyClient(Client*, Server*);

int sendData(Client*, void*, int);
int recvData(Client*);

void broadcastData(Server*, Client*);

#endif
