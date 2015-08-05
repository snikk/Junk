#ifndef __MAIN_GAME_H__
#define __MAIN_GAME_H__

#include "io/Window.h"
#include "drawing/Camera.h"
#include "shader/Shader.h"

#include "zombie/Player.h"
#include "zombie/Level.h"
#include "zombie/Bullet.h"

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

    Camera2D _camera; ///< Main Camera                                             

    SpriteBatch _agentSpriteBatch; ///< Draws all agents                           
    
    std::vector<Level*> _levels; ///< vector of all levels                                  

    int _screenWidth, _screenHeight;                                                        

    float _fps;                                                                             

    int _currentLevel;                                                                      

    Player* _player;                                                                        
    std::vector<Human*> _humans; ///< Vector of all humans                                  
    std::vector<Zombie*> _zombies; ///< Vector of all zombies                               
    std::vector<Bullet> _bullets;                                                           

    int _numHumansKilled; ///< Humans killed by player                                      
    int _numZombiesKilled; ///< Zombies killed by player                                    

    GameState _gameState;
};

#endif
