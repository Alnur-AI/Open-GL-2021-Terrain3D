#include "main.h"




int main( void )
{
  if( !GameInit() ) return -1;
    
  glEnable(GL_DEPTH_TEST);

  set3Dsettings();

    /* Loop until the user closes the window */
    while ( !glfwWindowShouldClose( screen.window ) )
    {
      // Preparation
      CountingFPS();
      MoveCamera();
      ShowDebugInfo();
      ChangeScreenSize();

      // Prepare for rendering
      glClearColor( 0.0f, 0.5f, 0.9f, 0.0f );
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      // Render World
      renderWorld();

      // Render arms and weapon
      renderArms();

      // Draw Menu (If pressed)
      drawMenu();


      //float aspect =  (screen.width) / float (screen.height);
      //glFrustum(-aspect,aspect,-1/aspect,1/aspect,screen.minViewDist,screen.maxViewDist);

      // Render debug text
      //showDebugText();
      draw.Word(std::to_string( FPS ), screen, textureSymbol, 100, 100);
      draw.Word("CENTER", screen, textureSymbol, 0.5f, 0.0f);

      // Swap front and back buffers
      glfwSwapBuffers( screen.window );
          
      // Poll for and process events
      glfwPollEvents( );
    }
      
  glDisable(GL_DEPTH_TEST);

  glfwTerminate( );  
  return 0;
}