#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#ifndef __APPLE__
#include <GL/glew.h>
#endif

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <list>
#include <strstream>
#include <chrono>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <FastDelegate.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#if defined(_DEBUG)
#   define GCC_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#   define GCC_NEW new
#endif

#define GCC_ERROR(args...) printf(args)

#define GCC_ASSERT(expr)

#if !defined(SAFE_DELETE)
    #define SAFE_DELETE(x) if (x) delete x; x = NULL;
#endif

#define WSADESCRIPTION_LEN 256
#define WSASYS_STATUS_LEN 128

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

class Actor;
class ActorComponent;

typedef unsigned int ActorId;
typedef unsigned int ComponentId;

typedef std::shared_ptr<Actor> StrongActorPtr;
typedef std::weak_ptr<Actor> WeakActorPtr;
typedef std::shared_ptr<ActorComponent> StrongActorComponentPtr;
typedef std::weak_ptr<ActorComponent> WeakActorComponentPtr;

typedef int SOCKET;

extern void printObj(const rapidjson::Value& data);

extern long getTicks();
extern long timeGetTime();

extern void* ZeroMemory(void* ptr, size_t num);

typedef short WORD;

#define WSAEWOULDBLOCK 10035

typedef struct WSAData {
    WORD wVersion;
    WORD wHighVersion;
    char szDescription[WSADESCRIPTION_LEN + 1];
    char szSystemStatus[WSASYS_STATUS_LEN + 1];
    unsigned short iMaxSockets;
    unsigned short iMaxUpdDg;
    char* lpVendorInfo;
} WSADATA, *LPWSADATA;

extern int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
extern int WSACleanup();
extern int WSAGetLastError();

extern int closesocket(SOCKET sock);

extern std::string ToStr(int num, int base);

#include "common.tcc"

#endif
