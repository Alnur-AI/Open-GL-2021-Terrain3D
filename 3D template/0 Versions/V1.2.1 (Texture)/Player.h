#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H


#endif //MAIN_PLAYER_H

/* old

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>


class Player
{
public: // Control (Mouse and Keyboard)
    void setKeys(int i, bool key){ keys[i] = key; }                          bool  getKeys(int i){ return keys[i]; }
    void setLastX(float x){ lastX = x; }                                     float getLastX(){return lastX;}
    void setLastY(float y){ lastY = y; }                                     float getLastY(){return lastY;}
    void setXoffSet(float x){ xoffset = x; }                                 float getXoffSet(){return xoffset;}
    void setYoffSet(float y){ yoffset = y; }                                 float getYoffSet(){return yoffset;}
    void setFirstMouse(bool fm){ firstMouse = fm; }                          bool  getFirstMouse(){return firstMouse;}
    void setCaptureMouse(bool cm){ captureMouse = cm; }                      bool  getCaptureMouse(){return captureMouse;}
    void setCapturedMouseJustNow(bool cmjn){ capturedMouseJustNow = cmjn; }  bool  getCapturedMouseJustNow(){return capturedMouseJustNow;}

private: // Control
    bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
    float lastX = 400, lastY = 300; //исходное положение мыши
    float xoffset = 0, yoffset = 0;
    bool firstMouse = true;
    bool captureMouse = true;  // Мышка захвачена нашим приложением или нет?
    bool capturedMouseJustNow = false;

public: // Camera
    void  setCameraX(float x){ cameraX = x; }   float getCameraX(){ return cameraX; }
    void  setCameraY(float y){ cameraY = y; }   float getCameraY(){ return cameraY; }
    void  setCameraZ(float z){ cameraZ = z; }   float getCameraZ(){ return cameraZ; }

    void  setRotateX(float x){ rotateX = x; }   float getRotateX(){ return rotateX; }
    void  setRotateY(float y){ rotateY = y; }   float getRotateY(){ return rotateY; }
    void  setRotateZ(float z){ rotateZ = z; }   float getRotateZ(){ return rotateZ; }

private: //Camera1
    float cameraX = 0;  float rotateX = 0;
    float cameraY = 0;  float rotateY = 0;
    float cameraZ = 5;  float rotateZ = 0;
};

*/