#include "Draw.h"


// Draw
//const std::vector<float>& color
void Draw::Square( const std::vector<float>& color )
{
  glNormal3f(0,0,1);
    float red = color.at(0);
    float green = color.at(1);
    float blue = color.at(2);
    float alpha = color.at(3);

    glEnableClientState(GL_VERTEX_ARRAY);  
    glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, &squareVert);
        glNormalPointer(GL_FLOAT, 0, squareNorm);
        glColor4f( red , green , blue, alpha);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 
        
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY); 
}
void Draw::Square( float red, float green, float blue, float alpha)
{
  glNormal3f(0,0,1);
    glEnableClientState(GL_VERTEX_ARRAY);  
    glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, &squareVert);
        glNormalPointer(GL_FLOAT, 0, squareNorm);
        glColor4f( red , green , blue, alpha);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 
             
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY); 
}
void Draw::Square( unsigned int texture , float alpha)
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  float texCoord[] = {0,1,  1,1,  1,0,  0,0};
    glEnableClientState(GL_VERTEX_ARRAY); 
    glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
    glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, &squareVert);
        glNormalPointer(GL_FLOAT, 0, squareNorm);
        glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
        glColor4f( 1 , 1 , 1, alpha);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY); 
    glDisable(GL_TEXTURE_2D);
}


void Draw::Pyramid()
{
    glVertexPointer( 3, GL_FLOAT, 0, &pyramidVert );
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);


    glNormalPointer(GL_FLOAT, 0, pyramidNormal);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, &pyramidInd);

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
void Draw::Pyramid(const std::vector<float>& position, const std::vector<float>& angle, const std::vector<float>& color, const std::vector<float>& size)
{
    float x = position.at(0);
    float y = position.at(1);
    float z = position.at(2);

    float xAngle = angle.at(0);
    float yAngle = angle.at(1);
    float zAngle = angle.at(2);

    float r = color.at(0);
    float g = color.at(1);
    float b = color.at(2);
    float a = color.at(3);

    float Sx = size.at(0);
    float Sy = size.at(1);
    float Sz = size.at(2);

    glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(Sx,Sy,Sz);
        glRotatef(xAngle, 1, 0, 0);
        glRotatef(yAngle, 0, 1, 0);
        glRotatef(zAngle, 0, 0, 1);
        glColor4f(r,g,b,a);
        Pyramid();
    glPopMatrix();
}

