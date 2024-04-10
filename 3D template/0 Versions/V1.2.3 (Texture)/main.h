#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


#include "Player.h"
#include "Screen.h"
#include "Draw.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// DRAW
Draw draw;

// SCREEN
Screen screen;

// CAMERA
Player player;


float rotateEarthZ = 0;

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

// Texture
unsigned int textureSymbol;
unsigned int textureEarth;
unsigned int textureDirt;
unsigned int textureMenu;
void LoadTexture(char *fileName, uint *target)
{
    int width;
    int height;
    int cnt;

    unsigned char *data = stbi_load(fileName, &width, &height, &cnt, 0);

    glGenTextures(1, target);
    glBindTexture(GL_TEXTURE_2D, *target);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 
                                  0, cnt == 4 ?GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

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
    screen.window = glfwCreateWindow( screen.width, screen.height, "Game", NULL, NULL );  
    if ( !screen.window )
    {
        glfwTerminate( );
        return false;
    }

    // Make the window's context current
    glfwMakeContextCurrent( screen.window );
    
    glfwSetKeyCallback        (screen.window, OnKeyboardPressed);  
  	glfwSetCursorPosCallback  (screen.window, OnMouseMove); 
    glfwSetMouseButtonCallback(screen.window, OnMouseButtonClicked);
	  glfwSetScrollCallback     (screen.window, OnMouseScroll);


    return true;
}
void set3Dsettings()
{
    float aspect =  (screen.width) / float (screen.height);

    // add it later in draw.word too!
    // НЕОБХОДИМО РАЗОБРАТЬСЯ ПОЧЕМУ НЕ ОТОБРАЖАЕТСЯ ТЕКСТ. РАЗБЕРИСЬ ЗАЧЕМ НУЖНЫ МАТРИКСМОДЫ.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-aspect,aspect, -1/aspect,1/aspect, screen.minViewDist, screen.maxViewDist);


    LoadTexture("Verdana.png", &textureSymbol);
    LoadTexture("Earth.png", &textureEarth);
    LoadTexture("Dirt.png", &textureDirt);
    LoadTexture("Menu.png", &textureMenu);

}
void ChangeScreenSize()
{
  glfwGetFramebufferSize(screen.window, &screen.width, &screen.height);
  glViewport(0, 0, screen.width, screen.height);
  //glLoadIdentity();
  //float aspect =  (screen.width) / float (screen.height);
  //glOrtho(-aspect, aspect, -1,1,-1,1);

}

