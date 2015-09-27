#include "MainGame.h"
#include <random>
#include <ctime>
#include <algorithm>
#include "io/InputManager.h"
#include "io/Error.h"
#include "common.h"

#include <iostream>

#include "zombie/Gun.h"
#include "zombie/Zombie.h"
#include "util/Util.h"

const float RADIANS = M_PI / 180.0;

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.3f;
const float PLAYER_SPEED = 5.0f;

MainGame::MainGame() :                                                                                
    _screenWidth(1280),
    _screenHeight(960),
    _gameState(GameState::PLAY),
    _fps(0),
    _player(nullptr),
    _numHumansKilled(0),                                                                               
    _numZombiesKilled(0) {}

MainGame::~MainGame() {
    // Don't forget to delete the levels!                                                              
    for (int i = 0; i < _levels.size(); i++) {                                                         
        delete _levels[i];                                                                             
    }                                                                                                  
    // Don't forget to delete the humans and zombies!                                                  
    for (int i = 0; i < _humans.size(); i++) {                                                         
        delete _humans[i];                                                                             
    }                                                                                                  
    for (int i = 0; i < _zombies.size(); i++) {                                                        
        delete _zombies[i];                                                                            
    } 
}

void MainGame::run() {
    initSystems();
    initLevel();
    gameLoop();
}

void MainGame::initSystems() {
    _window.init("Hey ho!", _screenWidth, _screenHeight, NULL, NULL);
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    initShaders();
    _agentSpriteBatch.init(&_textureProgram);
    _camera.init(_screenWidth, _screenHeight);

    glfwSetCursorPosCallback(_window.window, InputManager::cursorFunction);
    glfwSetMouseButtonCallback(_window.window, InputManager::mouseButtonFunction);
    glfwSetKeyCallback(_window.window, InputManager::keyFunction);
}

void MainGame::initLevel() {
    _levels.push_back(new Level("level/level1.txt", &_textureProgram));
    _currentLevel = 0;

    _player = new Player();
    _player->init(PLAYER_SPEED, _levels[_currentLevel]->getStartPlayerPos(), &_camera, &_bullets);

    _humans.push_back(_player);

    std::mt19937 randomEngine;
    randomEngine.seed(time(nullptr));

    std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
    std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

    // Add all the random humans
    for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++) {
        _humans.push_back(new Human);
        glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
        _humans.back()->init(HUMAN_SPEED, pos);
    }

    // Add the zombies
    const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getZombieStartPositions();
    for (int i = 0; i < zombiePositions.size(); i++) {
        _zombies.push_back(new Zombie);
        _zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i], 0.15);
    }

    // Set up the players guns
    const float BULLET_SPEED = 20.0f;
    _player->addGun(new Gun("Magnum", 10, 1, 5.0f * RADIANS, 30, BULLET_SPEED));
    _player->addGun(new Gun("Shotgun", 30, 12, 20.0f * RADIANS, 4, BULLET_SPEED));
    _player->addGun(new Gun("MP5", 2, 1, 10.0f * RADIANS, 20, BULLET_SPEED));
}

void MainGame::initShaders() {
    _textureProgram.init("shader/textureShading.vert", "shader/textureShading.frag");
    _textureProgram.addAttribute("vertexPosition");
    _textureProgram.addAttribute("vertexColor");
    _textureProgram.addAttribute("vertexUV");
}

