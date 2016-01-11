#include "MainGame.h"
#include <random>
#include <ctime>
#include <algorithm>
#include <io/InputManager.h>
#include <io/Error.h>
#include <common.h>
#include <network/Network.h>
#include <events/EngineEvents.h>
#include <events/EventManager.h>

//#include <actor/ActorFactory.h>

#include <iostream>

#include "zombie/actor/components/Render.h"
#include "zombie/actor/components/Health.h"

#include "zombie/Gun.h"
#include "zombie/Zombie.h"
#include <util/Util.h>

#ifdef _WIN32
#include <chrono>
#include <thread>
#define M_PI 3.14159265359
#endif

#include <actor/components/PositionComponent.h>

#include "zombie/events/Events.h"

const float RADIANS = M_PI / 180.0;

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.3f;
const float PLAYER_SPEED = 5.0f;

NetworkEventForwarder* g_pForwarder;

void destroyActorDelegate(IEventDataPtr pEventData) {
    std::shared_ptr<EvtData_Destroy_Actor> pCastEventData = std::static_pointer_cast<EvtData_Destroy_Actor>(pEventData);

    printf("Hey here we are. | pCastEventData->GetId() = %u\n", pCastEventData->GetId());
}

void addNewRemoteSocket(IEventDataPtr pEventData) {
    std::shared_ptr<EvtData_Remote_Client> pCastEventData = std::static_pointer_cast<EvtData_Remote_Client>(pEventData);

    printf("Hey.  I got a new Client!\n");
    const int sockID = pCastEventData->GetSocketId();
    const int ipAddress = pCastEventData->GetIpAddress();

    std::ostrstream out;

    out << static_cast<int>(RemoteEventSocket::NetMsg_PlayerLoginOk) << " ";
    out << sockID << " ";
    out << 20 << " ";
    out << 123 << " ";
    out << "\r\n";

    std::shared_ptr<BinaryPacket> gvidMsg(GCC_NEW BinaryPacket(out.rdbuf()->str(), (u_long)out.pcount()));
    BaseSocketManager::Get()->Send(sockID, gvidMsg);
}

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
    _actors.clear();
}

void MainGame::run() {
    //StrongActorPtr actor = CreateActor("actor/test.json");
    initSystems();
    initLevel();
    gameLoop();
}

void MainGame::initSystems() {
    GCC_NEW EventManager("Main EventManager", true);

    _window.init("Hey ho!", _screenWidth, _screenHeight, NULL, NULL);
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    initShaders();
    _agentSpriteBatch.init(&_textureProgram);
    _camera.init(_screenWidth, _screenHeight);

    glfwSetCursorPosCallback(_window.window, InputManager::cursorFunction);
    glfwSetMouseButtonCallback(_window.window, InputManager::mouseButtonFunction);
    glfwSetKeyCallback(_window.window, InputManager::keyFunction);
}

void displayPosition(StrongActorPtr pActor) {
    std::shared_ptr<PositionComponent> pPosition = MakeStrongPtr(pActor->GetComponent<PositionComponent>(PositionComponent::COMPONENT_ID));
    if (pPosition) {
        printf("Hey got the position!? | x = %f | y = %f | z = %f\n", pPosition->x, pPosition->y, pPosition->z);
    } else {
        printf("An error!!!! well I never.\n");
    }
}

