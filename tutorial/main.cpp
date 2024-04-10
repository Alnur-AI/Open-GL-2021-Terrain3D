#include "Engine/Image/Image.h"
//#include "Engine/Camera/camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string> 
#include <iomanip>  
#include "math.h"


#define STB_IMAGE_IMPLEMENTATION
#include "Engine/Image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Engine/Image/stb_image_write.h"

 

// WINDOW
GLFWwindow *window;

int SCREEN_WIDTH  = 800;
int SCREEN_HEIGHT = 600;

Pixel backgroundColor = {0.5f, 0.5f, 1.0f, 0.0f};



// MAP
typedef struct
{
  float x,y,z;
} TCell;
typedef struct
{
  float r,g,b;
} TColor;

#define mapW 100
#define mapH 100

TCell map[mapW][mapH];
TColor mapCol[mapW][mapH];

GLuint mapInd[mapW-1][mapH-1][6];
int mapIndCnt = sizeof(mapInd)/ sizeof(GLuint);



// SQUARE
//float floorVert[] = {1,1,0,  1,-1,0, -1,-1,0,  -1,1,0 };
float floorVert[] = {-1,-1,0,  1,-1,0, 1,1,0,  -1,1,0 };
float texCoord[] = {0,1,  1,1,  1,0,  0,0};



// TIME
int FPS = 0;
GLdouble currentFrame  = 0.0f;
GLdouble deltaTime = 0.0f;
GLdouble lastFrame = 0.0f;



// CAMERA
struct SCamera
{
	float x,y,z;
	float Xrot, Zrot;
}camera = {0,0,3, 0,0};


struct InputState
{
  bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
  GLfloat lastX = 400, lastY = 300; //исходное положение мыши
  GLfloat xoffset = 0, yoffset = 0;
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

  Input.xoffset = floor(float(xpos) - Input.lastX);
  Input.yoffset = floor(Input.lastY - float(ypos));


  Input.lastX = float(xpos);
  Input.lastY = float(ypos);
}

void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
  // ...
}




bool IsCoordInMap(float x, float y)
{
  return ( x>= 0 ) && (x < mapW) && (y >= 0) && (y < mapH);
}

void MapCreateHill(int posX, int posY, int rad, int height)
{
  for (int i = posX - rad; i < posX+rad; i++)
    for (int j = posY-rad; j < posY+rad; j++)
      if(IsCoordInMap(i,j))
      {
        float len = sqrt( pow(posX-i,2) + pow(posY - j,2) );
        if(len < rad)
        {
          len = len / rad * M_PI_2;
          map[i][j].z += cos(len)*height;
        }
      }
      
  

}

void MapColor()
{
  for (int i = 0; i < mapW; i++)
    for (int j = 0; j < mapH; j++)
    {
      mapCol[i][j].r = 0.31 + map[i][j].z*0.05;
      mapCol[i][j].g = 0.5 + map[i][j].z*0.0005;
      mapCol[i][j].b = 0.13 +  map[i][j].z*0.0005 ;


      if( mapW/2 - 3 < i-20 && i-20 < mapW/2 + 3 ){
        mapCol[i][j].r = 0.0;
        mapCol[i][j].g = 0.0;
        mapCol[i][j].b = 1.0;
      }
    }

}

void MapInit()
{
  for (int i = 0; i < mapW; i++)
    for (int j = 0; j < mapH; j++)
    {
      float dc = (rand()%20)*0.01;

      mapCol[i][j].r = 0.31 + dc;
      mapCol[i][j].g = 0.5 + dc;
      mapCol[i][j].b = 0.13 + dc;

      map[i][j].x = i;
      map[i][j].y = j;
      map[i][j].z = (rand() %10)*0.05;
    }

  for (int i = 0; i < mapW-1; i++)
  {
    int pos = i*mapH;
    for (int j = 0; j < mapH-1; j++){
      mapInd[i][j][0] = pos;
      mapInd[i][j][1] = pos + 1;
      mapInd[i][j][2] = pos + 1 + mapH;

      mapInd[i][j][3] = pos + 1 + mapH;
      mapInd[i][j][4] = pos + mapH;
      mapInd[i][j][5] = pos;

      pos++;
    }
  }  

  for (int i = 0; i < 10; i++)
    MapCreateHill(rand() % mapW, rand() % mapH, rand() % 50, rand()%10);
  

}




