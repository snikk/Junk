#pragma once

#include "Human.h"
#include "../io/InputManager.h"
#include "../drawing/Camera.h"
#include "Bullet.h"

class Gun;

class Player : public Human
{
public:
    Player();
    ~Player();

    void init(float speed, glm::vec2 pos, Camera2D* camera, std::vector<Bullet>* bullets);

    void addGun(Gun* gun);

    void update(const std::vector<std::string>& levelData,
                std::vector<Human*>& humans,
                std::vector<Zombie*>& zombies,
                float deltaTime) override;
private:
    std::vector<Gun*> _guns;
    int _currentGunIndex;

    Camera2D* _camera;
    std::vector<Bullet>* _bullets;

};

