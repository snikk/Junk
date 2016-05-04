#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char** argv) {
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct addrinfo validConnection;
    struct sockaddr_in validAddr;
    validConnection.ai_addr = (struct sockaddr *) &validAddr;
    int sock;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;

    int status;
    if ((status = getaddrinfo("127.0.0.1", "3490", &hints, &servinfo)) != 0) {
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

    if ((sock = socket(validConnection.ai_family, validConnection.ai_socktype, validConnection.ai_protocol)) == -1) {
        printf("Failed failed failed to create socket.\n");
        exit(1);
    }

    if (connect(sock, validConnection.ai_addr, validConnection.ai_addrlen) == -1) {
        close(sock);
        printf("Couldn't connect.  alas.\n");
        exit(1);
    }

    int size = 100;
    char *buffer = (char *) malloc(size);
    int bytes;
    if ((bytes = recv(sock, buffer, size - 1, 0)) == -1) {
        close(sock);
        printf("Couldn't receive anything!?\n");
        exit(1);
    }

    buffer[bytes] = '\0';

    printf("Got mah message! | message = %s\n", buffer);

    close(sock);
    
    return 0;
}
