#include "Network.h"
#include "../events/EngineEvents.h"

const char *BinaryPacket::g_Type = "BinaryPacket";

BaseSocketManager* g_pSocketManager = NULL;

BaseSocketManager* BaseSocketManager::Get() {
    return g_pSocketManager;
}

BaseSocketManager::BaseSocketManager() {
    m_Inbound = 0;
    m_Outbound = 0;
    m_MaxOpenSockets = 0;
    m_SubnetMask = 0;
    m_Subnet = 0xFFFFFFFF;
    m_NextSocketId = 0;

    g_pSocketManager = this;
    ZeroMemory(&m_WsaData, sizeof(WSADATA));
}

bool BaseSocketManager::Init() {
    if (WSAStartup(0x0202, &m_WsaData) == 0) {
        return true;
    } else {
        GCC_ERROR("WSAStartup failure!");
        return false;
    }
}

void BaseSocketManager::Shutdown() {
    while (!m_SockList.empty()) {
        delete *m_SockList.begin();
        m_SockList.pop_front();
    }

    WSACleanup();
}

int BaseSocketManager::AddSocket(NetSocket* socket) {
    socket->m_id = m_NextSocketId;
    m_SockMap[m_NextSocketId] = socket;
    ++m_NextSocketId;
    m_SockList.push_front(socket);
    if (m_SockList.size() > m_MaxOpenSockets) 
        ++m_MaxOpenSockets;

    return socket->m_id;
}

void BaseSocketManager::RemoveSocket(NetSocket* socket) {
    m_SockList.remove(socket);
    m_SockMap.erase(socket->m_id);
    SAFE_DELETE(socket);
}

NetSocket* BaseSocketManager::FindSocket(int sockId) {
    SocketIdMap::iterator i = m_SockMap.find(sockId);
    if (i == m_SockMap.end())
        return NULL;

    return (*i).second;
}

bool BaseSocketManager::Send(int sockId, std::shared_ptr<IPacket> packet) {
    NetSocket* sock = FindSocket(sockId);
    if (!sock)
        return false;

    sock->Send(packet);
    return true;
}

void BaseSocketManager::DoSelect(int pauseMicroSecs, int handleInput) {
    timeval tv;
    tv.tv_sec = 0;

    tv.tv_usec = pauseMicroSecs;

    fd_set inp_set, out_set, exc_set;
    int maxDesc;

    FD_ZERO(&inp_set);
    FD_ZERO(&out_set);
    FD_ZERO(&exc_set);

    maxDesc = 0;

    for (SocketList::iterator i = m_SockList.begin(); i != m_SockList.end(); ++i) {
        NetSocket* pSock = *i;
        if ((pSock->m_deleteFlag & 1) || pSock->m_sock == INVALID_SOCKET)
            continue;

        if (handleInput)
            FD_SET(pSock->m_sock, &inp_set);

        FD_SET(pSock->m_sock, &exc_set);

        if (pSock->VHasOutput())
            FD_SET(pSock->m_sock, &out_set);

        if ((int)pSock->m_sock > maxDesc)
            maxDesc = (int)pSock->m_sock;
    }

    int selRet = 0;

    selRet = select(maxDesc + 1, &inp_set, &out_set, &exc_set, &tv);
    if (selRet == SOCKET_ERROR) {
        GCC_ERROR("Error in DoSelect!");
        return;
    }

    if (selRet) {
        for (SocketList::iterator i = m_SockList.begin(); i != m_SockList.end(); ++i) {
            NetSocket* pSock = *i;

            if ((pSock->m_deleteFlag & 1) || pSock->m_sock == INVALID_SOCKET)
                continue;

            if (FD_ISSET(pSock->m_sock, &exc_set))
                pSock->HandleException();

            if (!(pSock->m_deleteFlag & 1) && FD_ISSET(pSock->m_sock, &out_set))
                pSock->VHandleOutput();

            if (handleInput && !(pSock->m_deleteFlag & 1) && FD_ISSET(pSock->m_sock, &inp_set)) {
                pSock->VHandleInput();
            }
        }
    }

    unsigned int timeNow = timeGetTime();

    SocketList::iterator i = m_SockList.begin();
    while (i != m_SockList.end()) {
        NetSocket* pSock = *i;
        if (pSock->m_timeOut && pSock->m_timeOut < timeNow) 
            pSock->VTimeOut();

        if (pSock->m_deleteFlag & 1) {
            switch (pSock->m_deleteFlag) {
                case 1:
                    g_pSocketManager->RemoveSocket(pSock);
                    i = m_SockList.begin();
                    break;

                case 3:
                    pSock->m_deleteFlag = 2;
                    if (pSock->m_sock != INVALID_SOCKET) {
                        closesocket(pSock->m_sock);
                        pSock->m_sock = INVALID_SOCKET;
                    }
                    break;
            }
        }
        i++;
    }
}

