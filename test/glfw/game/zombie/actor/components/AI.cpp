#include "AI.h"
#include <io/InputManager.h>
#include <actor/Actor.h>
#include <actor/components/PositionComponent.h>
#include "Render.h"
#include "Health.h"
#include "Inventory.h"
#include "../../events/Events.h"

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

const ComponentId PlayerComponent::COMPONENT_ID = 0xd4707054;
const ComponentId BulletComponent::COMPONENT_ID = 0x70ed6f44;
const ComponentId GunComponent::COMPONENT_ID = 0x2eaf60ab;

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

    auto inventory = m_pOwner->GetComponent<InventoryComponent>(InventoryComponent::COMPONENT_ID).lock();
    if (inventory) {
        if (InputManager::instance().isKeyDown(GLFW_KEY_1) && inventory->guns.size() > 0) {
            inventory->currentGunIndex = 0;
        } else if (InputManager::instance().isKeyDown(GLFW_KEY_2) && inventory->guns.size() > 1) {
            inventory->currentGunIndex = 1;
        } else if (InputManager::instance().isKeyDown(GLFW_KEY_3) && inventory->guns.size() > 2) {
            inventory->currentGunIndex = 2;
        }

        if (inventory->currentGunIndex >= 0) {
            if (InputManager::instance().isKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
                auto gun = inventory->GetCurrentGun().lock();
                auto gunComp = gun->GetComponent<GunComponent>(GunComponent::COMPONENT_ID).lock();
                if (gunComp && gunComp->CanFire()) {
                    gunComp->Reset();
                    std::shared_ptr<EvtData_Fire> pFire(GCC_NEW EvtData_Fire(m_pOwner->GetId(), gun->GetId()));
                    IEventManager::Get()->VQueueEvent(pFire);
                }
            }
        }
    }

    auto cam = camera.lock();
    if (cam) {
        glm::vec2 mouseCoords = cam->convertScreenToWorld(InputManager::instance().getMouseCoords());

        center = glm::vec2(pos->x + AGENT_RADIUS, pos->y + AGENT_RADIUS);

        direction = glm::normalize(mouseCoords - center);
    }

}

void PlayerComponent::VPostInit(void) {
    pHealth = m_pOwner->GetComponent<HealthComponent>(HealthComponent::COMPONENT_ID);
    pPosition = m_pOwner->GetComponent<PositionComponent>(PositionComponent::COMPONENT_ID);
}

bool BulletComponent::VInit(const rapidjson::Value& data) {
    return true;
}

void BulletComponent::VPostInit(void) {
    pPosition = m_pOwner->GetComponent<PositionComponent>(PositionComponent::COMPONENT_ID);
}

void BulletComponent::VUpdate(int deltaMs) {
    auto deltaTime = (deltaMs / 1000.0f) * 200;
    auto pos = pPosition.lock();
    if (pos) {
        pos->x = pos->x + (direction.x * speed * deltaTime);
        pos->y = pos->y + (direction.y * speed * deltaTime);
    }
}

bool GunComponent::VInit(const rapidjson::Value& data) {
    return true;
}

void GunComponent::VPostInit(void) {
}

void GunComponent::VUpdate(int deltaMs) {
    frameCounter += deltaMs;
}

ActorComponent* CreatePlayerAI() {
    return GCC_NEW PlayerComponent;
}

ActorComponent* CreateBulletComp() {
    return GCC_NEW BulletComponent;
}

ActorComponent* CreateGunComp() {
    return GCC_NEW GunComponent;
}