// Render
void renderWorld()
{
    glPushMatrix();

        // Set Camera
        glRotatef(player.getRotateX(), 1, 0, 0);
        glRotatef(player.getRotateY(), 0, 1, 0);
        glRotatef(player.getRotateZ(), 0, 0, 1);
        glTranslatef( -player.getCameraX(), -player.getCameraY(), -player.getCameraZ() );
        
        // Draw plane (position, rotation, color, scale)
        draw.ChessBoard(textureDirt);

        // Draw Pyramid (position, rotation, color, scale)
        draw.Pyramid({3, 3, 10}, {0, 0, 0}, {0.5, 0.5, 0.5} ,{2, 2, 3});
              
        // Draw Cube (position, rotation, color, scale)
        draw.Cube({3, 3, 4}, {0, 0, 0}, {1, 0.5, 0.5} ,{4, 2, 2});

        // Draw Sphere (position, rotation, color, scale)
        draw.Sphere(15,textureEarth, {-10, -3, 4}, {0, 0, rotateEarthZ += 0.1}, {0.5, 1, 0.5} ,{5,5,5}) ;
              
    glPopMatrix();
}
void renderArms()
{
    glDisable(GL_DEPTH_TEST);
    draw.Cube({2, -0.5, -4}, {10, 22, 0}, {0.1, 0.5, 0.5} ,{1, 1, 1});
    glEnable(GL_DEPTH_TEST);
}
void showDebugSquareCenter()
{
    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
        glLoadIdentity();

        float param =  screen.width / (float)screen.height;
        glScalef( 1, param, 1 );
        float squareVert[12] = {0.01,0.01,0,   0.01,-0.01,0,   -0.01,-0.01,0,   -0.01,0.01,0};
        glEnableClientState(GL_VERTEX_ARRAY);  


            glVertexPointer(3, GL_FLOAT, 0, &squareVert);
            glColor3f( 0.0 , 0 , 0.0);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 


        glDisableClientState(GL_VERTEX_ARRAY); 

    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

// Other
void MoveCamera()
{
  // UP DOWN
  if( Input.keys[GLFW_KEY_SPACE] ) player.moveCameraUp(0.1);//player.setCameraZ(player.getCameraZ + 0.1);//cameraPosZ += 0.1
  if( Input.keys[GLFW_KEY_LEFT_CONTROL] ) player.moveCameraDown(0.1);
    
  // WASD
  if( Input.keys[GLFW_KEY_W] ) player.moveCameraForward(0.1); 
  if( Input.keys[GLFW_KEY_S] ) player.moveCameraBackward(0.1);
  if( Input.keys[GLFW_KEY_D] ) player.moveCameraRight(0.1);
  if( Input.keys[GLFW_KEY_A] ) player.moveCameraLeft(0.1);

  // MOUSE
  if(Input.yoffset > 0) player.rotateCameraUp(Input.yoffset);   player.checkRotateXUp(); 
  if(Input.yoffset < 0) player.rotateCameraDown(Input.yoffset); player.checkRotateXDown();
  if(Input.xoffset > 0) player.rotateCameraRight(Input.xoffset);player.checkRotateZRight();
  if(Input.xoffset < 0) player.rotateCameraLeft(Input.xoffset); player.checkRotateZLeft();

  // CLEAR MOUSE
  Input.xoffset = 0;
  Input.yoffset = 0;
}
void drawMenu()
{
  if(Input.keys[GLFW_KEY_TAB])
  {
    //draw.Square(textureMenu);
    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
        glLoadIdentity();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureMenu);

        float texCoord[] = {1,0,  1,1,  0,1,  0,0};
        float param =  screen.width / (float)screen.height;
        glScalef( 10, 10*param, 10 );
        float squareVert[12] = {0.1,0.1,0,   0.1,-0.1,0,   -0.1,-0.1,0,   -0.1,0.1,0};

        glEnableClientState(GL_VERTEX_ARRAY);  
        glEnableClientState(GL_TEXTURE_COORD_ARRAY); 


            glVertexPointer(3, GL_FLOAT, 0, &squareVert);
            glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
            glColor3f( 0.0 , 0 , 0.0);
            glColor3f( 1 , 1 , 1);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 

        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY); 
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
  }

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
  std::cout <<  std::setprecision(3) << "x: " << (player.getCameraX()) << "\ny: " << (player.getCameraY()) << "\nz: " << (player.getCameraZ()) << "\n\nFPS:" << int (1.0/deltaTime) <<"\n";
  std::cout <<  std::setprecision(3) << "xAngle: " << (player.getRotateX()) << "\nyAngle: " << (player.getRotateY()) << "\nzAngle: " << (player.getRotateZ()) << "\n\nFPS:" << int (1.0/deltaTime) <<"\n";
  std::cout <<  "Mouse x: " << Input.lastX +  Input.xoffset << " Mouse y: " << Input.lastY + Input.yoffset << "\n\n\n\n";
  std::cout <<  "WASD - move around\n";
  std::cout <<  "Mouse - move around\n";
  std::cout <<  "Right mouse - capture mouse\n";
  std::cout <<  "Shift - acceleration\n";
  std::cout <<  "Space - move up\n";
  std::cout <<  "CTRL - move down\n";
  std::cout <<  "TAB - Open menu\n\n";
}




#endif //MAIN_H_
