#ifndef __AI_H__
#define __AI_H__

#include <actor/ActorComponent.h>
#include <actor/components/PositionComponent.h>
#include "Health.h"

class PlayerComponent : public ActorComponent {
public:
    const static ComponentId COMPONENT_ID;

    virtual bool VInit(const rapidjson::Value& data);
    virtual ComponentId VGetId(void) const { return COMPONENT_ID; };
    virtual ComponentId VGetComponentId(void) const { return VGetId(); }
    virtual void VPostInit(void);
    virtual void VUpdate(int deltaMs);

    float speed;

    int forward;
    int backward;
    int left;
    int right;

private:
    std::weak_ptr<HealthComponent> pHealth;
    std::weak_ptr<PositionComponent> pPosition;
};

extern ActorComponent* CreatePlayerAI();

#endif
