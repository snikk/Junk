#include "Network.h"
#include <stdlib.h>

void addClient(Server* server, Client* client) {
    printf("Added a new client.... Yippee? | name = %s | socket = %d\n", client->name, client->socket);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("I need a port buddy.\n");
        exit(1);
    }

    Server* server;
    createServer(&server, argv[1], addClient, broadcastData);

    while (1) {
        doSelect(server);
    }
}
