#include "Engine/Image/Image.h"
//#include "Engine/Camera/camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <iomanip>  
#include "math.h"

GLFWwindow *window;

int SCREEN_WIDTH  = 1280;
int SCREEN_HEIGHT = 720;

Pixel backgroundColor;

typedef struct
{
  float x,y,z;
} TCell;
typedef struct
{
  float r,g,b;
} TColor;


#define mapW 1000
#define mapH 1000

TCell map[mapW][mapH];
TColor mapCol[mapW][mapH];

GLuint mapInd[mapW-1][mapH-1][6];
int mapIndCnt = sizeof(mapInd)/ sizeof(GLuint);


float floorVert[] = {1,1,0,  1,-1,0, -1,-1,0,  -1,1,0 };


GLdouble deltaTime = 0.0f;
GLdouble lastFrame = 0.0f;


struct SCamera
{
	float x,y,z;
	float Xrot, Zrot;
};

struct SCamera camera = {0,0,3, 0,0};


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
      mapCol[i][j].r = 0.31 + map[i][j].z*0.1;
      mapCol[i][j].g = 0.5 ;
      mapCol[i][j].b = 0.13 +  map[i][j].z*0.1 ;
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

  for (int i = 0; i < 100; i++)
    MapCreateHill(rand() % mapW, rand() % mapH, rand() % 50, rand()%10);
  

}



void ShowWorld()
{
  //* BASIC MAP
  glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &floorVert);


    for(int i = -32; i < 32; i++)
      for (int j = -32; j < 32; j++)
      {
        glPushMatrix();

          if( (i+j)%2 == 0 ) glColor3f(0, 0.5, 0);
          else glColor3f(1, 1, 1);

          if( i == int(   round (camera.x )/2  ) && j == int(  round (camera.y)/2 ) )
            glColor3f(0.5, 0.0, 0);

          
          glTranslatef(i*2, j*2, 0);

          glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glPopMatrix();
      }
      

    glPushMatrix();
      glColor3f(0.0, 0.0, 0.5);
      glTranslatef(2, 4, 2);
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();
    

  glDisableClientState(GL_VERTEX_ARRAY);
  //*/

  /*
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, map);
  glColorPointer(3, GL_FLOAT, 0, mapCol);

  glDrawElements(GL_TRIANGLES, mapIndCnt, GL_UNSIGNED_INT, mapInd);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  */
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
    // Initialize the library
    if ( !glfwInit( ) )
    {
        return -1;
    }
    


    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "CG TASK 3", NULL, NULL );  
    if ( !window )
    {
        glfwTerminate( );
        return -1;
    }
    


    // Make the window's context current
    glfwMakeContextCurrent( window );
    
    glfwSetKeyCallback        (window, OnKeyboardPressed);  
  	glfwSetCursorPosCallback  (window, OnMouseMove); 
    glfwSetMouseButtonCallback(window, OnMouseButtonClicked);
	  glfwSetScrollCallback     (window, OnMouseScroll);

    





    // 3D setting
    glEnable(GL_DEPTH_TEST);

    float param = float (SCREEN_WIDTH) / float (SCREEN_HEIGHT);

    glLoadIdentity();
    glFrustum(-param,param,-1,1,2,2000);



    MapInit();
    MapColor();


    // Set background color
    backgroundColor.r = 0.5f;
    backgroundColor.g = 0.5f;
    backgroundColor.b = 1.0f;
    backgroundColor.a = 0.0f;



    /* Loop until the user closes the window */
    while ( !glfwWindowShouldClose( window ) )
    {

        GLdouble currentFrame = glfwGetTime();
    		deltaTime = currentFrame - lastFrame;
	    	lastFrame = currentFrame;

        std::cout <<  std::setprecision(3) << "x: " << (camera.x) << "\ny: " << (camera.y) << "\nz: " << (camera.z) << "\n\nFPS:" << int (1.0/deltaTime) <<"\n";
        std::cout  << "Mouse x: " << Input.xoffset << " Mouse y: " << Input.yoffset << "\n\n\n\n";

        glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


        // Exit setting
        if (Input.keys[GLFW_KEY_ESCAPE]) break;



        // Set backglound color; Clear screen. Clear only screen color;
        glClearColor( backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);







        /* START RENDERING HERE */


        




        
        glPushMatrix();
          MoveCamera();
          ShowWorld();
        glPopMatrix();
        

        

        /*
        glPushMatrix();
          MoveCamera();
          glRotatef(-xAlpha, 1,0,0);
          glRotatef(-zAlpha, 0,0,1);
          glTranslatef(-cameraPosX,-cameraPosY,-cameraPosZ);
          glLineWidth(5);
          glBegin(GL_LINE_STRIP);
              // 1 - цвет точки, 2 - координаты точки 
              glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f( 0.0f, 1.0f );
              glColor3f( 0.0f, 1.0f, 0.0f ); glVertex2f( 1.0f, -0.5f );
              glColor3f( 0.0f, 0.0f, 1.0f ); glVertex2f( -1.0f, -0.5f );

              // Координаты в OPEN GL нормированы (от -1 до 1 по обоим осям)

          glEnd();
        glPopMatrix();
        */



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