void MainGame::initLevel() {
    long ticks = getTicks();
    printf("getTicks() = %lu\n", ticks);

    printf("EvtData_Destroy_Actor::sk_EventType = %lu\n", EvtData_Destroy_Actor::sk_EventType);

    IEventManager::Get()->VAddListener(&destroyActorDelegate, EvtData_Destroy_Actor::sk_EventType);

    _debugView.init();
    CHK_ERR("Debug View Init");
    /*
    IEventManager::Get()->VAddListener(&destroyActorDelegate, EvtData_Destroy_Actor::sk_EventType);

    std::shared_ptr<EvtData_Destroy_Actor> pDestroyActorData1(GCC_NEW EvtData_Destroy_Actor(1));
    std::shared_ptr<EvtData_Destroy_Actor> pDestroyActorData2(GCC_NEW EvtData_Destroy_Actor(12));
    std::shared_ptr<EvtData_Destroy_Actor> pDestroyActorData3(GCC_NEW EvtData_Destroy_Actor(123));
    std::shared_ptr<EvtData_Destroy_Actor> pDestroyActorData4(GCC_NEW EvtData_Destroy_Actor(1234));
    std::shared_ptr<EvtData_Destroy_Actor> pDestroyActorData5(GCC_NEW EvtData_Destroy_Actor(12345));
    std::shared_ptr<EvtData_Destroy_Actor> pDestroyActorData6(GCC_NEW EvtData_Destroy_Actor(123456));

    IEventManager::Get()->VQueueEvent(pDestroyActorData1);
    IEventManager::Get()->VQueueEvent(pDestroyActorData2);
    IEventManager::Get()->VQueueEvent(pDestroyActorData3);
    IEventManager::Get()->VQueueEvent(pDestroyActorData4);
    IEventManager::Get()->VQueueEvent(pDestroyActorData5);
    IEventManager::Get()->VQueueEvent(pDestroyActorData6);

    printf("Here we are before the update call\n");
    IEventManager::Get()->VTickVUpdate();
    printf("After the update call?\n");
    */

    /*
    GameActorFactory factory;
    StrongActorPtr actor = factory.CreateActor("actor/test.json");

    
    std::weak_ptr<PositionComponent> pWeakPickup = actor->GetComponent<PositionComponent>(PositionComponent::COMPONENT_ID);
    std::shared_ptr<PositionComponent> pPosition = MakeStrongPtr(pWeakPickup);
    if (pPosition) {
        printf("Hey got the position!? | x = %f | y = %f | z = %f\n", pPosition->x, pPosition->y, pPosition->z);
    } else {
        printf("An error!!!! well I never.\n");
    }

    actor->Destroy();
    */

    /*
    StrongActorPtr player = factory.CreatePlayer();
    printf("Created the player?  How about that.  If *I* was the player perhaps my ID would be = %u\n", player->GetId());
    displayPosition(player);
    StrongActorPtr human = factory.CreateHuman();
    printf("Created the Human?  How about that.  If *HE* was running from zombies perhaps he would have an ID = %u\n", human->GetId());
    displayPosition(human);
    StrongActorPtr zombie = factory.CreateZombie();
    printf("Created the Zombie?  How about that.  Gross = %u\n", zombie->GetId());
    displayPosition(zombie);

    player->Destroy();
    human->Destroy();
    zombie->Destroy();
    */

    _levels.push_back(new Level("level/level1.txt", &_textureProgram));
    _currentLevel = 0;

    /*
    _player = new Player();
    _player->init(PLAYER_SPEED, _levels[_currentLevel]->getStartPlayerPos(), &_camera);
    */

    _player = _gameLogic.CreatePlayer(PLAYER_SPEED, _levels[_currentLevel]->getStartPlayerPos(), &_camera, nullptr).lock();

    /*
    std::mt19937 randomEngine;
    randomEngine.seed(time(nullptr));

    std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
    std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

    // Add all the random humans
    for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++) {
        _actors.push_back(new Human);
        glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
        _actors.back()->init(HUMAN_SPEED, pos);
    }

    // Add the zombies
    const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getZombieStartPositions();
    for (int i = 0; i < zombiePositions.size(); i++) {
        _actors.push_back(new Zombie);
        _actors.back()->init(ZOMBIE_SPEED, zombiePositions[i], 0.15);
    }

    // Set up the players guns
    const float BULLET_SPEED = 20.0f;
    _player->addGun(new Gun("Magnum", 10, 1, 5.0f * RADIANS, 30, BULLET_SPEED));
    _player->addGun(new Gun("Shotgun", 30, 12, 20.0f * RADIANS, 4, BULLET_SPEED));
    _player->addGun(new Gun("MP5", 2, 1, 10.0f * RADIANS, 20, BULLET_SPEED));
    */
}

void MainGame::initShaders() {
    _textureProgram.init("shader/textureShading.vert", "shader/textureShading.frag");
    _textureProgram.addAttribute("vertexPosition");
    _textureProgram.addAttribute("vertexColor");
    _textureProgram.addAttribute("vertexUV");
}