bool BaseSocketManager::IsInternal(unsigned int ipaddr) {
    if (!m_SubnetMask)
        return false;

    if ((ipaddr & m_SubnetMask) == m_Subnet)
        return false;

    return true;
}

unsigned int BaseSocketManager::GetHostByName(const std::string& hostName) {
    struct hostent* pHostEnt = gethostbyname(hostName.c_str());
    struct sockaddr_in tmpSockAddr;

    if (pHostEnt == NULL) {
        GCC_ERROR("Error occurred");
        return 0;
    }

    memcpy(&tmpSockAddr.sin_addr, pHostEnt->h_addr, pHostEnt->h_length);
    return ntohl(tmpSockAddr.sin_addr.s_addr);
}

const char* BaseSocketManager::GetHostByAddr(unsigned int ip) {
    static char host[32];
    
    int netip = htonl(ip);
    struct hostent* lpHostEnt = gethostbyaddr((const char*)&netip, 7, PF_INET);

    if (lpHostEnt) {
        strcpy(host, lpHostEnt->h_name);
        return host;
    }

    return NULL;
}

int BaseSocketManager::GetIpAddress(int sockId) {
    NetSocket* socket = FindSocket(sockId);
    if (socket) {
        return socket->GetIpAddress();
    } else {
        return 0;
    }
}

bool ClientSocketManager::Connect() {
    if (!BaseSocketManager::Init())
        return false;

    RemoteEventSocket* pSocket = GCC_NEW RemoteEventSocket;

    if (!pSocket->Connect(GetHostByName(m_HostName), m_Port)) {
        SAFE_DELETE(pSocket);
        return false;
    }

    AddSocket(pSocket);
    return true;
}

void GameServerListenSocket::VHandleInput() {
    unsigned int theipaddr;
    SOCKET new_sock = AcceptConnection(&theipaddr);

    int value = 1;
    //setsockopt(new_sock, SOL_SOCKET, SO_DONTLINGER, (char*)&value, sizeof(value));

    if (new_sock != INVALID_SOCKET) {
        RemoteEventSocket* sock = GCC_NEW RemoteEventSocket(new_sock, theipaddr);
        int sockId = g_pSocketManager->AddSocket(sock);
        int ipAddress = g_pSocketManager->GetIpAddress(sockId);
        std::shared_ptr<EvtData_Remote_Client> pEvent(GCC_NEW EvtData_Remote_Client(sockId, ipAddress));
        IEventManager::Get()->VQueueEvent(pEvent);
    }
}

inline void BinaryPacket::MemCpy(char const* const data, size_t size, int destOffset) {
    assert(size + destOffset <= VGetSize() - sizeof(u_long));
    memcpy(m_Data + destOffset + sizeof(u_long), data, size);
}

NetSocket::NetSocket() {
    m_sock = INVALID_SOCKET;
    m_deleteFlag = 0;
    m_sendOfs = 0;
    m_timeOut = 0;
    m_recvOfs = m_recvBegin = 0;
    m_internal = 0;
    m_bBinaryProtocol = 1;
}

