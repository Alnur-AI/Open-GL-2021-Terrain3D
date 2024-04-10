#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <iomanip>
#include <vector>

#include "Player.h"
#include "Draw.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

Draw draw;
GLFWwindow *window;

int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

float xAngle = 270;
float yAngle = 0;
float zAngle = 0;

float cameraPosX = 0.0;
float cameraPosY = -20.0;
float cameraPosZ = 7.0;

float lightTheta = 0;

// TIME
int FPS = 0;
GLdouble currentFrame  = 0.0f;
GLdouble deltaTime = 0.0f;
GLdouble lastFrame = 0.0f;


// IMPUT
struct InputState
{
  bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
  GLfloat lastX = 400, lastY = 300; //исходное положение мыши
  GLfloat xoffset, yoffset;
  bool firstMouse = true;
  bool captureMouse         = true;  // Мышка захвачена нашим приложением или нет?
  bool capturedMouseJustNow = false;
} static Input;

void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		break;
  case GLFW_KEY_1:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    break;
  case GLFW_KEY_2:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    break;
	default:
		if (action == GLFW_PRESS)
      Input.keys[key] = true;
		else if (action == GLFW_RELEASE)
      Input.keys[key] = false;
	}
}

void OnMouseButtonClicked(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    Input.captureMouse = !Input.captureMouse;

  if (Input.captureMouse)
  {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    Input.capturedMouseJustNow = true;
  }
  else
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

void OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
  if (Input.firstMouse)
  {
    Input.lastX = float(xpos);
    Input.lastY = float(ypos);
    Input.firstMouse = false;
  }

  GLfloat xoffset = float(xpos) - Input.lastX;
  GLfloat yoffset = Input.lastY - float(ypos);

  Input.xoffset = xoffset;
  Input.yoffset = yoffset;

  Input.lastX = float(xpos);
  Input.lastY = float(ypos);
}

void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
  // ...
}

// Preparation
bool GameInit()
{
    // Initialize the library
    if ( !glfwInit( ) )
    {
        return false;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "CG TASK 3", NULL, NULL );  
    if ( !window )
    {
        glfwTerminate( );
        return false;
    }

    // Make the window's context current
    glfwMakeContextCurrent( window );
    
    glfwSetKeyCallback        (window, OnKeyboardPressed);  
  	glfwSetCursorPosCallback  (window, OnMouseMove); 
    glfwSetMouseButtonCallback(window, OnMouseButtonClicked);
	glfwSetScrollCallback     (window, OnMouseScroll);



    return true;
}

void set3Dsettings()
{
    float param = float (SCREEN_WIDTH) / float (SCREEN_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-param,param,-1,1,2,500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ChangeScreenSize()
{
  glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

// Render
void renderWorld()
{
    glPushMatrix();

        // Set Camera
        glRotatef(xAngle, 1, 0, 0);
        glRotatef(yAngle, 0, 1, 0);
        glRotatef(zAngle, 0, 0, 1);
        glTranslatef( -cameraPosX, -cameraPosY, -cameraPosZ );

        // Set Light 0
        glPushMatrix();
          lightTheta+=0.5;
          glRotatef(lightTheta, 0, 1, 0);
          float position[] = {0,0,10,0};
          glLightfv(GL_LIGHT0, GL_POSITION, position);
        
          glTranslatef(0,0,10);
          glScalef(1, 1, 1);
          draw.Square(1,1,0);
        glPopMatrix();

        // Draw plane (position, rotation, color, scale)
        draw.ChessBoard();

        // Draw Pyramid (position, rotation, color, scale)
        draw.Pyramid({3, 3, 10}, {0, 0, 0}, {0.5, 0.5, 0.5} ,{2, 2, 3});
              
        // Draw Cube (position, rotation, color, scale)
        draw.Cube({0, 0, 4}, {0, 0, 0}, {1, 0.5, 0.5} ,{7, 7, 7});

        // Draw Sphere (position, rotation, color, scale)
        draw.Sphere(30, {-5, -5, 4}, {0, 0, 0}, {0.5, 1, 0.5} ,{2, 2, 2}) ;
              
    glPopMatrix();
}

void renderArms()
{
  glDisable(GL_NORMALIZE);
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    draw.Cube({2, -0.5, -4}, {10, 22, 0}, {0.1, 0.5, 0.5} ,{1, 1, 1});
    glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);
}

void showDebugText()
{
  glDisable(GL_NORMALIZE);
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);

    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
        glLoadIdentity();

        float param =  SCREEN_WIDTH / (float)SCREEN_HEIGHT;
        glScalef( 1, param, 1 );
        float squareVert[12] = {0.1,0.1,0,   0.1,-0.1,0,   -0.1,-0.1,0,   -0.1,0.1,0};
        glEnableClientState(GL_VERTEX_ARRAY);  
            glVertexPointer(3, GL_FLOAT, 0, &squareVert);
            glColor3f( 0.0 , 0 , 0.0);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 
        glDisableClientState(GL_VERTEX_ARRAY); 

    glPopMatrix();
    glEnable(GL_DEPTH_TEST);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);
}

