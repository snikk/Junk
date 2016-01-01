#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "../common.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//Camera class for 2D games
class Camera2D         
{
public:                
    Camera2D();        
    ~Camera2D();       
    
    //sets up the orthographic matrix and screen dimensions
    void init(int screenWidth, int screenHeight); 

    //updates the camera matrix if needed
    void update();     

    glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);
    
    bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

    //setters
    void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
    void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }

    //getters          
    glm::vec2 getPosition() { return _position; }

    float getScale() { return _scale; }
    glm::mat4 getCameraMatrix() { return _cameraMatrix; }
    glm::mat4 getInverseMatrix() { return _cameraMatrixInverse; }

private:               
    int _screenWidth, _screenHeight;
    bool _needsMatrixUpdate;        
    float _scale;      
    glm::vec2 _position;
    glm::mat4 _cameraMatrix;        
    glm::mat4 _cameraMatrixInverse;        
    glm::mat4 _orthoMatrix;
};

#endif
