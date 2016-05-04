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

    if (listener == -1) {
        printf("Couldn't event get the right socket.\n");
    }

    if (bind(listener, res->ai_addr, res->ai_addrlen) == -1) {
        printf("Failed to bind... OK.\n");
        exit(1);
    }

    char *name = (char*) malloc(128);
    gethostname(name, 128);

    printf("Mah hostess | name = %s\n", name);

    listen(listener, 10);

    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof(struct sockaddr_storage);

    char *msg = "Hey there client.  Been working out?\r\n";
    int len = strlen(msg);

    fd_set master;
    fd_set read;
    int fdMax = listener;

    int bufsize = 256;
    char *buf = (char *) malloc(bufsize);
    int nbytes;

    char *remoteIP = (char *) malloc(INET6_ADDRSTRLEN);
    struct sockaddr_storage remoteaddr;

    FD_ZERO(&master);
    FD_SET(listener, &master);
    FD_ZERO(&read);

    while (1) {
        read = master;

        if (select(fdMax + 1, &read, NULL, NULL, NULL) == -1) {
            printf("Failing on select... FAILING at life.\n");
            exit(1);
        }

        for (int i = 0; i <= fdMax; i++) {
            if (FD_ISSET(i, &read)) {
                if (i == listener) {
                    int newfd = accept(listener, (struct sockaddr *) &addr, &addr_len);
                    
                    if (newfd == -1) {
                        printf("Faled to add that dude.  Not cool brah.\n");
                    } else {
                        FD_SET(newfd, &master);
                        if (newfd > fdMax)
                            fdMax = newfd;

                        printf("select server: new conncetion from %s on socket %d\n", 
                            inet_ntop(remoteaddr.ss_family,
                                (struct sockaddr_in *)&remoteaddr,
                                remoteIP, INET6_ADDRSTRLEN),
                            newfd);
                    }
                } else {
                    if ((nbytes = recv(i, buf, bufsize, 0)) <= 0) {
                        if (nbytes == 0) {
                            printf("socket %d has hung up.\n", i);
                        } else {
                            printf("Error getting something back from the remote connection.\n");
                        }

                        close(i);
                        FD_CLR(i, &master);
                    } else {
                        buf[bufsize] = '\0';
                        printf("Got a message | buf = %s\n", buf);
                        for (int j = 0; j <= fdMax; j++) {
                            if (FD_ISSET(j, &master)) {
                                if (j != listener && j != i) {
                                    if (send(j, buf, nbytes, 0) == -1) {
                                        printf("Couldn't send the data!\n");
                                    } else {
                                        printf("Sent form %d to %d\n", i, j);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        //int s = accept(sock, &addr, &addr_len); 





        /*
        if (s == -1) {
            printf("Error!?  what!?\n");
            exit(1);
        }

        int bytes = send(s, msg, len, 0);
        if (bytes == 0) {
            printf("Connection closed?  That was fast.  I mean look at how many instructions separate us.\n");
        } else if (bytes < len) {
            printf("That was super small.  Breaking things up that small is a little silly.\n");
        } else {
            printf("Sent that message.  Boooyaaa.\n");
        }

        if (close(s) == -1) {
            printf("Didn't close this most recent socket.\n");
        }
        */
    }

    free(buf);
    free(remoteIP);

    return 0;
}
