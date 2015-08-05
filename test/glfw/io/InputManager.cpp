#include "InputManager.h"

void InputManager::keyFunction(GLFWwindow *win, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
        instance().pressKey(key);
    if (action == GLFW_RELEASE)
        instance().releaseKey(key);
}

void InputManager::cursorFunction(GLFWwindow *win, double xPos, double yPos) {
    instance().setMouseCoords(xPos, yPos);
}

void InputManager::mouseButtonFunction(GLFWwindow *win, int button, int action, int mods) {
    if (action == GLFW_PRESS)
        instance().pressKey(button);
    if (action == GLFW_RELEASE)
        instance().releaseKey(button);
}

InputManager::InputManager() : _mouseCoords(0.0f) {}
InputManager::~InputManager() {}

void InputManager::update() {
    for (auto& it : _keyMap) {
        _previousKeyMap[it.first] = it.second;
    }
}

void InputManager::pressKey(unsigned int keyID) {
    _keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
    _keyMap[keyID] = false;
}

void InputManager::setMouseCoords(float x, float y) {
    _mouseCoords.x = x;
    _mouseCoords.y = y;
    printf("Set mouse | x = %f | y = %f\n", _mouseCoords.x, _mouseCoords.y);
}

/// Returns true if the key is held down
bool InputManager::isKeyDown(unsigned int keyID) {
    auto it = _keyMap.find(keyID);
    if (it != _keyMap.end()) {
        return it->second;
    }

    return false;
}

/// Returns true if the key was just pressed
bool InputManager::isKeyPressed(unsigned int keyID) {
    return isKeyDown(keyID) == true && wasKeyDown(keyID) == false;
}

/// Returns true if the key is held down
bool InputManager::wasKeyDown(unsigned int keyID) {
    auto it = _previousKeyMap.find(keyID);
    if (it != _previousKeyMap.end()) {
        return it->second;
    }

    return false;
}

