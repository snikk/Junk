#ifndef __ACTOR_H__
#define __ACTOR_H__

class Actor {
    friend class ActorFactory;

    typedef std::map<ComponentId, StrongActorComponentPtr> ActorComponents;

    ActorId m_id;
    ActorComponents m_components;
    std::string m_type;

public:
    explicit Actor(ActorId id);
    ~Actor(void);

    bool Init();
    void PostInit(void);
    void Destroy(void);
    void Update(int deltaMs);

    ActorId GetId(void) const { return m_id; }

    template <class ComponentType>
    weak_ptr<ComponentType> GetComponent(ComponentId id) {
        ActorComponents::iterator findIt = m_components.find(id);
        if (findIt != m_components.end()) {
            StrongActorComponentPtr pBase(findIt->second);
            shared_ptr<ComponentType> pSub(std::tr1::static_pointer_cast<ComponentType>(pBase));
            weak_ptr<ComponentType> pWeakSub(pSub);
            return pWeakSub;
        } else {
            return weak_ptr<ComponentType>();
        }
    }

    const ActorComponents* GetComponents() { return &m_components; }
    void AddComponent(StrongActorComponentPtr pComponent);
};

#endif
