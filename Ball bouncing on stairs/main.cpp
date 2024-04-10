#include "Engine/Image/Image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <iomanip>  
#include "math.h"


const int SCREEN_WIDTH  = 1280;
const int SCREEN_HEIGHT = 720;

Pixel backgroundColor;


float floorVert[] = {1,1,0,  1,-1,0, -1,-1,0,  -1,1,0 };
float xAlpha = 90;
float zAlpha = 0;

float cameraPosX = 0.0;
float cameraPosY = -40.0;
float cameraPosZ = 3.0;


float sphereShiftX;
float sphereShiftY;
float sphereShiftZ = 20;
int sphereStateY = 1;
int sphereStateZ = 1;

float sphereMinZ=20;
float sphereMaxZ=35;

GLdouble deltaTime = 0.0f;
GLdouble lastFrame = 0.0f;




struct InputState
{
  bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
  GLfloat lastX = 400, lastY = 300; //исходное положение мыши
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

  Input.lastX = float(xpos);
  Input.lastY = float(ypos);
}

void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
  // ...
}


void drawCube(){
glEnableClientState(GL_VERTEX_ARRAY);
          // Белая сторона — ЗАДНЯЯ
          glBegin(GL_POLYGON);
          glColor3f(   1.0,  1.0, 1.0 );
          glVertex3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5,  0.5, 0.5 );
          glVertex3f( -0.5,  0.5, 0.5 );
          glVertex3f( -0.5, -0.5, 0.5 );
          glEnd();

          // Фиолетовая сторона — ПРАВАЯ
          glBegin(GL_POLYGON);
          glColor3f(  1.0,  0.0,  1.0 );
          glVertex3f( 0.5, -0.5, -0.5 );
          glVertex3f( 0.5,  0.5, -0.5 );
          glVertex3f( 0.5,  0.5,  0.5 );
          glVertex3f( 0.5, -0.5,  0.5 );
          glEnd();

          // Зеленая сторона — ЛЕВАЯ
          glBegin(GL_POLYGON);
          glColor3f(   0.0,  1.0,  0.0 );
          glVertex3f( -0.5, -0.5,  0.5 );
          glVertex3f( -0.5,  0.5,  0.5 );
          glVertex3f( -0.5,  0.5, -0.5 );
          glVertex3f( -0.5, -0.5, -0.5 );
          glEnd();

          // Синяя сторона — ВЕРХНЯЯ
          glBegin(GL_POLYGON);
          glColor3f(   0.0,  0.0,  1.0 );
          glVertex3f(  0.5,  0.5,  0.5 );
          glVertex3f(  0.5,  0.5, -0.5 );
          glVertex3f( -0.5,  0.5, -0.5 );
          glVertex3f( -0.5,  0.5,  0.5 );
          glEnd();

          // Красная сторона — НИЖНЯЯ
          glBegin(GL_POLYGON);
          glColor3f(   1.0,  0.0,  0.0 );
          glVertex3f(  0.5, -0.5, -0.5 );
          glVertex3f(  0.5, -0.5,  0.5 );
          glVertex3f( -0.5, -0.5,  0.5 );
          glVertex3f( -0.5, -0.5, -0.5 );
          glEnd();
          glDisableClientState(GL_VERTEX_ARRAY);


}

void drawSphere(float radius, float xs, float ys, float zs){

  //glPushMatrix();
  

  glColor3f(0.25, 0.87, 0.81);
    

    
          float xx,yy,zz;
          float X=-M_PI,Y=0;
          float Z=0;
          glBegin(GL_TRIANGLE_STRIP);
      
                    while(X<M_PI)
                    {
                      while(Y<2*M_PI)
                      {
                      xx=radius*cos(X)*cos(Y);
                      yy=radius*cos(X)*sin(Y);
                      zz=radius*sin(X);
                      glVertex3f(xx,yy,zz);
      
                      xx=radius*cos(X)*cos(Y);
                      yy=radius*cos(X+0.3)*sin(Y);
                      zz=radius*sin(X);
                      glVertex3f(xx,yy,zz);
      
                      xx=radius*cos(X+0.3)*cos(Y);
                      yy=radius*cos(X)*sin(Y);
                      zz=radius*sin(X+0.3);
                      glVertex3f(xx,yy,zz);
                      Y+=0.3;
                        }
                        Y=0;
                        X+=0.3;
                      }
          glEnd();


  glTranslatef(-xs,-ys,-zs);

  //glPopMatrix();
}

void ShowWorld()
{

    glEnableClientState(GL_VERTEX_ARRAY);

      

      float paramX = 1.0;
      float paramY = 1.0;
      float paramZ = float (SCREEN_WIDTH) / float (SCREEN_HEIGHT);

      //glScalef(paramY,paramY,paramZ);


      glVertexPointer(3, GL_FLOAT, 0, &floorVert);


      for(int i = -32; i < 32; i++)
        for (int j = -32; j < 32; j++)
        {
          glPushMatrix();

            if( (i+j)%2 == 0 ) glColor3f(0, 0.5, 0);
            else glColor3f(1, 1, 1);

            if( i == int(   round (cameraPosX )/2  ) && j == int(  round (cameraPosY)/2 ) )
              glColor3f(0.5, 0.0, 0);

            
            glTranslatef(i*2, j*2, 0);

            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


            
          glPopMatrix();
        }

      

    glDisableClientState(GL_VERTEX_ARRAY);


}