NetSocket::NetSocket(SOCKET new_sock, unsigned int hostIP) {
    m_deleteFlag = 0;
    m_sendOfs = 0;
    m_timeOut = 0;
    m_recvOfs = m_recvBegin = 0;
    m_internal = 0;
    m_bBinaryProtocol = 1;

    m_timeCreated = timeGetTime();

    m_sock = new_sock;
    m_ipaddr = hostIP;

    m_internal = g_pSocketManager->IsInternal(m_ipaddr);

    //setsockopt(m_sock, SOL_SOCKET, SO_DONTLINGER, NULL, 0);
}

NetSocket::~NetSocket() {
    if (m_sock != INVALID_SOCKET) {
        closesocket(m_sock);
        m_sock = INVALID_SOCKET;
    }
}

bool NetSocket::Connect(unsigned int ip, unsigned int port, bool forceCoalesce) {
    struct sockaddr_in sa;
    int x = 1;

    if ((m_sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        return false;

    if (!forceCoalesce)
        setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, (char*)&x, sizeof(x));

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(ip);
    sa.sin_port = htons(port);

    if (connect(m_sock, (struct sockaddr*)&sa, sizeof(sa))) {
        closesocket(m_sock);
        m_sock = INVALID_SOCKET;
        return false;
    }

    return true;
}

void NetSocket::SetBlocking(bool blocking) {
    //  WINDOWS ONLY!
    //unsigned long val = blocking ? 0 : 1;
    //ioctlsocket(m_sock, FIONBIO, &val);

    //  LINUX/OSX
    if (!blocking)
        fcntl(m_sock, F_SETFL, O_NONBLOCK);
}

void NetSocket::Send(std::shared_ptr<IPacket> pkt, bool clearTimeOut) {
    if (clearTimeOut)
        m_timeOut = 0;
    m_OutList.push_back(pkt);
}

void NetSocket::VHandleOutput() {
    int fSent = 0;
    do {
        GCC_ASSERT(!m_OutList.empty());
        PacketList::iterator i = m_OutList.begin();

        std::shared_ptr<IPacket> pkt = *i;
        const char* buf = pkt->VGetData();
        int len = static_cast<int>(pkt->VGetSize());

        int rc = send(m_sock, buf + m_sendOfs, len - m_sendOfs, 0);
        if (rc > 0) {
            g_pSocketManager->AddToOutbound(rc);
            m_sendOfs += rc;
            fSent = 1;
        } else if (WSAGetLastError() != WSAEWOULDBLOCK) {
            HandleException();
            fSent = 0;
        } else {
            fSent = 0;
        }

        if (m_sendOfs == pkt->VGetSize()) {
            m_OutList.pop_front();
            m_sendOfs = 0;
        }

    } while (fSent && !m_OutList.empty());
}

void NetSocket::VHandleInput() {
    bool bPktReceived = false;
    u_long packetSize = 0;
    int rc = recv(m_sock, m_recvBuf + m_recvBegin + m_recvOfs, RECV_BUFFER_SIZE - (m_recvBegin + m_recvOfs), 0);
    if (rc == 0)
        return;

    if (rc == SOCKET_ERROR) {
        m_deleteFlag = 1;
        return;
    }

    const int hdrSize = sizeof(u_long);
    unsigned int newData = m_recvOfs + rc;
    int processedData = 0;

    while (newData > hdrSize) {
        packetSize = *(reinterpret_cast<u_long*>(m_recvBuf + m_recvBegin));
        packetSize = ntohl(packetSize);

        if (newData < packetSize)
            break;

        if (packetSize > MAX_PACKET_SIZE) {
            HandleException();
            return;
        }

        if (newData >= packetSize) {
            std::shared_ptr<BinaryPacket> pkt(GCC_NEW BinaryPacket(&m_recvBuf[m_recvBegin + hdrSize], packetSize - hdrSize));
            m_InList.push_back(pkt);
            bPktReceived = true;
            processedData += packetSize;
            newData -= packetSize;
            m_recvBegin += packetSize;
        }
    }

    g_pSocketManager->AddToInbound(rc);
    m_recvOfs = newData;

    if (bPktReceived) {
        if (m_recvOfs == 0) {
            m_recvBegin = 0;
        } else if (m_recvBegin + m_recvOfs + MAX_PACKET_SIZE > RECV_BUFFER_SIZE) {
            int leftover = m_recvOfs;
            memcpy(m_recvBuf, &m_recvBuf[m_recvBegin], m_recvOfs);
            m_recvBegin = 0;
        }
    }
}

void NetListenSocket::Init(int portnum) {
    struct sockaddr_in sa;
    int value = 1;

    if ((m_sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        GCC_ERROR("NetListenSocket Error: Init failed to created socket handle");
    }

    if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value)) == SOCKET_ERROR) {
        closesocket(m_sock);
        m_sock = INVALID_SOCKET;
        GCC_ERROR("NetListenSocket Error: Init failed to set socket options");
    }

    printf("Hey hey.  Here is the INADDR_ANY = %d\n", INADDR_ANY);
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(portnum);

    if (bind(m_sock, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR) {
        closesocket(m_sock);
        m_sock = INVALID_SOCKET;
        GCC_ERROR("NetListenSocket Error: Init failed to bind");
    }

    SetBlocking(false);

    if (listen(m_sock, 256) == SOCKET_ERROR) {
        closesocket(m_sock);
        m_sock = INVALID_SOCKET;
        GCC_ERROR("NetListenSocket Error: Init failed to listen");
    }

    port = portnum;
}

