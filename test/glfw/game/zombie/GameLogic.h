#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include <actor/Actor.h>
#include <actor/ActorFactory.h>
#include <common.h>
#include <drawing/Camera.h>
#include "Bullet.h"

typedef std::map<ActorId, StrongActorPtr> ActorMap;

class GameLogic {
    ActorMap m_actors;

    ActorFactory m_actorFactory;

public:
    GameLogic();
    ~GameLogic();

    virtual WeakActorPtr VGetActor(const ActorId actorId);
    virtual void VDestroyActor(const ActorId actorId);

    WeakActorPtr CreatePlayer(float speed, glm::vec2 pos, Camera2D* camera, std::vector<Bullet>* bullets);
    WeakActorPtr CreateHuman();
    WeakActorPtr CreateZombie();
};

#endif