unsigned int textureSymbol;
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

void SymbolDrawWord(std::string text)
{
  glLoadIdentity();
  glOrtho(-20, 20, -20, 20, -20, 20);

        glDisable(GL_DEPTH_TEST); 
        glEnableClientState(GL_VERTEX_ARRAY);


          glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureSymbol);

            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
              glPushMatrix();
                glColor3f(1.0, 1.0, 1.0);
                
                glTexCoordPointer(2, GL_FLOAT, 0, texCoord);

                for (int i = 0; i < text.length(); i++)
                {
                  static float charSize = 1/16.0;
                  char c = text[i];
                  int y = c >> 4;
                  int x = c & 0b1111;
                  struct {float left, right, top, bottom;} rct;

                  rct.left = x*charSize;
                  rct.right = rct.left + charSize;
                  rct.top = y*charSize;
                  rct.bottom = rct.top + charSize;
                    texCoord[0] = texCoord[6] = rct.left;
                    texCoord[2] = texCoord[4] = rct.right;
                    texCoord[1] = texCoord[3] = rct.bottom;
                    texCoord[5] = texCoord[7] = rct.top;
                  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
                  glTranslatef(2,0,0);
                }

              glPopMatrix();
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
          glDisable(GL_TEXTURE_2D);
          

        glDisableClientState(GL_VERTEX_ARRAY);
        glEnable(GL_DEPTH_TEST); 

  float param = float (SCREEN_WIDTH) / float (SCREEN_HEIGHT);

  glLoadIdentity();
  glFrustum(-param,param,-1,1,1.5,2000);
}




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


    // Texture 
    LoadTexture("Engine/Symbol/Verdana.png", &textureSymbol);


    return true;
}

void Set3DSettings()
{
  // 3D setting

  float param = float (SCREEN_WIDTH) / float (SCREEN_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-param,param,-1,1,1.5,2000);
  //glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
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
  std::cout <<  std::setprecision(3) << "x: " << (camera.x) << "\ny: " << (camera.y) << "\nz: " << (camera.z) << "\n\nFPS:" << int (1.0/deltaTime) <<"\n";
  std::cout <<  "Mouse x: " << Input.lastX +  Input.xoffset << " Mouse y: " << Input.lastY + Input.yoffset << "\n\n\n\n";
  std::cout <<  "WASD - move around\n";
  std::cout <<  "Mouse - move around\n";
  std::cout <<  "Right mouse - capture mouse\n";
  std::cout <<  "Shift - acceleration\n";
  std::cout <<  "Space - move up\n";
  std::cout <<  "CTRL - move down\n\n\n\n\n\n";



}

void ChangeScreenSize()
{
  glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool ExitState()
{
  if (Input.keys[GLFW_KEY_ESCAPE]) return true;
  else return false;
}



void ShowWorld()
{
  /* BASIC MAP
  glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &floorVert);

    // Draw basic map
    for(int i = -32; i < 32; i++)
      for (int j = -32; j < 32; j++)
      {
        glPushMatrix();

          if( (i+j)%2 == 0 ) glColor3f(0, 0.5, 0);
          else glColor3f(1, 1, 1);

          if( i == int(   round (camera.x )/2  ) && j == int(  round (camera.y)/2   )    )
            glColor3f(0.5, 0.0, 0);

          
          glTranslatef(i*2, j*2, 0);

          glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glPopMatrix();
      }
      

  glDisableClientState(GL_VERTEX_ARRAY);
  */

  //* BEAUTY MAP
  //glEnable(GL_LIGHTING);
  //glEnable(GL_LIGHT0);
  //glEnable(GL_COLOR_MATERIAL);
  //glEnable(GL_NORMALIZE);


  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, map);
  glColorPointer(3, GL_FLOAT, 0, mapCol);

  glDrawElements(GL_TRIANGLES, mapIndCnt, GL_UNSIGNED_INT, mapInd);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);

  //glDisable(GL_LIGHTING);
  //glDisable(GL_LIGHT0);
  //glDisable(GL_COLOR_MATERIAL);
  //glDisable(GL_NORMALIZE);
  //*/

}

