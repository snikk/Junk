#include "Health.h"

const ComponentId HealthComponent::COMPONENT_ID = 0x234b43f8;

bool HealthComponent::VInit(const rapidjson::Value& data) {
    return true;
}

ActorComponent* CreateHealth() {
    return GCC_NEW HealthComponent;
}
