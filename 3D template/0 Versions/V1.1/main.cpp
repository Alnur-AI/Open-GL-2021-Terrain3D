#include "main.h"




int main( void )
{
  if( !GameInit() ) return -1;
    
  glEnable(GL_DEPTH_TEST);

    set3Dsettings();

    /* Loop until the user closes the window */
    while ( !glfwWindowShouldClose( window ) )
    {
      // Preparation
      CountingFPS();
      MoveCamera();
      ShowDebugInfo();

      // Prepare for rendering
      glClearColor( 0.0f, 0.5f, 0.9f, 0.0f );
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Render OpenGL here
      renderWorld();
          
      // Swap front and back buffers
      glfwSwapBuffers( window );
          
      // Poll for and process events
      glfwPollEvents( );
    }
      
    glDisable(GL_DEPTH_TEST);
    glfwTerminate( );
    
    return 0;
}