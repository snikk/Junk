#include "AI.h"
#include <io/InputManager.h>
#include <actor/Actor.h>

const ComponentId PlayerComponent::COMPONENT_ID = 0xd4707054;

bool PlayerComponent::VInit(const rapidjson::Value& data) {
    return true;
}

void PlayerComponent::VUpdate(int deltaMs) {
    auto pos = pPosition.lock();
    auto deltaTime = (deltaMs / 1000.0f) * 200;

    if (InputManager::instance().isKeyDown(forward)) {
        pos->y = pos->y + (speed * deltaTime);
    } else if (InputManager::instance().isKeyDown(backward)) {
        pos->y = pos->y - (speed * deltaTime);
    }
    if (InputManager::instance().isKeyDown(left)) {
        pos->x = pos->x - (speed * deltaTime);
    } else if (InputManager::instance().isKeyDown(right)) {
        pos->x = pos->x + (speed * deltaTime);
    }
}

void PlayerComponent::VPostInit(void) {
    pHealth = m_pOwner->GetComponent<HealthComponent>(HealthComponent::COMPONENT_ID);
    pPosition = m_pOwner->GetComponent<PositionComponent>(PositionComponent::COMPONENT_ID);
}

ActorComponent* CreatePlayerAI() {
    return GCC_NEW PlayerComponent;
}
