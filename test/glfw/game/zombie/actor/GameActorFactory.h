#ifndef __GAME_ACTOR_FACTORY_H__
#define __GAME_ACTOR_FACTORY_H__

#include <actor/ActorFactory.h>
#include <drawing/Camera.h>
#include "../Bullet.h"

class GameActorFactory : public ActorFactory {
public:
    StrongActorPtr CreatePlayer(float speed, glm::vec2 pos, Camera2D* camera, std::vector<Bullet>* bullets);
    StrongActorPtr CreateHuman();
    StrongActorPtr CreateZombie();
};

#endif
