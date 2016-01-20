#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <actor/ActorComponent.h>

class InventoryComponent : public ActorComponent {
public:
    const static ComponentId COMPONENT_ID;

    virtual bool VInit(const rapidjson::Value& data);
    virtual ComponentId VGetId(void) const { return COMPONENT_ID; };
    virtual ComponentId VGetComponentId(void) const { return VGetId(); }
    virtual void VPostInit(void) { }

    int currentGunIndex = -1;
    std::vector<StrongActorPtr> guns;

    virtual WeakActorPtr GetCurrentGun();
};

extern ActorComponent* CreateInventory();


#endif