void MoveCamera()
{
  
  float angle = -zAlpha / 180 * M_PI;
  float speed = 0;
  float accelerate = 1.0;


  // MOVE ACCELERATION 
  if(Input.keys[GLFW_KEY_LEFT_SHIFT]) accelerate = 2.5;
  else accelerate = 1.0;


  // MOUSE
  if(Input.keys[GLFW_KEY_UP]) xAlpha += 0.78; xAlpha = xAlpha > 180 ? 180 : xAlpha;
  if(Input.keys[GLFW_KEY_DOWN]) xAlpha -= 0.78; xAlpha = xAlpha <   0 ?   0 : xAlpha;
  if(Input.keys[GLFW_KEY_LEFT]) zAlpha++;
  if(Input.keys[GLFW_KEY_RIGHT]) zAlpha--;

  
  // WALK
  if(Input.keys[GLFW_KEY_W]) speed = 0.1;
  if(Input.keys[GLFW_KEY_S]) speed = -0.1;
  if(Input.keys[GLFW_KEY_A]) {speed = 0.1; angle -= M_PI*0.5;}
  if(Input.keys[GLFW_KEY_D]) {speed = 0.1; angle += M_PI*0.5;}


  // SPECIAL WALK MODE
  if(Input.keys[GLFW_KEY_W] && Input.keys[GLFW_KEY_A]){ speed = +0.1;  angle += M_PI*0.5; zAlpha++; }
  if(Input.keys[GLFW_KEY_W] && Input.keys[GLFW_KEY_D]){ speed = +0.1;  angle -= M_PI*0.5; zAlpha--; }
  if(Input.keys[GLFW_KEY_S] && Input.keys[GLFW_KEY_A]){ speed = -0.05; angle += M_PI*0.5; zAlpha--; }
  if(Input.keys[GLFW_KEY_S] && Input.keys[GLFW_KEY_D]){ speed = -0.05; angle -= M_PI*0.5; zAlpha++; }


  // IF WE MOVED
  if(speed != 0)
  {
      cameraPosX += sin(angle)*speed*accelerate;
      cameraPosY += cos(angle)*speed*accelerate;
  }


  // HEIGHT CONTROL
  if(Input.keys[GLFW_KEY_SPACE]) cameraPosZ+=0.1;
  if(Input.keys[GLFW_KEY_LEFT_CONTROL]) cameraPosZ-=0.1;
  

  // MATRIX TRANSFORMATION
  glRotatef(-xAlpha, 1,0,0);
  glRotatef(-zAlpha, 0,0,1);
  glTranslatef(-cameraPosX+sphereShiftX,-cameraPosY+sphereShiftY,-cameraPosZ+sphereShiftZ);

}


int main( void )
{
    // Initialize the library
    if ( !glfwInit( ) )
    {
        return -1;
    }
    


    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window;
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
    glFrustum(-param,param,-1,1,2,200);






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

        std::cout <<  std::setprecision(3) << "x: " << (cameraPosX) << "\ny: " << (cameraPosY) << "\nz: " << (cameraPosZ) << "\n\nFPS:" << int (1.0/deltaTime) <<"\n\n\n\n";
        std::cout <<  std::setprecision(3) << "x: " << (sphereShiftX) << "\ny: " << (sphereShiftY) << "\nz: " << (sphereShiftZ) << "\n\nspherestate:" << sphereStateZ <<"\n\n\n\n";




        // Exit setting
        if (Input.keys[GLFW_KEY_ESCAPE]) break;



        // Set backglound color; Clear screen. Clear only screen color;
        glClearColor( backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);







        /* START RENDERING HERE */

        
        
        

        glPushMatrix();


          MoveCamera();

          drawSphere(10,0,sphereShiftY,sphereShiftZ);

          ShowWorld();
          
          glPushMatrix();
          glScaled(30,30,10);
          glTranslatef(0,0,0.5);
          drawCube();          

          glTranslatef(0,1,0.5);
          drawCube(); 
          glPopMatrix();

        glPopMatrix();




        if(sphereStateY == 1)
        sphereShiftY+=0.05;

        if(sphereShiftY >= 25){
          sphereStateY=0;
        }

        if(sphereStateY == 0)
          sphereShiftY-=0.05;
        
        if(sphereShiftY <= 0){
          sphereStateY=1;
        }


        if(sphereShiftY > 12){
          sphereMinZ=25;
          sphereMaxZ=40;
        }

        if(sphereShiftY < 12){
          sphereMinZ=20;
          sphereMaxZ=35;
        }




        if(sphereStateZ == 1)
        sphereShiftZ+=0.1;

        if(sphereShiftZ >= sphereMaxZ){
          sphereStateZ=0;
        }

        if(sphereStateZ == 0)
          sphereShiftZ-=0.1;
        
        if(sphereShiftZ <= sphereMinZ){
          sphereStateZ=1;
        }
        
        
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