// Other
void MoveCamera()
{
  // UP DOWN
  if( Input.keys[GLFW_KEY_SPACE] ) cameraPosZ += 0.1;
  if( Input.keys[GLFW_KEY_LEFT_CONTROL] ) cameraPosZ -= 0.1;
    
  // WASD
  if( Input.keys[GLFW_KEY_W] ) {cameraPosX += 0.1*sin(2*M_PI/360*zAngle);      cameraPosY += 0.1*cos(2*M_PI/360*zAngle);}
  if( Input.keys[GLFW_KEY_S] ) {cameraPosX -= 0.1*sin(2*M_PI/360*zAngle);      cameraPosY -= 0.1*cos(2*M_PI/360*zAngle);}
  if( Input.keys[GLFW_KEY_D] ) {cameraPosX += 0.1*sin(2*M_PI/360*(90-zAngle)); cameraPosY -= 0.1*cos(2*M_PI/360*(90-zAngle));}
  if( Input.keys[GLFW_KEY_A] ) {cameraPosX -= 0.1*sin(2*M_PI/360*(90-zAngle)); cameraPosY += 0.1*cos(2*M_PI/360*(90-zAngle));}

  // MOUSE
  if(Input.yoffset > 0) xAngle -= (Input.yoffset/3.0) ; xAngle = xAngle > 360 ?       360         : xAngle;
  if(Input.yoffset < 0) xAngle -= (Input.yoffset/3.0) ; xAngle = xAngle < 180 ?       180         : xAngle;
  if(Input.xoffset > 0) zAngle += (Input.xoffset/3.0) ; zAngle = zAngle <   0 ?   360 - zAngle    : zAngle;
  if(Input.xoffset < 0) zAngle += (Input.xoffset/3.0) ; zAngle = zAngle > 360 ?   int(zAngle)%360 : zAngle;

  // CLEAR MOUSE
  Input.xoffset = 0;
  Input.yoffset = 0;
}

void CountingFPS()
{
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    FPS = int(1.0/deltaTime);
}

void ShowDebugInfo()
{
  std::cout <<  std::setprecision(3) << "x: " << (cameraPosX) << "\ny: " << (cameraPosY) << "\nz: " << (cameraPosZ) << "\n\nFPS:" << int (1.0/deltaTime) <<"\n";
  std::cout <<  std::setprecision(3) << "xAngle: " << (xAngle) << "\nyAngle: " << (yAngle) << "\nzAngle: " << (zAngle) << "\n\nFPS:" << int (1.0/deltaTime) <<"\n";
  //std::cout <<  "Mouse x: " << Input.lastX +  Input.xoffset << " Mouse y: " << Input.lastY + Input.yoffset << "\n\n\n\n";
  std::cout <<  "WASD - move around\n";
  std::cout <<  "Mouse - move around\n";
  std::cout <<  "Right mouse - capture mouse\n";
  std::cout <<  "Shift - acceleration\n";
  std::cout <<  "Space - move up\n";
  std::cout <<  "CTRL - move down\n\n\n\n\n\n";
}





#endif //MAIN_H_
