#include "GameLogic.h"
#include <actor/components/PositionComponent.h>
#include "actor/components/Render.h"
#include "actor/components/Health.h"
#include "actor/components/AI.h"
#include "actor/components/Inventory.h"
#include <random>
#include <glm/gtx/rotate_vector.hpp>

const float RADIANS = M_PI / 180.0;

GameLogic::GameLogic() {
}

GameLogic::~GameLogic() {
    for (auto it = m_actors.begin(); it != m_actors.end(); ++it)
        it->second->Destroy();
    m_actors.clear();
    Destroy();
}

void GameLogic::Init() {
    IEventManager::Get()->VAddListener(fastdelegate::MakeDelegate(this, &GameLogic::eventHandler), EvtData_Fire::sk_EventType);
}

void GameLogic::Destroy() {
    IEventManager::Get()->VRemoveListener(fastdelegate::MakeDelegate(this, &GameLogic::eventHandler), EvtData_Fire::sk_EventType);
}

void GameLogic::eventHandler(IEventDataPtr pEventData) {
    static std::mt19937 randomEngine(time(nullptr));
    switch (pEventData->VGetEventType()) {
        case EvtData_Fire::sk_EventType:
            auto pFire = std::static_pointer_cast<EvtData_Fire>(pEventData);

            auto owner = VGetActor(pFire->GetOwnerId()).lock();
            auto gun = VGetActor(pFire->GetGunId()).lock();
            if (owner && gun) {
                auto ownerAi = owner->GetComponent<PlayerComponent>(PlayerComponent::COMPONENT_ID).lock();
                auto gunComp = gun->GetComponent<GunComponent>(GunComponent::COMPONENT_ID).lock();
                if (ownerAi && gunComp) {
                    // For offsetting the accuracy
                    std::uniform_real_distribution<float> randRotate(-gunComp->spread, gunComp->spread);
                    std::uniform_real_distribution<float> randSpeed(gunComp->bulletSpeed * 0.8, gunComp->bulletSpeed * 1.2);

                    for (int i = 0; i < gunComp->bulletsPerShot; i++) {
                        CreateBullet(owner->GetId(), 
                                     ownerAi->center, 
                                     glm::rotate(ownerAi->direction, randRotate(randomEngine)), 
                                     gunComp->bulletDamage, 
                                     randSpeed(randomEngine));
                    }
                }
            }

            break;
    }
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

void GameLogic::VOnUpdate(int deltaMs) {
    for (auto it = m_actors.begin(); it != m_actors.end(); ++it) {
        it->second->Update(deltaMs);
    }
}

void GameLogic::VOnRender(SpriteBatch& _spriteBatch) {
    for (auto it = m_actors.begin(); it != m_actors.end(); ++it) {
        auto render = it->second->GetComponent<RenderComponent>(RenderComponent::COMPONENT_ID).lock();
        if (render)
            render->draw(_spriteBatch);
    }
}

WeakActorPtr GameLogic::CreatePlayer(float speed, glm::vec2 pos, std::weak_ptr<Camera2D> camera, std::vector<Bullet>* bullets) {
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
        pPlayerAI->camera = camera;

        pPlayer->AddComponent(pPlayerAI);
        pPlayerAI->SetOwner(pPlayer);
    } else {
        return StrongActorPtr();
    }

    std::shared_ptr<InventoryComponent> pInventory((InventoryComponent *) CreateInventory());
    if (pInventory) {
        const float BULLET_SPEED = 20.0f;
        pInventory->guns.push_back(CreateGun(100, 1, 5.0f * RADIANS, 80, BULLET_SPEED).lock());
        pInventory->guns.push_back(CreateGun(200, 12, 20.0f * RADIANS, 45, BULLET_SPEED).lock());
        pInventory->guns.push_back(CreateGun(20, 1, 10.0f * RADIANS, 60, BULLET_SPEED).lock());

        pPlayer->AddComponent(pInventory);
        pInventory->SetOwner(pPlayer);
    } else {
        return WeakActorPtr();
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

WeakActorPtr GameLogic::CreateBullet(ActorId owner, glm::vec2 position, glm::vec2 direction, float damage, float speed) {
    StrongActorPtr pBullet(m_actorFactory.CreateActor());

    std::shared_ptr<PositionComponent> pPosition((PositionComponent *) CreatePosition());
    if (pPosition) {
        pPosition->x = position.x;
        pPosition->y = position.y;
        pPosition->z = 0.0f;

        pBullet->AddComponent(pPosition);
        pPosition->SetOwner(pBullet);
    } else {
        return WeakActorPtr();
    }

    std::shared_ptr<BulletComponent> pBulletComp((BulletComponent *) CreateBulletComp());
    if (pBulletComp) {
        pBulletComp->ownerId = owner;
        pBulletComp->damage = damage;
        pBulletComp->speed = speed;
        pBulletComp->direction = direction;

        pBullet->AddComponent(pBulletComp);
        pBulletComp->SetOwner(pBullet);
    } else {
        return WeakActorPtr();
    }

    std::shared_ptr<RenderComponent> pRender((RenderComponent *) CreateRender());
    if (pRender) {
        pRender->color.r = 75;
        pRender->color.g = 75;
        pRender->color.b = 75;
        pRender->color.a = 255;

        pBullet->AddComponent(pRender);
        pRender->SetOwner(pBullet);
    } else {
        return StrongActorPtr();
    }

    pBullet->PostInit();

    m_actors.insert(std::make_pair(pBullet->GetId(), pBullet));

    return WeakActorPtr(pBullet);
}

WeakActorPtr GameLogic::CreateGun(int fireRate, int bulletsPerShot, float spread, float bulletSpeed, int bulletDamage) {
    StrongActorPtr pGun(m_actorFactory.CreateActor());

    std::shared_ptr<GunComponent> pGunComp((GunComponent *) CreateGunComp());
    if (pGunComp) {
        pGunComp->fireRate = fireRate;
        pGunComp->bulletsPerShot = bulletsPerShot;
        pGunComp->spread = spread;
        pGunComp->bulletSpeed = bulletSpeed;
        pGunComp->bulletDamage = bulletDamage;

        pGun->AddComponent(pGunComp);
        pGunComp->SetOwner(pGun);
    } else {
        return WeakActorPtr();
    }

    pGun->PostInit();

    m_actors.insert(std::make_pair(pGun->GetId(), pGun));

    return pGun;
}
