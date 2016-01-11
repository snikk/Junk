#include "GameActorFactory.h"
#include <actor/components/PositionComponent.h>
#include "components/Render.h"
#include "components/Health.h"
#include "components/AI.h"

StrongActorPtr GameActorFactory::CreatePlayer(float speed, glm::vec2 pos, Camera2D* camera, std::vector<Bullet>* bullets) {
    StrongActorPtr pPlayer(GCC_NEW Actor(GetNextActorId()));

    std::shared_ptr<PositionComponent> pPosition((PositionComponent *) CreatePosition());
    if (pPosition) {
        pPosition->x = pos.x;
        pPosition->y = pos.y;
        pPosition->z = 0.0f;

        pPlayer->AddComponent(pPosition);
        pPosition->SetOwner(pPlayer);
    } else {
        return StrongActorPtr();
    }

    std::shared_ptr<HealthComponent> pHealth((HealthComponent *) CreateHealth());
    if (pHealth) {
        pHealth->currentHealth = 150.0f;
        pHealth->maxHealth = 150.0f;

        pPlayer->AddComponent(pHealth);
        pHealth->SetOwner(pPlayer);
    } else {
        return StrongActorPtr();
    }

    std::shared_ptr<RenderComponent> pRender((RenderComponent *) CreateRender());
    if (pRender) {
        pRender->color.r = 0;
        pRender->color.g = 0;
        pRender->color.b = 185;
        pRender->color.a = 255;

        pPlayer->AddComponent(pRender);
        pRender->SetOwner(pPlayer);
    } else {
        return StrongActorPtr();
    }

    std::shared_ptr<PlayerComponent> pPlayerAI((PlayerComponent *) CreatePlayerAI());
    if (pPlayerAI) {
        pPlayerAI->speed = speed;

        pPlayerAI->forward = GLFW_KEY_W;
        pPlayerAI->backward = GLFW_KEY_S;
        pPlayerAI->left = GLFW_KEY_A;
        pPlayerAI->right = GLFW_KEY_D;

        pPlayer->AddComponent(pPlayerAI);
        pPlayerAI->SetOwner(pPlayer);
    } else {
        return StrongActorPtr();
    }

    pPlayer->PostInit();

    return pPlayer;
}

StrongActorPtr GameActorFactory::CreateHuman() {
    StrongActorPtr pHuman(GCC_NEW Actor(GetNextActorId()));

    std::shared_ptr<PositionComponent> pPosition((PositionComponent *) CreatePosition());
    if (pPosition) {
        pPosition->x = 123.0f;
        pPosition->y = 456.0f;
        pPosition->z = 789.0f;

        pHuman->AddComponent(pPosition);
        pPosition->SetOwner(pHuman);
    } else {
        return StrongActorPtr();
    }

    return pHuman;
}

StrongActorPtr GameActorFactory::CreateZombie() {
    StrongActorPtr pZombie(GCC_NEW Actor(GetNextActorId()));

    std::shared_ptr<PositionComponent> pPosition((PositionComponent *) CreatePosition());
    if (pPosition) {
        pPosition->x = 999.0f;
        pPosition->y = 888.0f;
        pPosition->z = 777.0f;

        pZombie->AddComponent(pPosition);
        pPosition->SetOwner(pZombie);
    } else {
        return StrongActorPtr();
    }

    return pZombie;
}

