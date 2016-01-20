#include "Inventory.h"

const ComponentId InventoryComponent::COMPONENT_ID = 0xfa71b060;

bool InventoryComponent::VInit(const rapidjson::Value& data) {
    return true;
}

WeakActorPtr InventoryComponent::GetCurrentGun() {
    if (currentGunIndex >= 0 && currentGunIndex < guns.size())
        return WeakActorPtr(guns[currentGunIndex]);

    return WeakActorPtr();
}

ActorComponent* CreateInventory() {
    return GCC_NEW InventoryComponent;
}
