#ifndef __ENGINE_EVENTS_H__
#define __ENGINE_EVENTS_H__

#include "EventManager.h"

class EvtData_Remote_Client : public BaseEventData {
    int m_sockId;
    int m_ipAddress;

public:
    static const EventType sk_EventType;

    EvtData_Remote_Client(void) {
        m_sockId = 0;
        m_ipAddress = 0;
    }

    EvtData_Remote_Client(const int socketId, const int ipaddress)
        : m_sockId(socketId), m_ipAddress(ipaddress) { }

    virtual const EventType& VGetEventType(void) const { return sk_EventType; }

    virtual IEventDataPtr VCopy() const {
        return IEventDataPtr(GCC_NEW EvtData_Remote_Client(m_sockId, m_ipAddress));
    }

    virtual const char* GetName(void) const {
        return "EvtData_Remote_Client";
    }

    virtual void VSerialize(std::ostrstream& out) const {
        out << m_sockId << " ";
        out << m_ipAddress;
    }

    virtual void VDeserialize(std::istrstream& in) {
        in >> m_sockId;
        in >> m_ipAddress;
    }

    int GetSocketId(void) const {
        return m_sockId;
    }

    int GetIpAddress(void) const {
        return m_ipAddress;
    }
};

class EvtData_Network_Player_Actor_Assignment : public BaseEventData {
    ActorId m_ActorId;
    int m_SocketId;

public:
    static const EventType sk_EventType;

    EvtData_Network_Player_Actor_Assignment() {
        m_ActorId = -1; //INVALID_ACTOR_ID;
        m_SocketId = -1;
    }

    explicit EvtData_Network_Player_Actor_Assignment(const ActorId actorId, const int socketId)
        : m_ActorId(actorId), m_SocketId(socketId)
    {
    }

    virtual const EventType& VGetEventType(void) const {
        return sk_EventType;
    }

    virtual IEventDataPtr VCopy() const { 
        return IEventDataPtr(GCC_NEW EvtData_Network_Player_Actor_Assignment(m_ActorId, m_SocketId));
    }

    virtual const char* GetName(void) const {
        return "EvtData_Network_Player_Actor_Assignment";
    }

    virtual void VSerialize(std::ostrstream& out) const {
        out << m_ActorId << " ";
        out << m_SocketId;
    }

    virtual void VDeserialize(std::istrstream& in) {
        in >> m_ActorId;
        in >> m_SocketId;
    }

    ActorId GetActorId(void) const {
        return m_ActorId;
    }

    ActorId GetSocketId(void) const {
        return m_SocketId;
    }
};

#endif
