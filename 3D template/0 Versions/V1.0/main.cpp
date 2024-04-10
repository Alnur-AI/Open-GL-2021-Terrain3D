#include <iostream>
#include <iomanip>
#include "Player.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>


int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

float xAngle = 3*90;
float yAngle = 0;
float zAngle = 0;

float cameraPosX = 0.0;
float cameraPosY = 0.0;
float cameraPosZ = 7.0;

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

// TIME
int FPS = 0;
GLdouble currentFrame  = 0.0f;
GLdouble deltaTime = 0.0f;
GLdouble lastFrame = 0.0f;

// PYRAMID
float pyramid[] = {0,0,2,  1,1,0,  1,-1,0, -1,-1,0,  -1,1,0,  1,1,0 };
float squareVert[] = {1,1,0,   1,-1,0,   -1,-1,0,   -1,1,0};


// OPENGL
void set3Dsettings()
{
    float param = float (SCREEN_WIDTH) / float (SCREEN_HEIGHT);
    glFrustum( -param, param, -1, 1, 2, 2000);
}


void drawSquare( float red, float green, float blue)
{
    glEnableClientState(GL_VERTEX_ARRAY);  
        glVertexPointer(3, GL_FLOAT, 0, &squareVert);
        glColor3f( red , green , blue);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 
    glDisableClientState(GL_VERTEX_ARRAY); 
}

void drawPyramid()
{
  glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &pyramid);
    glColor3f(1,0,0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void drawCube(){
  glEnableClientState(GL_VERTEX_ARRAY);
        // Желтая сторона — ПЕРЕДНЯЯ
        glBegin(GL_POLYGON);
          glColor3f(   1.0, 1.0, 0.0 );
          glVertex3f(  -0.5, 0.5, 0.5 );
          glVertex3f(  0.5, 0.5, 0.5 );
          glVertex3f(  0.5, 0.5, -0.5 );
          glVertex3f(  -0.5, 0.5, -0.5 );
        glEnd();

        // Белая сторона — ЗАДНЯЯ
        glBegin(GL_POLYGON);
          glColor3f(   1.0,  1.0, 1.0 );
          glVertex3f(  -0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, -0.5 );
          glVertex3f(  -0.5, -0.5, -0.5 );
        glEnd();

        // Фиолетовая сторона — ПРАВАЯ
        glBegin(GL_POLYGON);
          glColor3f(  1.0,  0.0,  1.0 );
          glVertex3f(  0.5, 0.5, 0.5 );
          glVertex3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, -0.5 );
          glVertex3f(  0.5, 0.5, -0.5 );
        glEnd();

        // Зеленая сторона — ЛЕВАЯ
        glBegin(GL_POLYGON);
          glColor3f(   0.0,  1.0,  0.0 );
          glVertex3f(  -0.5, 0.5, 0.5 );
          glVertex3f(  -0.5, -0.5, 0.5 );
          glVertex3f(  -0.5, -0.5, -0.5 );
          glVertex3f(  -0.5, 0.5, -0.5 );
        glEnd();

        // Синяя сторона — ВЕРХНЯЯ
        glBegin(GL_POLYGON);
          glColor3f(   0.0,  0.0,  1.0 );
          glVertex3f(  -0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5, 0.5, 0.5 );
          glVertex3f(  -0.5, 0.5, 0.5 );
        glEnd();

        // Красная сторона — НИЖНЯЯ
        glBegin(GL_POLYGON);
          glColor3f(   1.0,  0.0,  0.0 );
          glVertex3f(  -0.5, -0.5, -0.5 );
          glVertex3f(  0.5, -0.5,  -0.5 );
          glVertex3f( 0.5, 0.5,  -0.5 );
          glVertex3f( -0.5, 0.5, -0.5 );
        glEnd();
  glDisableClientState(GL_VERTEX_ARRAY);


}

