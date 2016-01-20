#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include <actor/Actor.h>
#include <actor/ActorFactory.h>
#include <common.h>
#include <drawing/Camera.h>
#include "Bullet.h"
#include "events/Events.h"

typedef std::map<ActorId, StrongActorPtr> ActorMap;

class GameLogic {
    ActorMap m_actors;

    ActorFactory m_actorFactory;

public:
    GameLogic();
    ~GameLogic();

    virtual WeakActorPtr VGetActor(const ActorId actorId);
    virtual void VDestroyActor(const ActorId actorId);

    virtual void Init();
    virtual void Destroy();

    virtual void eventHandler(IEventDataPtr pEventData);

    WeakActorPtr CreatePlayer(float speed, glm::vec2 pos, std::weak_ptr<Camera2D> camera, std::vector<Bullet>* bullets);
    WeakActorPtr CreateHuman();
    WeakActorPtr CreateZombie();

    WeakActorPtr CreateBullet(ActorId owner, glm::vec2 position, glm::vec2 direction, float damage, float speed);
    WeakActorPtr CreateGun(int fireRate, int bulletsPerShot, float spread, float bulletSpeed, int bulletDamage);

    virtual void VOnUpdate(int deltaMs);
    virtual void VOnRender(SpriteBatch& _spriteBatch);
};

#endif