void MainGame::gameLoop() {
    // Some helpful constants.
    const float DESIRED_FPS = 60.0f; // FPS the game is designed to run at
    const int MAX_PHYSICS_STEPS = 6; // Max number of physics steps per frame
    const long MS_PER_SECOND = 1000; // Number of milliseconds in a second
    const long US_PER_SECOND = 1000000; // Number of microseconds in a second
    const long NS_PER_SECOND = 1000000000; // Number of nanoseconds in a second
    const long DESIRED_FRAMETIME = (US_PER_SECOND / DESIRED_FPS) / US_PER_SECOND; // The desired frame time per frame
    const float MAX_DELTA_TIME = 1.0f; // Maximum size of deltaTime

    // Zoom out the camera by 4x
    const float CAMERA_SCALE = 1.0f / 4.0f;
    _camera.setScale(CAMERA_SCALE);

    // Start our previousTicks variable
    float previousTime = glfwGetTime();
    float newTime;

    // Main loop
    while (_gameState == GameState::PLAY) {
        // Calculate the frameTime in milliseconds
        newTime = glfwGetTime();
        float frameTime = newTime - previousTime;
        // Get the total delta time
        float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

        previousTime = newTime; // Store newTicks in previousTicks so we can use it next frame

        checkVictory();

        InputManager::instance().update();

        processInput();
        
        int i = 0; // This counter makes sure we don't spiral to death!
        // Loop while we still have steps to process.
        while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
            // The deltaTime should be the the smaller of the totalDeltaTime and MAX_DELTA_TIME
            float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
            // Update all physics here and pass in deltaTime
            updateAgents(deltaTime);
            updateBullets(deltaTime);
            // Since we just took a step that is length deltaTime, subtract from totalDeltaTime
            totalDeltaTime -= deltaTime;
            // Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
            i++;
        }

        // Make sure the camera is bound to the player position
        _camera.setPosition(_player->getPosition());
        _camera.update();

        drawGame();

        // End the frame, limit the FPS, and get the current FPS.
        float renderTime = glfwGetTime() - newTime;
        long totalSleepTime = (US_PER_SECOND / DESIRED_FPS) - (US_PER_SECOND * renderTime);
        if (totalSleepTime > 0) {
            usleep(totalSleepTime);
        }
    }
}

void MainGame::updateAgents(float deltaTime) {
    // Update all humans
    for (int i = 0; i < _humans.size(); i++) {
        _humans[i]->update(_levels[_currentLevel]->getLevelData(),
                           _humans,
                           _zombies,
                           deltaTime);
    }

    // Update all zombies
    for (int i = 0; i < _zombies.size(); i++) {
        _zombies[i]->update(_levels[_currentLevel]->getLevelData(),
                           _humans,
                           _zombies,
                           deltaTime);
    }

    // Update Zombie collisions
    for (int i = 0; i < _zombies.size(); i++) {
        // Collide with other zombies
        for (int j = i + 1; j < _zombies.size(); j++) {
            _zombies[i]->collideWithAgent(_zombies[j]);
        }
        // Collide with humans
        for (int j = 1; j < _humans.size(); j++) {
            if (_zombies[i]->collideWithAgent(_humans[j])) {
                if (_humans[j]->applyDamage(deltaTime * _zombies[i]->getDamage())) {
                    // Add the new zombie
                    _zombies.push_back(new Zombie);
                    _zombies.back()->init(ZOMBIE_SPEED, _humans[j]->getPosition(), 0.15);
                    _zombies.back()->setState(ZombieState::BORN);
                    _zombies.back()->setHealth(0.0f);

                    // Delete the human
                    delete _humans[j];
                    _humans[j] = _humans.back();
                    _humans.pop_back();
                }
            }
        }

        // Collide with player
        if (_zombies[i]->collideWithAgent(_player)) {
            if (_player->applyDamage(deltaTime * _zombies[i]->getDamage())) {
                fatalError("YOU LOSE");
            }
        }
    }

    // Update Human collisions
    for (int i = 0; i < _humans.size(); i++) {
        // Collide with other humans
        for (int j = i + 1; j < _humans.size(); j++) {
            _humans[i]->collideWithAgent(_humans[j]);
        }
    }

    // Dont forget to update zombies
}