void drawSphere(int sectors)
{
  int nTheta = sectors;
  int nPhi = sectors;
  float theta_i,theta_im1, phi_j, phi_jm1;
  float x,y,z;

  glEnableClientState(GL_VERTEX_ARRAY);
  for (int i = 1; i < nTheta; i++)
    for (int j = 1; j < nPhi; j++)
    {
      theta_i = M_PI*i/(nTheta-1);
      theta_im1 = M_PI*(i-1)/(nTheta-1);
      phi_j =  2*M_PI*j/(nTheta-1);
      phi_jm1 = 2*M_PI*(j-1)/(nTheta-1);

      glBegin(GL_POLYGON);
        glColor3f(   1.0, 0.0, 0.0 );
        x = sin(theta_im1)*cos(phi_jm1);
        y = sin(theta_im1)*sin(phi_jm1);
        z = cos(theta_im1);
        glVertex3f(  x, y, z );


        glColor3f(   1.0, 0.5, 0.0 );
        x = sin(theta_im1)*cos(phi_j);
        y = sin(theta_im1)*sin(phi_j);
        z = cos(theta_im1);
        glVertex3f(  x, y, z );


        glColor3f(   1.0, 1.0, 0.0 );
        x = sin(theta_i)*cos(phi_j);
        y = sin(theta_i)*sin(phi_j);
        z = cos(theta_i);
        glVertex3f(  x, y, z );


        glColor3f(   0.5, 1.0, 0.0 );
        x = sin(theta_i)*cos(phi_jm1);
        y = sin(theta_i)*sin(phi_jm1);
        z = cos(theta_i);
        glVertex3f(  x, y, z );
      glEnd();
    }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void drawWorld()
{
    for (int i = -32; i < 32; i++)
        for (int j = -32; j < 32; j++){
            glPushMatrix();
                glTranslatef(2*i,2*j,0);
                drawSquare(abs(i+j)%2, abs(i+j)%2, abs(i+j)%2);
            glPopMatrix();
        }
    
}

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
  

  glRotatef(xAngle, 1, 0, 0);
  glRotatef(yAngle, 0, 1, 0);
  glRotatef(zAngle, 0, 0, 1);
  glTranslatef( -cameraPosX, -cameraPosY, -cameraPosZ );
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


int main( void )
{
    GLFWwindow *window;
    
    // Initialize the library
    if ( !glfwInit( ) )
    {
        return -1;
    }
    
    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Game", NULL, NULL );
    
    if ( !window )
    {
        glfwTerminate( );
        return -1;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent( window );

    // Make the window's context current
    glfwMakeContextCurrent( window );


    
    glfwSetKeyCallback        (window, OnKeyboardPressed);
  	glfwSetCursorPosCallback  (window, OnMouseMove); 
    glfwSetMouseButtonCallback(window, OnMouseButtonClicked);
	  glfwSetScrollCallback     (window, OnMouseScroll);

    // 
    glEnable(GL_DEPTH_TEST);
    set3Dsettings();

    
    /* Loop until the user closes the window */
    while ( !glfwWindowShouldClose( window ) )
    {
        // Counting fps and deltaTime
        CountingFPS();

        // Debug information in console
        ShowDebugInfo();


        glClearColor( 0.0f, 0.5f, 0.9f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Render OpenGL here
        glPushMatrix();
            MoveCamera();
            drawWorld();

            /*
            glPushMatrix();
              glTranslatef(0,0,2);
              drawPyramid();
            glPopMatrix();

            glPushMatrix();
              glTranslatef(0,0,5);
              glScaled(2,2,2);
              drawCube();
            glPopMatrix();

            glPushMatrix();
              glTranslatef(0,0,1);
              glScaled(2,2,2);
              drawCube();
            glPopMatrix();
            */

            glPushMatrix();
              glTranslatef(0,6,5);
              //glScalef(1,1,1);
              drawSphere(10);
            glPopMatrix();
            

            
        glPopMatrix();
        
        // Swap front and back buffers
        glfwSwapBuffers( window );
        
        // Poll for and process events
        glfwPollEvents( );
    }
    
    glDisable(GL_DEPTH_TEST);
    glfwTerminate( );
    
    return 0;
}