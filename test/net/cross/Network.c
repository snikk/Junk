#include "Network.h"

int main(int argc, char** argv) {
    printf("Hello, World!\n");

    struct sockaddr_in sa;
    
    inet_pton(AF_INET, "192.168.1.1", &(sa.sin_addr));

    printf("addr | hex = %#010x | int = %d\n", sa.sin_addr.s_addr, sa.sin_addr.s_addr);

    printf("-----------------------------------\n");

    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct addrinfo validConnection;
    struct sockaddr_in validAddr;
    validConnection.ai_addr = (struct sockaddr *) &validAddr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;

    int status;
    if ((status = getaddrinfo("www.google.com", NULL, &hints, &servinfo)) != 0) {
        printf("Well that didn't go as expected.");
        exit(1);
    }

    for (struct addrinfo *info = servinfo; info != NULL; info = info->ai_next) {
        char *buffer = (char*) malloc(64);
        memset(buffer, 0, 64);
        inet_ntop(info->ai_family, info->ai_family == AF_INET ? &(((struct sockaddr_in *)(info->ai_addr))->sin_addr) : &(((struct sockaddr_in6 *)(info->ai_addr))->sin6_addr), buffer, 64);
        printf("Hey there | %s | ", buffer);
        if (info->ai_family == AF_INET) {
            struct sockaddr_in *addr = (struct sockaddr_in *) info->ai_addr;

            memcpy(&validConnection, info, sizeof(struct addrinfo));
            validConnection.ai_addr = (struct sockaddr *) &validAddr;
            memcpy(&validAddr, addr, sizeof(struct sockaddr_in));

            printf("AF_INET | hex = %#010x | int = %d", addr->sin_addr.s_addr, addr->sin_addr.s_addr);
        } else if (info->ai_family == AF_INET6) {
            struct sockaddr_in6 *addr = (struct sockaddr_in6 *) info->ai_addr;
            printf("AF_INET6 | hex = ");

            for (int i = 0; i < 16; i++) {
                if (i > 0 && i % 2 == 0)
                    printf(":");
                printf("%02x", addr->sin6_addr.s6_addr[i]);
            }
        }
        printf("\n");
    }

    freeaddrinfo(servinfo);

    printf("validConnection | hex = %#010x | int = %d\n", ((struct sockaddr_in *)validConnection.ai_addr)->sin_addr.s_addr, ((struct sockaddr_in *)validConnection.ai_addr)->sin_addr.s_addr);
    printf("validAddr| hex = %#010x | int = %d\n", validAddr.sin_addr.s_addr, validAddr.sin_addr.s_addr);
    int sock = socket(validConnection.ai_family, validConnection.ai_socktype, validConnection.ai_protocol);

    if (sock == -1) {
        printf("Hmm... Couldn't get the socket.  Bummer. | errno = %d\n", errno);
    }

    printf("Added that sock!  YES! | sock = %d\n", sock);

    if (close(sock) == -1) {
        printf("hmmmm.... I didn't close.  How very very odd.\n");
        exit(1);
    }

    if (close(sock) != -1) {
        printf("Succeeded!?  This was already closed though.  Kinda loosey goosey.\n");
        exit(1);
    }

    struct addrinfo *res;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, "3490", &hints, &res);

    int listener = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    while (1) {
    }

    free(buf);
    free(remoteIP);

    return 0;
}

int createServer(Server** serverLocation, const char* port) {
    *serverLocation = (Server*) malloc(sizeof Server);
    Server* server;

    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, port, &hints, &res);

    server->listener = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (server->listener == -1) {
        printf("Couldn't event get the right socket.\n");
        return 1;
    }

    if (bind(listener, res->ai_addr, res->ai_addrlen) == -1) {
        printf("Failed to bind... OK.\n");
        return 1;
    }

    char *name = (char*) malloc(128);
    gethostname(name, 128);

    printf("Mah hostess | name = %s\n", name);

    listen(server->listener, 10);

    server->fdMax = listener;

    FD_ZERO(&master);
    FD_SET(listener, &master);
    FD_ZERO(&read);

    server->clients = malloc(MAX_CLIENTS * sizeof Client);
    server->numClients = 0;

    return 0;
}

int destroyServer(Server** server) {
    free((*server)->clients);
    free(*server);
    return 0;
}

int doSelect(Server* server) {
    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof(struct sockaddr_storage);
    char remoteIP[INET6_ADDRSTRLEN];

    read = master;

    if (select(server->numClients + 1, &read, NULL, NULL, NULL) == -1) {
        printf("Failing on select... FAILING at life.\n");
        return 1;
    }

    if (FD_ISSET(server->listener, &read)) {
        int newfd = accept(listener, (struct sockaddr *) &addr, &addr_len);
        inet_ntop(addr.ss_family,
            (struct sockaddr_in *)&addr,
            remoteIP, INET6_ADDRSTRLEN),

        Client* client;
        if (createClient(&client, server, newfd, remoteIP)) {
            printf("Faled to add that dude.  Not cool brah.\n");
        } else {
            FD_SET(client->socket, &master);
            server->onClient(server, client);
        }
    }

    for (int i = 0; i < server->numClients + 1; i++) {
        Client* client = server->clients[i];
        if (FD_ISSET(client->socket, &read)) {
            int nbytes;
            if ((nbytes = recvClient(client)) == 0) {
                deleteClient(client);
            } else {
                server->onData(server, client);
            }
        }
    }
}

int sendData(Client* client, void* data, int size) {
    int nbytes;
    if ((nbytes = send(client->socket, data, size, 0)) == -1) {
        printf("Couldn't send the data!\n");
    }
    return nbytes;
}

int recvData(Client* client) {
    int nbytes;
    if ((nbytes = recv(i, client->buffer, MAX_BUFFER, 0)) <= 0) {
        if (nbytes == 0) {
            printf("socket %d has hung up.\n", client->socket);
        } else {
            buf[nbytes] = '\0';
            printf("Error getting something back from the remote connection.\n");
        }
    }
    return nbytes;
}

int createClient(Client** clientLocation, Server* server, int fd, char* name) {
    if (fd == -1) {
        printf("Failed to get proper socket\n");
        return 1;
    }

    printf("select server: new conncetion from %s on socket %d\n", name, client->socket);

    Client *client = server->clients[server->numClients];
    server->numClients++;
    memset(client, 0, sizeof Client);
    *clientLocation = client;

    int len = strlen(name);
    client->name = malloc(len);
    memcpy(client->name, name, len);

    client->socket = fd;

    client->buffer = malloc(sizeof(char) * MAX_BUFFER);

    return 0;
}

int destroyClient(Client* client, Server* server) {
    // TODO: Whelp.  Gotta figure this one out.

    free(client->location);
    free(client->name);
}
