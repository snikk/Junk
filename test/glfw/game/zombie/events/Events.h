#ifndef __ZOMBIE_EVENTS_H__
#define __ZOMBIE_EVENTS_H__

#include <events/EventManager.h>
#include <actor/Actor.h>

class EvtData_Destroy_Actor : public BaseEventData {
    ActorId m_id;

public:
    static const EventType sk_EventType;

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

#endif
