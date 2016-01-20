#include "PositionComponent.h"

const ComponentId PositionComponent::COMPONENT_ID = 333;

bool PositionComponent::VInit(const rapidjson::Value& data) {
    if (data.HasMember("x") && data["x"].IsDouble())
        x = data["x"].GetDouble();
    if (data.HasMember("y") && data["y"].IsDouble())
        y = data["y"].GetDouble();
    if (data.HasMember("z") && data["z"].IsDouble())
        z = data["z"].GetDouble();

    return true;
}

ActorComponent* CreatePosition() {
    return GCC_NEW PositionComponent;
}
