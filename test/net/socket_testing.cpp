#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char** argv) {
    unsigned long ipAddress = inet_addr("128.64.16.2");

    struct in_addr addr;
    addr.s_addr = htonl(0x88482818);

    char ipAddressString[16];
    strcpy(ipAddressString, inet_ntoa(addr));

    printf("0x%08x 0x%08x %s\n:", ipAddress, addr.s_addr, ipAddressString);

    printf("\n\n\n-------------------------------------------\n\n\n");

    const char* host = "notgoingtohappenftp.microsoft.com";
    struct hostent* pHostEnt = gethostbyname(host);

    if (pHostEnt == NULL) {
        fprintf(stderr, "No such host\n");
    } else {
        struct sockaddr_in addr;
        memcpy(&addr.sin_addr, pHostEnt->h_addr, pHostEnt->h_length);
        printf("Address of %s is 0x%08x\n", host, ntohl(addr.sin_addr.s_addr));
    }

    return 0;
}
