#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


#include "Engine/Player.h"
#include "Engine/Rendering/Screen.h"
#include "Engine/Rendering/Draw.h"

// TEXTURE
#include "Engine/Rendering/Image.h"

// DRAW
Draw draw;

// SCREEN
Screen screen;

// CAMERA TIME
Player player;

float rotateEarthZ = 0;



// INPUT
struct InputState
{
  bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
  GLfloat lastX = 400, lastY = 300; //исходное положение мыши
  GLfloat xoffset, yoffset;
  bool firstMouse = true;
  bool captureMouse         = false;  // Мышка захвачена нашим приложением или нет?
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
void InitWord(char *fileName, uint *target){
  
  draw.charWidthArray = (float*)malloc( sizeof(*draw.charWidthArray)*256 );
  for (int i = 0; i < 256; i++){
    draw.charWidthArray[i] = 1;
  }

  int width;
  int height;
  int cnt;

  unsigned char *data = stbi_load(fileName, &width, &height, &cnt, 0);

  unsigned char alpha;

  int pixPerChar = width / 16;
  for(int k = 0; k < 256; k++)
  {
    int x = (k % 16)*pixPerChar;
    int y = (k / 16)*pixPerChar;
    int i;
    int ind; 
    for(i = x + pixPerChar - 1; i > x; i--)
    {
      for (int j = y + pixPerChar-1; j > y; j--)
      {
        alpha = data[ (j*width + i)*cnt + 3 ];
        if(alpha > 0)break;
      }
      if(alpha>0)break;
    }
    i += pixPerChar /5.0;
    if(i > x+pixPerChar - 1)i = x+pixPerChar-1;
    if(k==32)i=(x+pixPerChar/2.0);

    draw.charWidthArray[k] = (i-x)/(float)pixPerChar;
  }

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

    // Load GLAD
    gladLoadGL();

    // Load textures
    InitWord("Engine/Textures/Verdana_Alpha.png", &textureSymbol);
    LoadTexture("Engine/Textures/Earth.png", &textureEarth);
    LoadTexture("Engine/Textures/Dirt.png", &textureDirt);
    LoadTexture("Engine/Textures/Menu.png", &textureMenu);

    // Return
    return true;
}
void set3Dsettings()
{
  float aspect =  (screen.width) / float (screen.height);
    
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-aspect/10,aspect/10, -1/aspect/10,1/aspect/10, screen.minViewDist, screen.maxViewDist);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

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
  std::vector<float> position;
  std::vector<float> rotation ;
  std::vector<float> color ;
  std::vector<float> scale;
  glPushMatrix();

        // Set Camera
        glRotatef(player.getRotateX(), 1, 0, 0);
        glRotatef(player.getRotateY(), 0, 1, 0);
        glRotatef(player.getRotateZ(), 0, 0, 1);
        glTranslatef( -player.getCameraX(), -player.getCameraY(), -player.getCameraZ() );
        
        // Set Light0
        glPushMatrix();
          glRotatef(rotateEarthZ, 0, 1, 0);
          glTranslatef(0,0,10);

          float light0Position[] = {0,0,1,0};
          glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

          draw.Square(1,1,0,0.1);
        glPopMatrix();
        
 
        // Draw plane (position, rotation, color, scale)
        draw.ChessBoard(textureDirt, 1);

        // Draw Pyramid (position, rotation, color, scale)
        position = {-3, -3, 1};
        rotation = { 0,  0, 0};
        color = {0.5, 0.5, 0.5,0.5};
        scale = {2, 2, 3};
        draw.Pyramid(position, rotation, color, scale);
              
        // Draw Cube (position, rotation, color, scale)
        position = {3, 3, 4};
        rotation = {0, 0, 0} ;
        color = {1, 0.5, 0.5,0.5} ;
        scale = {4, 2, 2};
        draw.Cube(position, rotation, color, scale);

        // Draw Sphere (position, rotation, color, scale)
        //draw.Sphere(10, {0, 0, 0}, {0, 0, rotateEarthZ += 0.2}, {0.5, 1, 0.5,1} ,{3,3,3}) ;
        position = {0, 0, 0};
        rotation = {0, 0, rotateEarthZ += 0.2};
        color = {0.5, 1, 0.5,1};
        scale = {100,100,100};
        draw.Sphere(20,textureEarth, position, rotation, color, scale );
              
  glPopMatrix();
}
void renderArms()
{
  //glDisable(GL_DEPTH_TEST);
  draw.Cube({2, -0.5, -4}, {10, 22, 0}, {0.1, 0.5, 0.5,1} ,{1, 1, 1});
  //glEnable(GL_DEPTH_TEST);
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
  if(Input.captureMouse){
    if(Input.xoffset > 0) player.rotateCameraRight(Input.xoffset);player.checkRotateZRight();
    if(Input.xoffset < 0) player.rotateCameraLeft(Input.xoffset); player.checkRotateZLeft();
    if(Input.yoffset > 0) player.rotateCameraUp(Input.yoffset);   player.checkRotateXUp(); 
    if(Input.yoffset < 0) player.rotateCameraDown(Input.yoffset); player.checkRotateXDown();
  }

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
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glPushMatrix();
        glLoadIdentity();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureMenu);

        float texCoord[] = {1,0,  1,1,  0,1,  0,0};
        float param =  screen.width / (float)screen.height;
        glScalef( 1*param, 1*param, 1 );
        float squareVert[12] = {1,1,0,   1,-1,0,   -1,-1,0,   -1,1,0};

        glEnableClientState(GL_VERTEX_ARRAY);  
        glEnableClientState(GL_TEXTURE_COORD_ARRAY); 

            glVertexPointer(3, GL_FLOAT, 0, &squareVert);
            glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
            glColor3f( 1 , 1 , 1);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 

        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY); 
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
  }

}
void CountingFPS()
{
  player.time.currentFrame = glfwGetTime();
  player.time.deltaTime = player.time.currentFrame - player.time.lastFrame;
  player.time.lastFrame = player.time.currentFrame;

  player.time.FPS[player.time.indFPS] = int(1.0/player.time.deltaTime);

  player.time.indFPS++; if(player.time.indFPS >= FPScount) player.time.indFPS = 0;

  for (int i = 0; i < FPScount; i++)
    player.time.averFPS += player.time.FPS[i];

  player.time.averFPS /= FPScount;
}
void ShowDebugInfo()
{
  std::cout <<  std::setprecision(3) << "x: " << (player.getCameraX()) << "\ny: " << (player.getCameraY()) << "\nz: " << (player.getCameraZ()) << "\n\nFPS:" << player.time.averFPS  <<"\n";
  std::cout <<  std::setprecision(3) << "xAngle: " << (player.getRotateX()) << "\nyAngle: " << (player.getRotateY()) << "\nzAngle: " << (player.getRotateZ()) << "\n\nFPS:" << player.time.averFPS <<"\n";
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
