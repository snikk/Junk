#ifndef __HEALTH_H__
#define __HEALTH_H__

#include <actor/ActorComponent.h>

class HealthComponent : public ActorComponent {
public:
    const static ComponentId COMPONENT_ID;

    virtual bool VInit(const rapidjson::Value& data);
    virtual ComponentId VGetId(void) const { return COMPONENT_ID; };
    virtual ComponentId VGetComponentId(void) const { return VGetId(); }
    virtual void VPostInit(void) { }

    float maxHealth;
    float currentHealth;

    float getHealthPercentage() const { return maxHealth / currentHealth; }
};

extern ActorComponent* CreateHealth();

#endif
