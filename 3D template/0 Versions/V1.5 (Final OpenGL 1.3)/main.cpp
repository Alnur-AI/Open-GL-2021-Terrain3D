#include "main.h"




int main( void )
{
  if( !GameInit() ) return -1;
    
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);

  glEnable(GL_BLEND);
  glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  set3Dsettings();

  
  for (int i = 0; i < 256; i++)
    std::cout << draw.charWidthArray[i] << std::endl;
    

  /* Loop until the user closes the window */
  while ( !glfwWindowShouldClose( screen.window ) )
  {
    // Preparation
    CountingFPS();
    MoveCamera();
    //ShowDebugInfo();
    ChangeScreenSize();

    // Prepare for rendering
    glClearColor( 0.0f, 0.5f, 0.9f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // render 3D world
      glMatrixMode(GL_MODELVIEW); 
      // draw World
      renderWorld();
      // Render arms and weapon
      renderArms();

      // render 2D world
      glMatrixMode(GL_PROJECTION);
      // Draw Menu (If pressed)
      drawMenu();
      // Render debug text
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      std::vector<float> textColor = {0,0,1,1};
      draw.Word( "ABCDEFGHIJKLMNOPQRSTUVWXYZ", screen, textureSymbol, -0.9f, 0.0f, textColor);
      draw.Word( "FPS: " + std::to_string( player.time.averFPS ), screen, textureSymbol, 0.45f, 0.9f, textColor);
      draw.Word( "x: "   + std::to_string( int(player.getCameraX()) ), screen, textureSymbol, 0.65f, 0.8f, textColor);
      draw.Word( "y: "   + std::to_string( int(player.getCameraY())  ), screen, textureSymbol, 0.65f, 0.7f, textColor);
      draw.Word( "z: "   + std::to_string( int(player.getCameraZ())  ), screen, textureSymbol, 0.65f, 0.6f, textColor);

      draw.Word( "Rx: "   + std::to_string( int(player.getRotateX()) ), screen, textureSymbol, 0.05f, 0.8f, textColor);
      draw.Word( "Ry: "   + std::to_string( int(player.getRotateY())  ), screen, textureSymbol, 0.05f, 0.7f, textColor);
      draw.Word( "Rz: "   + std::to_string( int(player.getRotateZ())  ), screen, textureSymbol, 0.05f, 0.6f, textColor);

      draw.Word( "CENTER", screen, textureSymbol, 200, 200, textColor);
      glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    // Swap front and back buffers
    glfwSwapBuffers( screen.window );
          
    // Poll for and process events
    glfwPollEvents( );
  }
  glDisable(GL_BLEND);

  glDisable(GL_NORMALIZE);
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);

  glfwTerminate( );  
  return 0;
}