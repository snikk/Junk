#include "Network.h"

int createServer(Server** serverLocation, const char* port, void (*onClient)(Server*, Client*), void (*onData)(Server *, Client *)) {
    *serverLocation = malloc(sizeof(Server));
    Server* server = *serverLocation;

    struct addrinfo *res;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, port, &hints, &res);

    server->listener = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (server->listener == -1) {
        printf("Couldn't event get the right socket.\n");
        return 1;
    }

    if (bind(server->listener, res->ai_addr, res->ai_addrlen) == -1) {
        printf("Failed to bind... OK.\n");
        return 1;
    }

    char *name = (char*) malloc(128);
    gethostname(name, 128);

    printf("Mah hostess | name = %s\n", name);

    listen(server->listener, 10);

    FD_ZERO(&(server->master));
    FD_SET(server->listener, &(server->master));
    FD_ZERO(&(server->read));

    server->clients = malloc(MAX_CLIENTS * sizeof(ClientStorage));
    server->freeClient = server->clients;
    server->numClients = 0;
    server->fdMax = server->listener;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (i > 0)
            server->clients[i].prev = server->clients[i - 1];
        else
            server->clients[i].prev = NULL;

        if (i < MAX_CLIENTS - 1)
            server->clients[i].next = server->clients[i + 1];
        else
            server->clients[i].next = NULL;
    }

    server->onClient = onClient;
    server->onData = onData;

    return 0;
}

int destroyServer(Server* server) {
    free(server->clients);
    free(server);
    return 0;
}

int doSelect(Server* server) {
    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof(struct sockaddr_storage);
    char remoteIP[INET6_ADDRSTRLEN];

    server->read = server->master;

    if (select(server->fdMax + 1, &(server->read), NULL, NULL, NULL) == -1) {
        printf("Failing on select... FAILING at life.\n");
        return 1;
    }

    if (FD_ISSET(server->listener, &(server->read))) {
        int newfd = accept(server->listener, (struct sockaddr *) &addr, &addr_len);
        inet_ntop(addr.ss_family,
            (struct sockaddr_in *)&addr,
            remoteIP, INET6_ADDRSTRLEN);

        Client* client;
        if (createClient(&client, server, newfd, remoteIP)) {
            printf("Faled to add that dude.  Not cool brah.\n");
        } else {
            FD_SET(client->socket, &(server->master));
            server->onClient(server, client);
        }
    }

    for (int i = 0; i < server->numClients + 1; i++) {
        Client *client = &server->clients[i];
        if (FD_ISSET(client->socket, &(server->read))) {
            int nbytes;
            if ((nbytes = recvData(client)) == 0) {
                destroyClient(client, server);
            } else {
                server->onData(server, client);
            }
        }
    }

    return 0;
}

int sendData(Client* client, void* data, int size) {
    int nbytes;
    if ((nbytes = send(client->socket, data, size, 0)) == -1) {
        printf("Couldn't send the data!\n");
    }
    return nbytes;
}

int recvData(Client* client) {
    if ((client->nbytes = recv(client->socket, client->buffer, MAX_BUFFER, 0)) <= 0) {
        if (client->nbytes == 0) {
            printf("socket %d has hung up.\n", client->socket);
        } else {
            printf("Error getting something back from the remote connection.\n");
        }
    } else {
        client->buffer[client->nbytes] = '\0'; 
    }
    return client->nbytes;
}

int createClient(Client** clientLocation, Server* server, int fd, char* name) {
    if (fd == -1) {
        printf("Failed to get proper socket\n");
        return 1;
    }

    if (server->numClients == MAX_CLIENTS) {
        printf("No more room for clients.  All full.\n");
        return 1;
    }

    ClientStorage *client = &server->freeClient->client;
    server->freeClient = server->freeClient->next;
    server->numClients++;
    memset(client, 0, sizeof(Client));
    *clientLocation = client;

    printf("select server: new connection from %s on socket %d\n", name, client->socket);

    int len = strlen(name);
    client->name = malloc(len);
    memcpy(client->name, name, len);

    client->socket = fd;
    if (fd > server->fdMax)
        server->fdMax = fd;

    client->buffer = malloc(sizeof(char) * MAX_BUFFER);

    return 0;
}

int destroyClient(Client* client, Server* server) {
    // TODO: Whelp.  Gotta figure this one out.

    free(client->buffer);
    free(client->name);

    return 0;
}

void broadcastData(Server* server, Client* client) {
    for (int i = 0; i < server->numClients; i++) {
        if (&server->clients[i] == client)
            continue;

        sendData(&server->clients[i], client->buffer, client->nbytes);
    }
}