void Draw::Cube(){
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

        // Желтая сторона — ПЕРЕДНЯЯ
        glBegin(GL_POLYGON);
          
          glNormal3f(  -0.5, 0.5, 0.5 );
          glVertex3f(  -0.5, 0.5, 0.5 );

          glNormal3f(  0.5, 0.5, 0.5 );
          glVertex3f(  0.5, 0.5, 0.5 );
          
          glNormal3f(  0.5, 0.5, -0.5 );
          glVertex3f(  0.5, 0.5, -0.5 );
          
          glNormal3f(  -0.5, 0.5, -0.5 );
          glVertex3f(  -0.5, 0.5, -0.5 );
        glEnd();

        // Белая сторона — ЗАДНЯЯ
        glBegin(GL_POLYGON);
          
          glNormal3f(  -0.5, -0.5, 0.5 );
          glVertex3f(  -0.5, -0.5, 0.5 );

          glNormal3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, 0.5 );

          glNormal3f(  0.5, -0.5, -0.5 );
          glVertex3f(  0.5, -0.5, -0.5 );

          glNormal3f(  -0.5, -0.5, -0.5 );
          glVertex3f(  -0.5, -0.5, -0.5 );
        glEnd();

        // Фиолетовая сторона — ПРАВАЯ
        glBegin(GL_POLYGON);

          glNormal3f(  0.5, 0.5, 0.5 );
          glVertex3f(  0.5, 0.5, 0.5 );

          glNormal3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, 0.5 );

          glNormal3f(  0.5, -0.5, -0.5 );
          glVertex3f(  0.5, -0.5, -0.5 );

          glNormal3f(  0.5, 0.5, -0.5 );
          glVertex3f(  0.5, 0.5, -0.5 );
        glEnd();

        // Зеленая сторона — ЛЕВАЯ
        glBegin(GL_POLYGON);

          glNormal3f(  -0.5, 0.5, 0.5 );
          glVertex3f(  -0.5, 0.5, 0.5 );

          glNormal3f(  -0.5, -0.5, 0.5 );
          glVertex3f(  -0.5, -0.5, 0.5 );

          glNormal3f(  -0.5, -0.5, -0.5 );
          glVertex3f(  -0.5, -0.5, -0.5 );
          
          glNormal3f(  -0.5, 0.5, -0.5 );
          glVertex3f(  -0.5, 0.5, -0.5 );
        glEnd();

        // Синяя сторона — ВЕРХНЯЯ
        glBegin(GL_POLYGON);

          glNormal3f(  -0.5, -0.5, 0.5 );
          glVertex3f(  -0.5, -0.5, 0.5 );

          glNormal3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, 0.5 );

          glNormal3f(  0.5, 0.5, 0.5 );
          glVertex3f(  0.5, 0.5, 0.5 );

          glNormal3f(  -0.5, 0.5, 0.5 );
          glVertex3f(  -0.5, 0.5, 0.5 );
        glEnd();

        // Красная сторона — НИЖНЯЯ
        glBegin(GL_POLYGON);

          glNormal3f(  -0.5, -0.5, -0.5 );
          glVertex3f(  -0.5, -0.5, -0.5 );
          
          glNormal3f(  0.5, -0.5,  -0.5 );
          glVertex3f(  0.5, -0.5,  -0.5 );
          
          glNormal3f( 0.5, 0.5,  -0.5 );
          glVertex3f( 0.5, 0.5,  -0.5 );

          glNormal3f( -0.5, 0.5, -0.5 );
          glVertex3f( -0.5, 0.5, -0.5 );
        glEnd();

  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);


}
void Draw::Cube(const std::vector<float>& position, const std::vector<float>& angle, const std::vector<float>& color, const std::vector<float>& size)
{
    float x = position.at(0);
    float y = position.at(1);
    float z = position.at(2);

    float xAngle = angle.at(0);
    float yAngle = angle.at(1);
    float zAngle = angle.at(2);

    float r = color.at(0);
    float g = color.at(1);
    float b = color.at(2);
    float a = color.at(3);

    float Sx = size.at(0);
    float Sy = size.at(1);
    float Sz = size.at(2);

    glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(Sx,Sy,Sz);
        glRotatef(xAngle, 1, 0, 0);
        glRotatef(yAngle, 0, 1, 0);
        glRotatef(zAngle, 0, 0, 1);
        glColor4f(r,g,b,a);
        Cube();
    glPopMatrix();
}

