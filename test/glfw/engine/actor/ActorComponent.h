#ifndef __ACTOR_COMPONENT_H__
#define __ACTOR_COMPONENT_H__

#include <rapidjson/document.h>
#include "../common.h"

typedef unsigned int ComponentId;

class ActorComponent {
    friend class ActorFactory;

protected:
    StrongActorPtr m_pOwner;

public:
    virtual ~ActorComponent(void) { }

    virtual bool VInit(const rapidjson::Value& data) = 0;
    virtual void VPostInit(void) { }
    virtual void VUpdate(int deltaMs) { }

    virtual ComponentId VGetComponentId(void) const = 0;

    virtual ComponentId VGetId(void) const = 0;

    void SetOwner(StrongActorPtr pOwner) { m_pOwner = pOwner; }
};

#endif