void MainGame::gameLoop() {
    REGISTER_EVENT(EvtData_Destroy_Actor);

    printf("game loop begins!\n");
    BaseSocketManager* baseSocketManager = GCC_NEW BaseSocketManager;
    GameServerListenSocket* listenSocket = GCC_NEW GameServerListenSocket(7788);
    baseSocketManager->AddSocket(listenSocket);

    IEventManager::Get()->VAddListener(&addNewRemoteSocket, EvtData_Remote_Client::sk_EventType);

    ClientSocketManager* pClient = GCC_NEW ClientSocketManager("127.0.0.1", 7788);

    g_pForwarder = GCC_NEW NetworkEventForwarder(0);
    IEventManager* pEvent = IEventManager::Get();

    pEvent->VAddListener(fastdelegate::MakeDelegate(g_pForwarder, &NetworkEventForwarder::ForwardEvent), EvtData_Destroy_Actor::sk_EventType);

    int id = 0;

    if (!pClient->Connect()) {
        GCC_ERROR("Couldn't attach to game server.\n");
    }

    glm::mat4 projection = glm::mat4();
    float xScale = (float) _window.height / (float) _window.width;
    projection = glm::scale(projection, glm::vec3(xScale, -1.0f, 1.0f));

    while (_gameState == GameState::PLAY) {
        // Set the base depth to 1.0
        glClearDepth(1.0);
        CHK_ERR("glClearDepth");
        // Clear the color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        CHK_ERR("glClear");

        //printf("-------------Start frame--------------\n");
        baseSocketManager->DoSelect(0);
        pClient->DoSelect(0);

        /*
        if (id < 10 && g_pForwarder != NULL) {
            std::shared_ptr<EvtData_Destroy_Actor> pDestroyActorData(GCC_NEW EvtData_Destroy_Actor(id++));

            IEventManager::Get()->VQueueEvent(pDestroyActorData);
        }
        */

        _debugView.clear();
        _debugView.setColor(0xFF00FF00);
        _debugView.move(0.1 * _window.width, 0.1 * _window.height);
        _debugView.lineTo(0.2 * _window.width, 0.25 * _window.height);
        _debugView.lineTo(0.2 * _window.width, -0.25 * _window.height);
        _debugView.lineTo(-0.2 * _window.width, 0.25 * _window.height);
        _debugView.lineTo(-0.2 * _window.width, -0.25 * _window.height);

        _debugView.move(0.6 * _window.width, 0.7 * _window.height, 0xFFFFFFFF);
        _debugView.lineTo(-0.6 * _window.width, 0.7 * _window.height, 0xFFFF0000);
        _debugView.curveTo(-0.7 * _window.width, 0.7 * _window.height, -0.7 * _window.width, 0.6 * _window.height);
        _debugView.lineTo(-0.7 * _window.width, -0.6 * _window.height);
        _debugView.curveTo(-0.7 * _window.width, -0.7 * _window.height, -0.6 * _window.width, -0.7 * _window.height);
        _debugView.lineTo(0.6 * _window.width, -0.7 * _window.height);
        _debugView.curveTo(0.7 * _window.width, -0.7 * _window.height, 0.7 * _window.width, -0.6 * _window.height);
        _debugView.lineTo(0.7 * _window.width, 0.6 * _window.height);
        _debugView.curveTo(0.7 * _window.width, 0.7 * _window.height, 0.6 * _window.width, 0.7 * _window.height);
        
        //_camera.setScale(1.0f / 4.0f);
        _camera.setScale(1.0f / 4.0f);
        //_camera.setPosition(InputManager::instance().getMouseCoords());
        //_camera.setPosition(glm::vec2(_window.width / 2.0f, _window.height / 2.0f));
        //_camera.update();

        glm::vec2 screen = (InputManager::instance().getMouseCoords() / glm::vec2(_window.width, _window.height)) * 2.0f - 1.0f;
        screen.y *= -1;

        glm::vec4 mouse = _camera.getInverseMatrix() * glm::vec4(screen, 0.0f, 1.0f);

        _debugView.move(1.0 * _window.width, 1.0 * _window.height, 0xFF0000FF);
        _debugView.curveTo(mouse.x, mouse.y, 1.0 * _window.width, -1.0 * _window.height);
        _debugView.curveTo(mouse.x, mouse.y, -1.0 * _window.width, -1.0 * _window.height);
        _debugView.curveTo(mouse.x, mouse.y, -1.0 * _window.width, 1.0 * _window.height);
        _debugView.curveTo(mouse.x, mouse.y, 1.0 * _window.width, 1.0 * _window.height);

        _debugView.move(0.0f, 0.0f, 0xFF00FFFF);
        _debugView.lineTo(_window.width, _window.height);
        _debugView.curveTo(0.0f, _window.height, 0.0f, 0.0f);
        _debugView.curveTo(_window.width, 0.0f, _window.width, _window.height);

        _debugView.move(0.0f, 0.0f, 0xFF000000);
        _debugView.lineTo(mouse.x, mouse.y);

        _debugView.draw(_camera.getCameraMatrix());

        _player->Update(1000.0f / 60.0f);
        auto pPlayerPos = _player->GetComponent<PositionComponent>(PositionComponent::COMPONENT_ID).lock();
        if (pPlayerPos)
            _camera.setPosition(glm::vec2(pPlayerPos->x, pPlayerPos->y));
        _camera.update();

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

        auto pPlayerRender = _player->GetComponent<RenderComponent>(RenderComponent::COMPONENT_ID).lock();
        if (pPlayerRender) {
            pPlayerRender->draw(_agentSpriteBatch);
        }

        _agentSpriteBatch.end();
        CHK_ERR("agentSpriteBatchEnd");
        
        // Render to the screen
        _agentSpriteBatch.renderBatch();
        CHK_ERR("render batches");

        // Unbind the program
        _textureProgram.unuse();
        CHK_ERR("unuse");

        // Swap our buffer and draw everything to the screen!
        _window.swapBuffers();

        IEventManager::Get()->VTickVUpdate();

        processInput();
        InputManager::instance().update();

#ifdef _WIN32
    	std::this_thread::sleep_for(std::chrono::microseconds(16000));
#else
		usleep(16000);
#endif
    }

    _player->Destroy();
    delete baseSocketManager;

    /*
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
#ifdef _WIN32
			std::this_thread::sleep_for(std::chrono::microseconds(totalSleepTime));
#else
			usleep(totalSleepTime);
#endif
        }
    }
    */
}

void MainGame::updateAgents(float deltaTime) {
    /*
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
    */
}

void MainGame::updateBullets(float deltaTime) {
    /*
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
    */
}

void MainGame::checkVictory() {
    /*
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
    */
}

void MainGame::processInput() {
    if (glfwWindowShouldClose(_window.window))
        _gameState = GameState::EXIT;
    glfwPollEvents();
}

void MainGame::drawGame() {
    /*
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
    */
}

