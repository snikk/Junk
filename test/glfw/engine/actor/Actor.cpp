#include "../common.h"
#include "Actor.h"

Actor::Actor(ActorId id) {
    m_id = id;
    m_type = "Unknown";
}

Actor::~Actor(void) {
    printf("Destroying Actor | m_id = %d\n", m_id);
}

bool Actor::Init() {
    return true;
}

void Actor::PostInit(void) {
    for (ActorComponents::iterator it = m_components.begin(); it != m_components.end(), ++it) {
        it->second->VPostInit();
    }
}

void Actor::Destory(void) {
    m_components.clear();
}

void Actor::Update(int deltaMs) {
    for (ActorComponents::iterator it = m_components.begin(); it != m_components.end(), ++it) {
        it->second->VUpdate(deltaMs);
    }
}

void Actor::AddComponent(StrongActorComponentPtr pComponent) {
    m_components.insert(std::make_pair(pComponent->VGetId(), pComponent));
}
