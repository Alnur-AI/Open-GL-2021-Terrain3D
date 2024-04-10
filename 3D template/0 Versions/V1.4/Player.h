#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Time.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>


class Player
{
public: 
    Time time;

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
    // SET GET
    void  setCameraX(float x){ cameraX = x; }   float getCameraX(){ return cameraX; }
    void  setCameraY(float y){ cameraY = y; }   float getCameraY(){ return cameraY; }
    void  setCameraZ(float z){ cameraZ = z; }   float getCameraZ(){ return cameraZ; }

    void  setRotateX(float x){ rotateX = x; }   float getRotateX(){ return rotateX; }
    void  setRotateY(float y){ rotateY = y; }   float getRotateY(){ return rotateY; }
    void  setRotateZ(float z){ rotateZ = z; }   float getRotateZ(){ return rotateZ; }

    // WASD
    void moveCameraForward(float shift) {cameraX += shift*sin(2*M_PI/360*rotateZ);      cameraY += shift*cos(2*M_PI/360*rotateZ);}
    void moveCameraBackward(float shift){cameraX -= shift*sin(2*M_PI/360*rotateZ);      cameraY -= shift*cos(2*M_PI/360*rotateZ);}
    void moveCameraRight(float shift) {cameraX += shift*sin(2*M_PI/360*(90-rotateZ)); cameraY -= shift*cos(2*M_PI/360*(90-rotateZ));}
    void moveCameraLeft(float shift)  {cameraX -= shift*sin(2*M_PI/360*(90-rotateZ)); cameraY += shift*cos(2*M_PI/360*(90-rotateZ));}
    void moveCameraUp(float z){ cameraZ += z;}
    void moveCameraDown(float z){ cameraZ -= z;}

    // Rotate
    void rotateCameraUp   (float shift) {rotateX -= (shift/4.0);} //rotateX = rotateX > 360 ?        360         : rotateX;}
    void rotateCameraDown (float shift) {rotateX -= (shift/4.0);} //rotateX = rotateX < 180 ?        180         : rotateX;}
    void rotateCameraRight(float shift) {rotateZ += (shift/4.0);} //rotateZ = rotateZ <   0 ?   360 - rotateZ    : rotateZ;}
    void rotateCameraLeft (float shift) {rotateZ += (shift/4.0);} //rotateZ = rotateZ > 360 ?   int(rotateZ)%360 : rotateZ;}

    void checkRotateXUp()  {rotateX = rotateX > 360 ? 360 : rotateX; }
    void checkRotateXDown(){rotateX = rotateX < 180 ? 180 : rotateX;}
    void checkRotateZRight() {rotateZ = rotateZ <   0 ? 360 - rotateZ : rotateZ;}
    void checkRotateZLeft() {rotateZ = rotateZ > 360 ? int(rotateZ)%360 : rotateZ;}

private: //Camera1
    float cameraX = -8;  float rotateX = 270;
    float cameraY = -20;  float rotateY = 0;
    float cameraZ = 5;  float rotateZ = 0;
};

#endif //MAIN_PLAYER_H