void MoveCamera()
{

  float angle = -camera.Zrot / 180 * M_PI;
  float speed = 0;
  float accelerate = 1.0;


  // HEIGHT CONTROL
  if(Input.keys[GLFW_KEY_SPACE]) camera.z +=0.1;
  if(Input.keys[GLFW_KEY_LEFT_CONTROL]) camera.z -=0.1;

  // MOVE ACCELERATION 
  if(Input.keys[GLFW_KEY_LEFT_SHIFT]) accelerate = 2.5;
  else accelerate = 1.0;


  // MOUSE
  if(Input.yoffset > 0) camera.Xrot += (Input.yoffset/3.0) ; camera.Xrot = camera.Xrot > 180 ? 180 : camera.Xrot;
  if(Input.yoffset < 0) camera.Xrot += (Input.yoffset/3.0) ; camera.Xrot = camera.Xrot <   0 ?   0 : camera.Xrot;
  if(Input.xoffset > 0) camera.Zrot -= (Input.xoffset/3.0);
  if(Input.xoffset < 0) camera.Zrot -= (Input.xoffset/3.0);

  Input.xoffset = 0;
  Input.yoffset = 0;

  //if(Input.keys[GLFW_KEY_UP]) camera.Xrot += 0.78; camera.Xrot = camera.Xrot > 180 ? 180 : camera.Xrot;
  //if(Input.keys[GLFW_KEY_DOWN]) camera.Xrot -= 0.78; camera.Xrot = camera.Xrot <   0 ?   0 : camera.Xrot;
  //if(Input.keys[GLFW_KEY_LEFT]) camera.Zrot++;
  //if(Input.keys[GLFW_KEY_RIGHT]) camera.Zrot--;

  
  // WALK
  if(Input.keys[GLFW_KEY_W]) speed = 0.1;
  if(Input.keys[GLFW_KEY_S]) speed = -0.1;
  if(Input.keys[GLFW_KEY_A]) {speed = 0.1; angle -= M_PI*0.5;}
  if(Input.keys[GLFW_KEY_D]) {speed = 0.1; angle += M_PI*0.5;}


  // SPECIAL WALK MODE
  //if(Input.keys[GLFW_KEY_W] && Input.keys[GLFW_KEY_A]){ speed = +0.1;  angle += M_PI*0.5; zAlpha++; }
  //if(Input.keys[GLFW_KEY_W] && Input.keys[GLFW_KEY_D]){ speed = +0.1;  angle -= M_PI*0.5; zAlpha--; }
  //if(Input.keys[GLFW_KEY_S] && Input.keys[GLFW_KEY_A]){ speed = -0.05; angle += M_PI*0.5; zAlpha--; }
  //if(Input.keys[GLFW_KEY_S] && Input.keys[GLFW_KEY_D]){ speed = -0.05; angle -= M_PI*0.5; zAlpha++; }


  // IF WE MOVED
  if(speed != 0)
  {
      camera.x += sin(angle)*speed*accelerate;
      camera.y += cos(angle)*speed*accelerate;
  }



  

  // MATRIX TRANSFORMATION
  glRotatef(-camera.Xrot, 1,0,0);
  glRotatef(-camera.Zrot, 0,0,1);
  glTranslatef(-camera.x,-camera.y,-camera.z);

}


int main( void )
{
    // Initialize game
    if( !GameInit() ) return -1;

    // Enable Z-buffer
    glEnable(GL_DEPTH_TEST); 

    // 3D settings for perspective 
    Set3DSettings();

    // Create Map
    MapInit();
    MapColor();

    /* Loop until the user closes the window */
    while ( !glfwWindowShouldClose( window ) )
    {
        // Exit setting
        if ( ExitState() ) break;

        // Counting fps and deltaTime
        CountingFPS();

        // Debug information in console
        ShowDebugInfo();

        // If you change screen size
        ChangeScreenSize();    

        // Set backglound color; Clear screen. Clear only screen color;
        glClearColor( backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        /* START RENDERING HERE */

          // draw world
          glPushMatrix();
            MoveCamera();
            ShowWorld();
          glPopMatrix();

          // draw text here (don't work with beauty map)
          SymbolDrawWord(std::to_string( FPS ) );

        /*END RENDERING HERE*/


        // Swap front and back buffers (Because OPEN GL use double bufferisation)
        glfwSwapBuffers( window );
        
        // Poll for and process events
        glfwPollEvents( );
    }
    

    // Before exit
    glDisable(GL_DEPTH_TEST);
    glfwTerminate( );
    
    return 0;
}
