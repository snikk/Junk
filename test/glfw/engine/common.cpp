#include "common.h"

void printObj(const rapidjson::Value& data) {
    if (data.IsObject()) {
        for (rapidjson::Value::ConstMemberIterator itr = data.MemberBegin(); itr != data.MemberEnd(); ++itr) {
            printf("obj[%s] = ", itr->name.GetString());
            switch (itr->value.GetType()) {
                case 0:
                    printf("IsNull!");
                    break;
                case 1:
                    printf("False");
                    break;
                case 2:
                    printf("True");
                    break;
                case 3:
                    // IsObject
                    printf("{\n");
                    printObj(itr->value);
                    printf("}\n");
                    break;
                case 4:
                    // IsArray
                    printf("[\n");
                    printObj(itr->value);
                    printf("]\n");
                    break;
                case 5:
                    printf("%s", itr->value.GetString());
                    break;
                case 6:
                    printf("%d", itr->value.GetInt());
                    break;
            }

            printf("\n");
        }
    } else {
        for (rapidjson::SizeType i = 0; i < data.Size(); i++) {
            printf("{\n");
            printObj(data[i]);
            printf("}, \n");
        }
    }
}

extern long getTicks() {
    auto start = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count();
}

extern long timeGetTime() {
    auto start = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count();
}

extern void* ZeroMemory(void* ptr, size_t num) {
    return memset(ptr, 0, num);
}

extern int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData) {
    return 0;
}

extern int WSACleanup() {
    return 0;
}

extern int WSAGetLastError() {
    if (errno == EWOULDBLOCK)
        return WSAEWOULDBLOCK;

    return errno;
}

extern int closesocket(SOCKET sock) {
    return close(sock);
}

extern std::string ToStr(int num, int base) {
    char str[33];
    memset(str, 0, 33);
    snprintf(str, 33, "%d(%d)", num, base);

    return (std::string(str));
}

