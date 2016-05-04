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
} Client;

typedef struct {
    struct sockaddr_in sa;

    struct addrinfo *servinfo;
    struct addrinfo validConnection;

    struct sockaddr_in validAddr;

    int status;

    struct addrinfo *res;

    int listener = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    char *name;

    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof(struct sockaddr_storage);

    fd_set master;
    fd_set read;
    int fdMax;

    char *buf;
    int nbytes;

    int numClients;
    Client* clients;

    void (*onClient)(Server *, Client *);
    void (*onData)(Server *, Client *);
} Server;

int createServer(Server**, void (*onClient)(Server*, Client*), void (*onData)(Server *, Client *));
int destroyServer(Server**);

int doSelect(Server*);

int createClient(Client**, Server*, int, char*);
int destroyClient(Client**, Server*);

int sendData(Client*, void*, int);
int recvData(Client*, void*, int);

#endif
