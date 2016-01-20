#include "../common.h"
#include "Actor.h"

Actor::Actor(ActorId id) {
    m_id = id;
    m_type = "Unknown";
}

Actor::~Actor(void) {
}

bool Actor::Init(const rapidjson::Value& val) {
    printf("Actor init function!\n");
    if (val.IsObject()) {
        if (val["type"].IsString()) {
            m_type = std::string(val["type"].GetString());
        } else {
            printf("Actor Error: Must have a type\n");
            return false;
        }
    } else {
        printf("Actor Error: JSON must be an object.\n");
        return false;
    }
    return true;
}

void Actor::PostInit(void) {
    for (ActorComponents::iterator it = m_components.begin(); it != m_components.end(); ++it) {
        it->second->VPostInit();
    }
}

void Actor::Destroy(void) {
    m_components.clear();
}

void Actor::Update(int deltaMs) {
    for (ActorComponents::iterator it = m_components.begin(); it != m_components.end(); ++it) {
        it->second->VUpdate(deltaMs);
    }
}

void Actor::AddComponent(StrongActorComponentPtr pComponent) {
    m_components.insert(std::make_pair(pComponent->VGetId(), pComponent));
}
