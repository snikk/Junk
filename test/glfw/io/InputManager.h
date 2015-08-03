#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <unordered_map>
#include <glm/glm.hpp>
#include "../common.h"

class InputManager {
public:
    static InputManager& instance() {
        static InputManager manager;
        return manager;
    }
    static void keyFunction(GLFWwindow *win, int key, int scancode, int action, int mods);
    static void cursorFunction(GLFWwindow *win, double xPos, double yPos);

    void update();         

    void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID); 
    
    void setMouseCoords(float x, float y);

    /// Returns true if the key is held down
    bool isKeyDown(unsigned int keyID);

    /// Returns true if the key was just pressed
    bool isKeyPressed(unsigned int keyID);

    //getters              
    glm::vec2 getMouseCoords() const { return _mouseCoords; }
private:
    InputManager();
    ~InputManager();
    InputManager(InputManager const&) = delete;
    void operator=(InputManager const&) = delete;

    /// Returns true if the key is held down
    bool wasKeyDown(unsigned int keyID); 

    std::unordered_map<unsigned int, bool> _previousKeyMap;
    std::unordered_map<unsigned int, bool> _keyMap;
    glm::vec2 _mouseCoords;
};

#endif