void MainGame::updateBullets(float deltaTime) {
    // Update and collide with world
    for (int i = 0; i < _bullets.size(); ) {
        // If update returns true, the bullet collided with a wall
        if (_bullets[i].update(_levels[_currentLevel]->getLevelData(), deltaTime)) {
            _bullets[i] = _bullets.back();
            _bullets.pop_back();
        } else {
            i++;
        }
    }

    bool wasBulletRemoved;

    // Collide with humans and zombies
    for (int i = 0; i < _bullets.size(); i++) {
        wasBulletRemoved = false;
        // Loop through zombies
        for (int j = 0; j < _zombies.size(); ) {
            // Check collision
            if (_bullets[i].collideWithAgent(_zombies[j])) {
                // Damage zombie, and kill it if its out of health
                if (_zombies[j]->applyDamage(_bullets[i].getDamage())) {
                    // If the zombie died, remove him
                    delete _zombies[j];
                    _zombies[j] = _zombies.back();
                    _zombies.pop_back();
                    _numZombiesKilled++;
                } else {
                    j++;
                }

                // Remove the bullet
                _bullets[i] = _bullets.back();
                _bullets.pop_back();
                wasBulletRemoved = true;
                i--; // Make sure we don't skip a bullet
                // Since the bullet died, no need to loop through any more zombies
                break;
            } else {
                j++;
            }
        }
        // Loop through humans
        if (wasBulletRemoved == false) {
            for (int j = 1; j < _humans.size(); ) {
                // Check collision
                if (_bullets[i].collideWithAgent(_humans[j])) {
                    // Damage human, and kill it if its out of health
                    if (_humans[j]->applyDamage(_bullets[i].getDamage())) {
                        // If the human died, remove him
                        delete _humans[j];
                        _humans[j] = _humans.back();
                        _humans.pop_back();
                    } else {
                        j++;
                    }

                    // Remove the bullet
                    _bullets[i] = _bullets.back();
                    _bullets.pop_back();
                    _numHumansKilled++;
                    i--; // Make sure we don't skip a bullet
                    // Since the bullet died, no need to loop through any more zombies
                    break;
                } else {
                    j++;
                }
            }
        }
    }
}

void MainGame::checkVictory() {
    // TODO: Support for multiple levels!
    // _currentLevel++; initLevel(...);

    // If all zombies are dead we win!
    if (_zombies.empty()) {
        // Print victory message
        std::printf("*** You win! ***\n You killed %d humans and %d zombies. There are %d/%d civilians remaining",
                    _numHumansKilled, _numZombiesKilled, _humans.size() - 1, _levels[_currentLevel]->getNumHumans());

        // Easy way to end the game :P
        fatalError("");
    }
}

void MainGame::processInput() {
    if (glfwWindowShouldClose(_window.window))
        _gameState = GameState::EXIT;
    glfwPollEvents();
}

void MainGame::drawGame() {
    // Set the base depth to 1.0
    glClearDepth(1.0);
    CHK_ERR("glClearDepth");
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CHK_ERR("glClear");

    CHK_ERR("Before use");
    _textureProgram.use();

    // Draw code goes here
    glActiveTexture(GL_TEXTURE0);
    CHK_ERR("glActiveTexture");

    // Make sure the shader uses texture 0
    GLint textureUniform = _textureProgram.getUniform("mySampler");
    CHK_ERR("texture");
    glUniform1i(textureUniform, 0);
    CHK_ERR("setUniform");

    // Grab the camera matrix
    glm::mat4 projectionMatrix = _camera.getCameraMatrix();
    GLint pUniform = _textureProgram.getUniform("P");
    CHK_ERR("getUniform");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
    CHK_ERR("getUniform");

    // Draw the level
    _levels[_currentLevel]->draw();
    CHK_ERR("draw");

    // Begin drawing agents
    _agentSpriteBatch.begin();

    const glm::vec2 agentDims(AGENT_RADIUS * 2.0f);

    // Draw the humans
    for (int i = 0; i < _humans.size(); i++) {
        if (_camera.isBoxInView(_humans[i]->getPosition(), agentDims)) {
            _humans[i]->draw(_agentSpriteBatch);
        }
    }

    // Draw the zombies
    for (int i = 0; i < _zombies.size(); i++) {
        if (_camera.isBoxInView(_zombies[i]->getPosition(), agentDims)) {
            _zombies[i]->draw(_agentSpriteBatch);
        }
    }

    // Draw the bullets
    for (int i = 0; i < _bullets.size(); i++) {
        _bullets[i].draw(_agentSpriteBatch);
    }

    // End spritebatch creation
    _agentSpriteBatch.end();

    // Render to the screen
    _agentSpriteBatch.renderBatch();
    CHK_ERR("render batches");

    // Unbind the program
    _textureProgram.unuse();
    CHK_ERR("unuse");

    // Swap our buffer and draw everything to the screen!
    _window.swapBuffers();
}
