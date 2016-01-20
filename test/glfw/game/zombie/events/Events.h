#ifndef __ZOMBIE_EVENTS_H__
#define __ZOMBIE_EVENTS_H__

#include <events/EventManager.h>
#include <actor/Actor.h>

class EvtData_Destroy_Actor : public BaseEventData {
    ActorId m_id;

public:
    static const EventType sk_EventType = 0xd32340ca;

    explicit EvtData_Destroy_Actor(ActorId id = -1) : m_id(id) { }
    explicit EvtData_Destroy_Actor(std::istrstream& in) {
        in >> m_id;
    }

    virtual const EventType& VGetEventType(void) const {
        return sk_EventType;
    }

    virtual IEventDataPtr VCopy(void) const {
        return IEventDataPtr(GCC_NEW EvtData_Destroy_Actor(m_id));
    }

    virtual void VSerialize(std::ostrstream &out) const {
        out << m_id;
    }

    virtual void VDeserialize(std::istrstream& in) {
        in >> m_id;
    }

    virtual const char* GetName(void) const {
        return "EvtData_Destroy_Actor";
    }

    ActorId GetId(void) const { return m_id; }
};

class EvtData_Fire : public BaseEventData {
    ActorId m_id;
    ActorId m_gun;

public:
    static const EventType sk_EventType = 0x814a9705;

    explicit EvtData_Fire(ActorId id = -1, ActorId gun = -1) : m_id(id), m_gun(gun) { }
    explicit EvtData_Fire(std::istrstream& in) {
        in >> m_id;
        in >> m_gun;
    }

    virtual const EventType& VGetEventType(void) const {
        return sk_EventType;
    }

    virtual IEventDataPtr VCopy(void) const {
        return IEventDataPtr(GCC_NEW EvtData_Fire(m_id));
    }

    virtual void VSerialize(std::ostrstream &out) const {
        out << m_id;
        out << m_gun;
    }

    virtual void VDeserialize(std::istrstream& in) {
        in >> m_id;
        in >> m_gun;
    }

    virtual const char* GetName(void) const {
        return "EvtData_Fire";
    }

    ActorId GetOwnerId(void) const { return m_id; }
    ActorId GetGunId(void) const { return m_gun; }
};

#endif
