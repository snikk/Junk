#ifndef __PICKUP_H__
#define __PICKUP_H__

#include "../PickupInterface.h"

class AmmoPickup : public PickupInterface {
public:
    const static ComponentId COMPONENT_ID;

    virtual bool VInit(const rapidjson::Value& data);
    virtual void VApply(WeakActorPtr pActor);
    virtual ComponentId VGetId(void) const { return 1; };
};

class HealthPickup : public PickupInterface {
public:
    const static ComponentId COMPONENT_ID;

    virtual bool VInit(const rapidjson::Value& data);
    virtual void VApply(WeakActorPtr pActor);
    virtual ComponentId VGetId(void) const { return 2; };
};

extern ActorComponent* CreateAmmoPickup();
extern ActorComponent* CreateHealthPickup();

#endif
