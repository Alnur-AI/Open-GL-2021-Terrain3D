#include "main.h"




int main( void )
{
  if( !GameInit() ) return -1;
    
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);

    set3Dsettings();

    /* Loop until the user closes the window */
    while ( !glfwWindowShouldClose( window ) )
    {
      // Preparation
      CountingFPS();
      MoveCamera();
      ShowDebugInfo();
      ChangeScreenSize();

      // Prepare for rendering
      glClearColor( 0.0f, 0.5f, 0.9f, 0.0f );
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Render OpenGL here
      renderWorld();

      // Render arms and weapon
      renderArms();

      // Render debug text
      showDebugText();

      // Swap front and back buffers
      glfwSwapBuffers( window );
          
      // Poll for and process events
      glfwPollEvents( );
    }


  glDisable(GL_NORMALIZE);
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  

  glDisable(GL_DEPTH_TEST);

  glfwTerminate( );  
  return 0;
}