SOCKET NetListenSocket::AcceptConnection(unsigned int* pAddr) {
    SOCKET new_sock;
    struct sockaddr_in sock;
    unsigned int size = sizeof(sock);

    if ((new_sock = accept(m_sock, (struct sockaddr*)&sock, &size)) == INVALID_SOCKET)
        return INVALID_SOCKET;

    if (getpeername(new_sock, (struct sockaddr*)&sock, &size) == SOCKET_ERROR) {
        closesocket(new_sock);
        return INVALID_SOCKET;
    }

    *pAddr = ntohl(sock.sin_addr.s_addr);
    return new_sock;
}

void RemoteEventSocket::VHandleInput() {
    NetSocket::VHandleInput();

    while (!m_InList.empty()) {
        std::shared_ptr<IPacket> packet = *m_InList.begin();
        m_InList.pop_front();
        const char* buf = packet->VGetData();
        int size = static_cast<int>(packet->VGetSize());

        std::istrstream in(buf + sizeof(u_long), (size - sizeof(u_long)));

        int type;
        in >> type;

        switch (type) {
            case NetMsg_Event:
                CreateEvent(in);
                break;

            case NetMsg_PlayerLoginOk:
            {
                int serverSockId, actorId;
                in >> serverSockId;
                in >> actorId;
                std::shared_ptr<EvtData_Network_Player_Actor_Assignment> pEvent(GCC_NEW EvtData_Network_Player_Actor_Assignment(actorId, serverSockId));
                IEventManager::Get()->VQueueEvent(pEvent);
                break;
            }
            default:
            GCC_ERROR("Unknown message type.\n");
        }
    }
}

void RemoteEventSocket::CreateEvent(std::istrstream& in) {
    EventType eventType;
    in >> eventType;
    IEventDataPtr pEvent(CREATE_EVENT(eventType));

    if (pEvent) {
        pEvent->VDeserialize(in);
        IEventManager::Get()->VQueueEvent(pEvent);
    } else {
        GCC_ERROR("ERROR Unknown event type from remote: 0x%s\n", ToStr(eventType, 16).c_str());
    }
}

void NetworkEventForwarder::ForwardEvent(IEventDataPtr pEventData) {
    std::ostrstream out;

    out << static_cast<int>(RemoteEventSocket::NetMsg_Event) << " ";
    out << pEventData->VGetEventType() << " ";
    pEventData->VSerialize(out);
    out << "\r\n";

    std::shared_ptr<BinaryPacket> eventMsg(GCC_NEW BinaryPacket(out.rdbuf()->str(), out.pcount()));

    g_pSocketManager->Send(m_sockId, eventMsg);
}

