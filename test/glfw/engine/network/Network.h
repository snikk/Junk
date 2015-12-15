#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "../common.h"
#include "../events/EventManager.h"

#define MAX_PACKET_SIZE (256)
#define RECV_BUFFER_SIZE (MAX_PACKET_SIZE * 512)

class NetSocket;
class NetListenSocket;
class IPacket;

class BaseSocketManager {
public:
    BaseSocketManager();
    virtual ~BaseSocketManager() { Shutdown(); }

    bool Init();
    void Shutdown();

    int AddSocket(NetSocket* socket);
    void RemoveSocket(NetSocket* socket);

    bool Send(int sockId, std::shared_ptr<IPacket> packet);
    void DoSelect(int pauseMicroSecs, int handleInput = 1);

    void SetSubnet(unsigned int subnet, unsigned int subnetMask) {
        m_Subnet = subnet;
        m_SubnetMask = subnetMask;
    }

    bool IsInternal(unsigned int ipaddr);

    unsigned int GetHostByName(const std::string& hostName);
    const char* GetHostByAddr(unsigned int ip);

    void AddToOutbound(int rc) { m_Outbound += rc; }
    void AddToInbound(int rc) { m_Inbound += rc; }

    int GetIpAddress(int sockId);

    static BaseSocketManager* Get();

protected:
    WSADATA m_WsaData;

    typedef std::list<NetSocket*> SocketList;
    typedef std::map<int, NetSocket*> SocketIdMap;

    SocketList m_SockList;
    SocketIdMap m_SockMap;

    int m_NextSocketId;

    unsigned int m_Inbound;
    unsigned int m_Outbound;
    unsigned int m_MaxOpenSockets;

    unsigned int m_SubnetMask;
    unsigned int m_Subnet;

    NetSocket* FindSocket(int sockId);
};

class ClientSocketManager : public BaseSocketManager {
    std::string m_HostName;
    unsigned int m_Port;

    public:
    ClientSocketManager(const std::string& hostName, unsigned int port) {
        m_HostName = hostName;
        m_Port = port;
    }

    bool Connect();
};

class NetSocket {
    friend class BaseSocketManager;
    typedef std::list<std::shared_ptr<IPacket> > PacketList;

public:
    NetSocket();
    NetSocket(SOCKET new_sock, unsigned int hostIP);
    virtual ~NetSocket();

    bool Connect(unsigned int ip, unsigned int port, bool forceCoalesce = 0);
    void SetBlocking(bool blocking);
    void Send(std::shared_ptr<IPacket> pkt, bool clearTimeOut = 1);

    virtual int VHasOutput() { return !m_OutList.empty(); }
    virtual void VHandleOutput();
    virtual void VHandleInput();
    virtual void VTimeOut() { m_timeOut = 0; }
    void HandleException() { m_deleteFlag |= 1; }
    void SetTimeOut(unsigned int ms = 45 * 1000) { m_timeOut = timeGetTime() + ms; }
    int GetIpAddress() { return m_ipaddr; }

protected:
    SOCKET m_sock;
    int m_id;

    int m_deleteFlag;

    PacketList m_OutList;
    PacketList m_InList;

    char m_recvBuf[RECV_BUFFER_SIZE];
    unsigned int m_recvOfs, m_recvBegin;
    bool m_bBinaryProtocol;

    int m_sendOfs;
    unsigned int m_timeOut;
    unsigned int m_ipaddr;

    int m_internal;
    int m_timeCreated;
};

class NetListenSocket : public NetSocket {
public:
    NetListenSocket() { };
    NetListenSocket(int portnum) { port = 0; Init(portnum); }

    void Init(int portnum);
    SOCKET AcceptConnection(unsigned int* pAddr);

    unsigned short port;
};

class RemoteEventSocket : public NetSocket {
public:
    enum {
        NetMsg_Event, 
        NetMsg_PlayerLoginOk, 
    };

    RemoteEventSocket(SOCKET new_sock, unsigned int hostIP) : NetSocket(new_sock, hostIP) { }

    RemoteEventSocket() { };

    virtual void VHandleInput();

protected:
    void CreateEvent(std::istrstream& in);
};

class GameServerListenSocket : public NetListenSocket {
public:
    GameServerListenSocket(int portnum) { Init(portnum); }
    void VHandleInput();
};

class IPacket {
public:
    virtual char const* const VGetType() const = 0;
    virtual char const* const VGetData() const = 0;
    virtual u_long VGetSize() const = 0;
    virtual ~IPacket() { }
};

class BinaryPacket : public IPacket {
protected:
    char* m_Data;

public:
    inline BinaryPacket(char const* const data, u_long size);
    inline BinaryPacket(u_long size);

    virtual ~BinaryPacket() { SAFE_DELETE(m_Data); }
    virtual char const* const VGetType() const { return g_Type; }
    virtual char const* const VGetData() const { return m_Data; }
    virtual u_long VGetSize() const { return ntohl(*(u_long*)m_Data); }
    inline void MemCpy(char const* const data, size_t size, int desOffset);

    static const char* g_Type;
};

inline BinaryPacket::BinaryPacket(char const* const data, u_long size) {
    m_Data = GCC_NEW char[size + sizeof(u_long)];
    assert(m_Data);
    *(u_long*) m_Data = htonl(size + sizeof(u_long));
    memcpy(m_Data + sizeof(u_long), data, size);
}

inline BinaryPacket::BinaryPacket(u_long size) {
    m_Data = GCC_NEW char[size + sizeof(u_long)];
    assert(m_Data);
    *(u_long*)m_Data = htonl(size + sizeof(u_long));
}

class NetworkEventForwarder {
public:
    NetworkEventForwarder(int sockId) { m_sockId = sockId; }
    void ForwardEvent(IEventDataPtr pEventData);
protected:
    int m_sockId;
};

#endif
