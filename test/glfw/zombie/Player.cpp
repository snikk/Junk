#include "Player.h"

#include "Gun.h"

Player::Player() :
    _currentGunIndex(-1) {
    // Empty
}

Player::~Player() {
    // Empty
}

void Player::init(float speed, glm::vec2 pos, Camera2D* camera, std::vector<Bullet>* bullets) {
    _speed = speed;
    _position = pos;
    _bullets = bullets;
    _camera = camera;
    _color.r = 0;
    _color.g = 0;
    _color.b = 185;
    _color.a = 255;
    _health = 150;
}

void Player::addGun(Gun* gun) {
    // Add the gun to his inventory
    _guns.push_back(gun);

    // If no gun equipped, equip gun.
    if (_currentGunIndex == -1) {
        _currentGunIndex = 0;
    }
}

void Player::update(const std::vector<std::string>& levelData,
                    std::vector<Human*>& humans,
                    std::vector<Zombie*>& zombies,
                    float deltaTime) {

    if (InputManager::instance().isKeyDown(GLFW_KEY_W)) {
        _position.y += _speed * deltaTime;
    } else if (InputManager::instance().isKeyDown(GLFW_KEY_S)) {
        _position.y -= _speed * deltaTime;
    }
    if (InputManager::instance().isKeyDown(GLFW_KEY_A)) {
        _position.x -= _speed * deltaTime;
    } else if (InputManager::instance().isKeyDown(GLFW_KEY_D)) {
        _position.x += _speed * deltaTime;
    }

    if (InputManager::instance().isKeyDown(GLFW_KEY_1) && _guns.size() > 0) {
        _currentGunIndex = 0;
    } else if (InputManager::instance().isKeyDown(GLFW_KEY_2) && _guns.size() > 1) {
        _currentGunIndex = 1;
    } else if (InputManager::instance().isKeyDown(GLFW_KEY_3) && _guns.size() > 2) {
        _currentGunIndex = 2;
    }

    if (_currentGunIndex != -1) {

        glm::vec2 mouseCoords = InputManager::instance().getMouseCoords();
        mouseCoords = _camera->convertScreenToWorld(mouseCoords);

        glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);

        glm::vec2 direction = glm::normalize(mouseCoords - centerPosition);

        _guns[_currentGunIndex]->update(InputManager::instance().isKeyDown(GLFW_MOUSE_BUTTON_LEFT),
                                        centerPosition,
                                        direction,
                                        *_bullets,
                                        deltaTime);
                                        

    }

    collideWithLevel(levelData);
}
