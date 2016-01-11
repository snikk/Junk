#include "Render.h"
#include "Health.h"
#include <actor/components/PositionComponent.h>
#include <io/ResourceManager.h>
#include <actor/Actor.h>

const ComponentId RenderComponent::COMPONENT_ID = 0x50cddea2;

bool RenderComponent::VInit(const rapidjson::Value& data) {
    return true;
}

void RenderComponent::draw(SpriteBatch& _spriteBatch) {
    static int textureID = ResourceManager::getTexture("images/circle.png").id;
    static float AGENT_WIDTH = 60.0f;

    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

    std::shared_ptr<PositionComponent> position = MakeStrongPtr(m_pOwner->GetComponent<PositionComponent>(PositionComponent::COMPONENT_ID));

    if (!position)
        return;

    glm::vec4 destRect;
    destRect.x = position->x;
    destRect.y = position->y;
    destRect.z = AGENT_WIDTH;
    destRect.w = AGENT_WIDTH;

    std::shared_ptr<HealthComponent> health = MakeStrongPtr(m_pOwner->GetComponent<HealthComponent>(HealthComponent::COMPONENT_ID));

    if (health) {
        float per = health->getHealthPercentage();
        ColorRGBA8 newColor(color.r * per, color.g * per, color.b * per, color.a);
        _spriteBatch.draw(destRect, uvRect, textureID, 0.0f, newColor);
    } else {
        _spriteBatch.draw(destRect, uvRect, textureID, 0.0f, color);
    }
}

ActorComponent* CreateRender() {
    return GCC_NEW RenderComponent;
}
