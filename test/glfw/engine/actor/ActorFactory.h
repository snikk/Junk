#ifndef __ACTOR_FACTORY_H__
#define __ACTOR_FACTORY_H__

#include <map>
#include <string>
#include "Actor.h"
#include <rapidjson/document.h>
#include "../common.h"
#include "ActorComponent.h"

typedef ActorComponent *(*ActorComponentCreator)(void);
typedef std::map<std::string, ActorComponentCreator> ActorComponentCreatorMap;

class ActorFactory {
    ActorId m_lastActorId;

protected:
    ActorComponentCreatorMap m_actorComponentCreators;

public:
    ActorFactory(void);
    StrongActorPtr CreateActor(const char* actorResource);

    void RegisterComponent(std::string name, ActorComponentCreator creator);

protected:
    virtual StrongActorComponentPtr CreateComponent(const rapidjson::Value& data);

    ActorId GetNextActorId(void) { ++m_lastActorId; return m_lastActorId; }
};

#endif
