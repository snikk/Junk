#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char** argv) {
    printf("Hello, World!\n");

    int status;
    struct addrinfo* info;
    struct addrinfo hints;

    char ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    const int size = 255;
    char hostname[size];
    int hostStatus = gethostname(hostname, size);
    if (hostStatus) {
        printf("Had an error when getting host name!\n");
        return hostStatus;
    }

    printf("Hostname = %s\n", hostname);

    struct hostent* host = gethostbyname(hostname);
    printf("Hostname = %s\n", host->h_name);
    for (char** alias = host->h_aliases; *alias != NULL; alias++)
        printf("Alias = %s\n", *alias);
    printf("AddrType = %d\n", host->h_addrtype);
    printf("Length = %d\n", host->h_length);
    for (char** addr = host->h_addr_list; *addr != NULL; addr++) {
        printf("Address = %s\n", *addr);
        for (char* address = addr[0]; *address != NULL; address++) {
            printf("%d ", (unsigned char)*address);
        }
    }

    printf("\n\n");
    
    status = getaddrinfo(NULL, "3490", &hints, &info);
    printf("Get Addr Info status = %d\n", status);

    for (struct addrinfo* p = info; p != NULL; p = p->ai_next) {
        void *addr;
        char ipver[100];
        memset(ipver, 0, sizeof ipver);

        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            sprintf(ipver, "IPv4: port: %d", ipv4->sin_port);
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            sprintf(ipver, "IPv6: port: %d", ipv6->sin6_port);
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("  %s: %s\n", ipver, ipstr);
    }

    struct addrinfo* ptr = info;
    while (ptr) {
        printf("Flags           = %d\n", ptr->ai_flags);
        printf("Family          = %d | INET = %d | INET6 = %d | UNSPEC = %d\n", ptr->ai_family, AF_INET, AF_INET6, AF_UNSPEC);
        printf("Socktype        = %d | STREAM = %d | DGRAM = %d\n", ptr->ai_socktype, SOCK_STREAM, SOCK_DGRAM);
        printf("Protocol        = %d\n", ptr->ai_protocol);
        printf("Addrlength      = %d\n", ptr->ai_addrlen);
        printf("Address:\n");
        printf("    Family      = %d\n", ptr->ai_addr->sa_family);
        printf("    Data        = ");
        for (int i = 0; i < 15; i++)
            printf("%02x ", ptr->ai_addr->sa_data[i]);
        printf("\n");

        printf("Name of network = %s\n", ptr->ai_canonname);


        ptr = ptr->ai_next;
    }

    freeaddrinfo(info);

    return 0;
}
