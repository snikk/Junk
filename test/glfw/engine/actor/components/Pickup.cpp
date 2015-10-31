#include "Pickup.h"

const ComponentId AmmoPickup::COMPONENT_ID = 111;
const ComponentId HealthPickup::COMPONENT_ID = 222;

bool AmmoPickup::VInit(const rapidjson::Value& data) {
    if (data.IsObject()) {
        printObj(data);
    } else {
        printf("Component Error: Must be an object!\n");
        return false;
    }
    return true;
}

void AmmoPickup::VApply(WeakActorPtr pActor) {
}

bool HealthPickup::VInit(const rapidjson::Value& data) {
    if (data.IsObject()) {
        printObj(data);
    } else {
        printf("Component Error: Must be an object!\n");
        return false;
    }
    return true;
}

void HealthPickup::VApply(WeakActorPtr pActor) {
}

ActorComponent* CreateAmmoPickup() {
    return GCC_NEW AmmoPickup;
}

ActorComponent* CreateHealthPickup() {
    return GCC_NEW HealthPickup;
}

