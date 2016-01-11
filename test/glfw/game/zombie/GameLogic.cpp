#include "GameLogic.h"
#include <actor/components/PositionComponent.h>
#include "actor/components/Render.h"
#include "actor/components/Health.h"
#include "actor/components/AI.h"

GameLogic::GameLogic() {
}

GameLogic::~GameLogic() {
    for (auto it = m_actors.begin(); it != m_actors.end(); ++it)
        it->second->Destroy();
    m_actors.clear();
}

WeakActorPtr GameLogic::VGetActor(const ActorId actorId) {
    auto it = m_actors.find(actorId);
    if (it != m_actors.end())
        return WeakActorPtr(it->second);
    return WeakActorPtr();
}

void GameLogic::VDestroyActor(const ActorId actorId) {
    auto it = m_actors.find(actorId);
    if (it != m_actors.end())
        m_actors.erase(it);
}

WeakActorPtr GameLogic::CreatePlayer(float speed, glm::vec2 pos, Camera2D* camera, std::vector<Bullet>* bullets) {
    StrongActorPtr pPlayer(m_actorFactory.CreateActor());

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

    m_actors.insert(std::make_pair(pPlayer->GetId(), pPlayer));

    return WeakActorPtr(pPlayer);
}

WeakActorPtr GameLogic::CreateHuman() {
    StrongActorPtr pHuman(m_actorFactory.CreateActor());

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

WeakActorPtr GameLogic::CreateZombie() {
    StrongActorPtr pZombie(m_actorFactory.CreateActor());

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