void Draw::Sphere(int sectors)
{
  int nTheta = sectors+1;
  int nPhi = sectors+1;
  float theta_i,theta_im1, phi_j, phi_jm1;
  float x1,y1,z1;
  float x2,y2,z2;
  float x3,y3,z3;
  float x4,y4,z4;

  glEnableClientState(GL_VERTEX_ARRAY);
  for (int i = 1; i < nTheta; i++)
    for (int j = 1; j < nPhi; j++)
    {
      theta_i = M_PI*i/(nTheta-1);
      theta_im1 = M_PI*(i-1)/(nTheta-1);
      phi_j =  2*M_PI*j/(nTheta-1);
      phi_jm1 = 2*M_PI*(j-1)/(nTheta-1);

      // Left Up
      x1 = sin(theta_im1)*cos(phi_jm1);
      y1 = sin(theta_im1)*sin(phi_jm1);
      z1 = cos(theta_im1);
        
      // Right Up
      x2 = sin(theta_im1)*cos(phi_j);
      y2 = sin(theta_im1)*sin(phi_j);
      z2 = cos(theta_im1);
        
      // Right Down
      x3 = sin(theta_i)*cos(phi_j);
      y3 = sin(theta_i)*sin(phi_j);
      z3 = cos(theta_i);
       
      // Left Down
      x4 = sin(theta_i)*cos(phi_jm1);
      y4 = sin(theta_i)*sin(phi_jm1);
      z4 = cos(theta_i);

      glBegin(GL_POLYGON);
        glColor3f(   1.0, 0.0, 0.0 );
        glNormal3f(x1, y1, z1);
        glVertex3f(  x1, y1, z1 );


        glColor3f(   1.0, 0.5, 0.0 );
        glNormal3f(x2, y2, z2);
        glVertex3f(  x2, y2, z2 );


        glColor3f(   1.0, 1.0, 0.0 );
        glNormal3f(x3, y3, z3);
        glVertex3f(  x3, y3, z3 );


        glColor3f(   0.5, 1.0, 0.0 );
        glNormal3f(x4, y4, z4);
        glVertex3f(  x4, y4, z4 );
      glEnd();
    }
  glDisableClientState(GL_VERTEX_ARRAY);
}
void Draw::Sphere(int sectors, const std::vector<float>& position, const std::vector<float>& angle, const std::vector<float>& color, const std::vector<float>& size)
{
    float x = position.at(0);
    float y = position.at(1);
    float z = position.at(2);

    float xAngle = angle.at(0);
    float yAngle = angle.at(1);
    float zAngle = angle.at(2);

    float r = color.at(0);
    float g = color.at(1);
    float b = color.at(2);
    float a = color.at(3);

    float Sx = size.at(0);
    float Sy = size.at(1);
    float Sz = size.at(2);

    glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(Sx,Sy,Sz);
        glRotatef(xAngle, 1, 0, 0);
        glRotatef(yAngle, 0, 1, 0);
        glRotatef(zAngle, 0, 0, 1);
        glColor4f(r,g,b,a);
        Sphere(sectors);
    glPopMatrix();
}
void Draw::Sphere(int sectors, unsigned int texture, float alpha)
{
  int nTheta = sectors+1;
  int nPhi = sectors+1;

  float theta_i, theta_im1, phi_j, phi_jm1;
  float tex_i, tex_j, tex_im1, tex_jm1;
  float x1,y1,z1;
  float x2,y2,z2;
  float x3,y3,z3;
  float x4,y4,z4;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
  glEnableClientState(GL_NORMAL_ARRAY);
  for (int i = 1; i < nTheta; i++)
    for (int j = 1; j < nPhi; j++)
    {
      theta_i = M_PI*i/(nTheta-1);
      theta_im1 = M_PI*(i-1)/(nTheta-1);
      phi_j =  2*M_PI*j/(nTheta-1);
      phi_jm1 = 2*M_PI*(j-1)/(nTheta-1);

      tex_i = i/float(nTheta-1);
      tex_j = j/float(nPhi-1);
      tex_im1 = (i-1)/float(nTheta-1);
      tex_jm1 = (j-1)/float(nPhi-1);

      // Left Up
      x1 = sin(theta_im1)*cos(phi_jm1);
      y1 = sin(theta_im1)*sin(phi_jm1);
      z1 = cos(theta_im1);
        
      // Right Up
      x2 = sin(theta_im1)*cos(phi_j);
      y2 = sin(theta_im1)*sin(phi_j);
      z2 = cos(theta_im1);
        
      // Right Down
      x3 = sin(theta_i)*cos(phi_j);
      y3 = sin(theta_i)*sin(phi_j);
      z3 = cos(theta_i);
       
      // Left Down
      x4 = sin(theta_i)*cos(phi_jm1);
      y4 = sin(theta_i)*sin(phi_jm1);
      z4 = cos(theta_i);

      glBegin(GL_POLYGON);
        glColor4f( 1.0, 1.0, 1.0, alpha );

        // Left Up
        glNormal3f(x1, y1, z1);
        glTexCoord2f(tex_jm1, tex_im1); //glTexCoord2f(0, 0);
        glVertex3f(  x1, y1, z1 );

        // Right Up
        glNormal3f(x2, y2, z2);
        glTexCoord2f(tex_j, tex_im1); //glTexCoord2f(1, 0);
        glVertex3f(  x2, y2, z2 );

        // Right Down
        glNormal3f(x3, y3, z3);
        glTexCoord2f(tex_j, tex_i); //glTexCoord2f(1, 1);
        glVertex3f(  x3, y3, z3 );

        // Left Down
        glNormal3f(x4, y4, z4);
        glTexCoord2f(tex_jm1, tex_i); //glTexCoord2f(0, 1);
        glVertex3f(  x4, y4, z4 );
      glEnd(); 
    }
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
  glDisableClientState(GL_VERTEX_ARRAY);

  glDisable(GL_TEXTURE_2D);
}
void Draw::Sphere(int sectors, unsigned int texture, const std::vector<float>& position, const std::vector<float>& angle, const std::vector<float>& color, const std::vector<float>& size)
{
    float x = position.at(0);
    float y = position.at(1);
    float z = position.at(2);

    float xAngle = angle.at(0);
    float yAngle = angle.at(1);
    float zAngle = angle.at(2);

    float r = color.at(0);
    float g = color.at(1);
    float b = color.at(2);
    float a = color.at(3);

    float Sx = size.at(0);
    float Sy = size.at(1);
    float Sz = size.at(2);

    glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(Sx,Sy,Sz);
        glRotatef(xAngle, 1, 0, 0);
        glRotatef(yAngle, 0, 1, 0);
        glRotatef(zAngle, 0, 0, 1);
        glColor4f(r,g,b,a);
        Sphere(sectors, texture, a);
    glPopMatrix();
}

