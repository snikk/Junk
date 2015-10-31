#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "../common.h"
#include "ActorComponent.h"

typedef unsigned int ActorId;

class Actor {
    friend class ActorFactory;

public:
    typedef std::map<ComponentId, StrongActorComponentPtr> ActorComponents;

private:
    ActorId m_id;
    ActorComponents m_components;
    std::string m_type;

public:
    explicit Actor(ActorId id);
    ~Actor(void);

    bool Init(const rapidjson::Value& val);
    void PostInit(void);
    void Destroy(void);
    void Update(int deltaMs);

    ActorId GetId(void) const { return m_id; }

    template <class ComponentType>
    std::weak_ptr<ComponentType> GetComponent(ComponentId id) {
        ActorComponents::iterator findIt = m_components.find(id);
        if (findIt != m_components.end()) {
            StrongActorComponentPtr pBase(findIt->second);
            std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));
            std::weak_ptr<ComponentType> pWeakSub(pSub);
            return pWeakSub;
        } else {
            return std::weak_ptr<ComponentType>();
        }
    }

    const ActorComponents* GetComponents() { return &m_components; }
    void AddComponent(StrongActorComponentPtr pComponent);
};

#endif
