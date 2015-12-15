#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__ 

#include "../common.h"

typedef unsigned long EventType;

class IEventData;

typedef std::shared_ptr<IEventData> IEventDataPtr;
typedef fastdelegate::FastDelegate1<IEventDataPtr> EventListenerDelegate;

extern GenericObjectFactory<IEventData, EventType> g_eventFactory;
#define REGISTER_EVENT(eventClass) g_eventFactory.Register<eventClass>(eventClass::sk_EventType)
#define CREATE_EVENT(eventType) g_eventFactory.Create(eventType)

class IEventData {
public:
    virtual const EventType& VGetEventType(void) const = 0;
    virtual float VGetTimeStamp(void) const = 0;
    virtual void VSerialize(std::ostrstream& out) const = 0;
    virtual void VDeserialize(std::istrstream& in) = 0;
    virtual IEventDataPtr VCopy(void) const = 0;
    virtual const char* GetName(void) const = 0;
};

class BaseEventData : public IEventData {
    const float m_timeStamp;

public:
    explicit BaseEventData(const float timeStamp = 0.0f) : m_timeStamp(timeStamp) { }
    virtual ~BaseEventData(void) { }

    virtual const EventType& VGetEventType(void) const = 0;
    float VGetTimeStamp(void) const { return m_timeStamp; }

    virtual void VSerialize(std::ostrstream &out) const { }
};

class IEventManager {
public:
    enum eConstants { kINFINITE = 0xFFFFFFFF };

    explicit IEventManager(const char* pName, bool setAsGlobal);
    virtual ~IEventManager(void);

    virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;

    virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;

    virtual bool VTriggerEvent(const IEventDataPtr& pEvent) const = 0;

    virtual bool VQueueEvent(const IEventDataPtr& pEvent) = 0;

    virtual bool VAbortEvent(const EventType& type, bool allOfType = false) = 0;

    virtual bool VTickVUpdate(unsigned long maxMillis = kINFINITE) = 0;

    static IEventManager* Get(void);
};

const unsigned int EVENTMANAGER_NUM_QUEUES = 2;

class EventManager : public IEventManager {
    typedef std::list<EventListenerDelegate> EventListenerList;
    typedef std::map<EventType, EventListenerList> EventListenerMap;
    typedef std::list<IEventDataPtr> EventQueue;

    EventListenerMap m_eventListeners;
    EventQueue m_queues[EVENTMANAGER_NUM_QUEUES];
    int m_activeQueue;

public:
    explicit EventManager(const char* pName, bool setAsGlobal);
    virtual ~EventManager(void) { }

    virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type);
    virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type);

    virtual bool VTriggerEvent(const IEventDataPtr& pEvent) const;
    virtual bool VQueueEvent(const IEventDataPtr& pEvent);
    virtual bool VAbortEvent(const EventType& pEvent, bool allOfType = false);
    virtual bool VTickVUpdate(unsigned long maxMillis = kINFINITE);
};

#endif

