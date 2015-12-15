#include "HealthComponent.h"

const ComponentId HealthComponent::COMPONENT_ID = 8989898;

bool HealthComponent::VInit(const rapidjson::Value& data) {
    if (data.HasMember("health") && data["health"].IsDouble())
        health = data["health"].GetDouble();

    return true;
}

ActorComponent* CreateHealth() {
    return GCC_NEW HealthComponent;
}
