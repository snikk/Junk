#ifndef __MAIN_GAME_H__
#define __MAIN_GAME_H__

#include <io/Window.h>
#include <drawing/Camera.h>
#include <shader/Shader.h>

#include "zombie/Player.h"
#include "zombie/Level.h"
#include "zombie/Bullet.h"
#include "zombie/GameLogic.h"

#include <actor/Actor.h>
#include <actor/ActorComponent.h>
#include <debug/DebugView.h>

enum class GameState {
    PLAY, 
    EXIT
};

class MainGame {
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initSystems();
    void initLevel();
    void initShaders();
    void gameLoop();
    void updateAgents(float deltaTime);
    void updateBullets(float deltaTime);
    void checkVictory();
    void processInput();
    void drawGame();

    /// Member Variables                                                                    
    Window _window; ///< The game window                                           

    Shader _textureProgram; ///< The shader program                           

    std::shared_ptr<Camera2D> _camera; ///< Main Camera                                             
    SpriteBatch _agentSpriteBatch; ///< Draws all agents                           
    DebugView _debugView;
    
    std::vector<Level*> _levels; ///< vector of all levels                                  

    int _screenWidth, _screenHeight;                                                        

    float _fps;                                                                             

    int _currentLevel;                                                                      

    StrongActorPtr _player;                                                                        
    std::list<StrongActorPtr> _actors; ///< Vector of all actors

    int _numHumansKilled; ///< Humans killed by player                                      
    int _numZombiesKilled; ///< Zombies killed by player                                    

    GameState _gameState;

    GameLogic _gameLogic;
};

#endif