void Draw::ChessBoard(unsigned int texture, float alpha)
{
    for (int i = -4; i < 4; i++)
        for (int j = -4; j < 4; j++){
            glPushMatrix();
                glTranslatef(2*i,2*j,0);
                Square(texture, alpha);
                //Square(abs(i+j)%2, abs(i+j)%2, abs(i+j)%2);
            glPopMatrix();
        }
    
}


void Draw::Word(std::string text, Screen screen, unsigned int textureSymbol, int xPixel, int yPixel, const std::vector<float>& color)
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);


  glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, textureSymbol);
      glPushMatrix();

        glLoadIdentity();
        float xf = -1  + (2*xPixel)/(float)screen.width;
        float yf = -1  + (2*yPixel)/(float)screen.height;
        float param =  (screen.width) / float (screen.height);
        glTranslatef(xf,yf,0);
        //glTranslatef(,-1,0);
        glScalef(0.05/param,0.05,0.05);
        glColor4f(color.at(0),color.at(1),color.at(2),color.at(3));

        //float squareVert[12] = {1,1,0,   1,-1,0,   -1,-1,0,   -1,1,0};
        float recCoord[] = {-1,-1,0,  1,-1,0,  1,1,0,  -1,1,0};
        float texCoord[] = {0,1,  1,1,  1,0,  0,0};

        glEnableClientState(GL_VERTEX_ARRAY);  
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, recCoord);
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

        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY); 


      glPopMatrix();
  glDisable(GL_TEXTURE_2D);


  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST); 
  
}
void Draw::Word(std::string text, Screen screen, unsigned int textureSymbol, float xNorm, float yNorm, const std::vector<float>& color)
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);


  glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, textureSymbol);
      glPushMatrix();

        glLoadIdentity();
        float param =  (screen.width) / float (screen.height);
        glTranslatef(xNorm,yNorm,0);
        //glTranslatef(,-1,0);
        glScalef(0.05/param,0.05,0.05);
        glColor4f(color.at(0),color.at(1),color.at(2),color.at(3));

        //float squareVert[12] = {1,1,0,   1,-1,0,   -1,-1,0,   -1,1,0};
        float recCoord[] = {-1,-1,0,  1,-1,0,  1,1,0,  -1,1,0};
        float texCoord[] = {0,1,  1,1,  1,0,  0,0};

        glEnableClientState(GL_VERTEX_ARRAY);  
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, recCoord);
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

        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY); 


      glPopMatrix();
  glDisable(GL_TEXTURE_2D);


  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST); 
}

