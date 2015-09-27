#pragma once

#include "Agent.h"

enum class ZombieState {
    BORN, 
    ALIVE, 
    DEAD
};

class Zombie : public Agent
{
public:
    Zombie();
    ~Zombie();

    void init(float speed, glm::vec2 pos, float damage);

    virtual void update(const std::vector<std::string>& levelData,
                        std::vector<Human*>& humans,
                        std::vector<Zombie*>& zombies,
                        float deltaTime) override;

    float getDamage() const { return _damage; }

    ZombieState getState() const { return _state; }
    void setState(ZombieState newState) { _state = newState; }
    void setHealth(float newHealth) { _health = newHealth; }
private:

    Human* getNearestHuman(std::vector<Human*>& humans);

    float _damage;
    ZombieState _state;
};

