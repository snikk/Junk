#ifndef __HEALTH_COMPONENT_H_
#define __HEALTH_COMPONENT_H_

#include "../ActorComponent.h"

class HealthComponent : public ActorComponent {
public:
    const static ComponentId COMPONENT_ID;

    virtual bool VInit(const rapidjson::Value& data);
    virtual ComponentId VGetId(void) const { return COMPONENT_ID; };
    virtual ComponentId VGetComponentId(void) const { return VGetId(); }
    virtual void VPostInit(void) { printf("Total Health = %f\n", health); }

    float health = 0.0f;
};

extern ActorComponent* CreateHealth();

#endif
