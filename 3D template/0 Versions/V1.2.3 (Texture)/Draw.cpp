#include "Draw.h"


// Draw
//const std::vector<float>& color
void Draw::Square( const std::vector<float>& color )
{
    float red = color.at(0);
    float green = color.at(1);
    float blue = color.at(2);

    glEnableClientState(GL_VERTEX_ARRAY);  
        glVertexPointer(3, GL_FLOAT, 0, &squareVert);
        glColor3f( red , green , blue);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 
    glDisableClientState(GL_VERTEX_ARRAY); 
}
void Draw::Square( float red, float green, float blue)
{
    glEnableClientState(GL_VERTEX_ARRAY);  
        glVertexPointer(3, GL_FLOAT, 0, &squareVert);
        glColor3f( red , green , blue);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 
    glDisableClientState(GL_VERTEX_ARRAY); 
}
void Draw::Square( unsigned int texture )
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  float texCoord[] = {0,1,  1,1,  1,0,  0,0};

    glEnableClientState(GL_VERTEX_ARRAY); 
    glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
        glVertexPointer(3, GL_FLOAT, 0, &squareVert);
        glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
        glColor3f( 1 , 1 , 1);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY); 
    glDisable(GL_TEXTURE_2D);
}
void Draw::SquareDelete( unsigned int texture )
{
  glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, texture);
      glPushMatrix();

        glLoadIdentity();
        glScalef(0.5,0.5,0.5);
        glColor3f(1,1,1);

        //float squareVert[12] = {1,1,0,   1,-1,0,   -1,-1,0,   -1,1,0};
        float recCoord[] = {-1,-1,0,  1,-1,0,  1,1,0,  -1,1,0};
        float texCoord[] = {0,1,  1,1,  1,0,  0,0};

        glEnableClientState(GL_VERTEX_ARRAY);  
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, recCoord);
        glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 

        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY); 


      glPopMatrix();
  glDisable(GL_TEXTURE_2D);
} 

void Draw::Pyramid()
{
    glVertexPointer( 3, GL_FLOAT, 0, &pyramidVert );
    glEnableClientState(GL_VERTEX_ARRAY);

    //glColorPointer( 3, GL_FLOAT, 0, &pyramidColor);
    //glEnableClientState(GL_COLOR_ARRAY);

    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, &pyramidInd);

    //glDisableClientState(GL_COLOR_ARRAY);
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

    float Sx = size.at(0);
    float Sy = size.at(1);
    float Sz = size.at(2);

    glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(Sx,Sy,Sz);
        glRotatef(xAngle, 1, 0, 0);
        glRotatef(yAngle, 0, 1, 0);
        glRotatef(zAngle, 0, 0, 1);
        glColor3f(r,g,b);
        Pyramid();
    glPopMatrix();
}

void Draw::Cube(){
  glEnableClientState(GL_VERTEX_ARRAY);
        // Желтая сторона — ПЕРЕДНЯЯ
        glBegin(GL_POLYGON);
          //glColor3f(   1.0, 1.0, 0.0 );
          glVertex3f(  -0.5, 0.5, 0.5 );
          glVertex3f(  0.5, 0.5, 0.5 );
          glVertex3f(  0.5, 0.5, -0.5 );
          glVertex3f(  -0.5, 0.5, -0.5 );
        glEnd();

        // Белая сторона — ЗАДНЯЯ
        glBegin(GL_POLYGON);
          //glColor3f(   1.0,  1.0, 1.0 );
          glVertex3f(  -0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, -0.5 );
          glVertex3f(  -0.5, -0.5, -0.5 );
        glEnd();

        // Фиолетовая сторона — ПРАВАЯ
        glBegin(GL_POLYGON);
          //glColor3f(  1.0,  0.0,  1.0 );
          glVertex3f(  0.5, 0.5, 0.5 );
          glVertex3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, -0.5 );
          glVertex3f(  0.5, 0.5, -0.5 );
        glEnd();

        // Зеленая сторона — ЛЕВАЯ
        glBegin(GL_POLYGON);
          //glColor3f(   0.0,  1.0,  0.0 );
          glVertex3f(  -0.5, 0.5, 0.5 );
          glVertex3f(  -0.5, -0.5, 0.5 );
          glVertex3f(  -0.5, -0.5, -0.5 );
          glVertex3f(  -0.5, 0.5, -0.5 );
        glEnd();

        // Синяя сторона — ВЕРХНЯЯ
        glBegin(GL_POLYGON);
          //glColor3f(   0.0,  0.0,  1.0 );
          glVertex3f(  -0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5, 0.5, 0.5 );
          glVertex3f(  -0.5, 0.5, 0.5 );
        glEnd();

        // Красная сторона — НИЖНЯЯ
        glBegin(GL_POLYGON);
          //glColor3f(   1.0,  0.0,  0.0 );
          glVertex3f(  -0.5, -0.5, -0.5 );
          glVertex3f(  0.5, -0.5,  -0.5 );
          glVertex3f( 0.5, 0.5,  -0.5 );
          glVertex3f( -0.5, 0.5, -0.5 );
        glEnd();
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

    float Sx = size.at(0);
    float Sy = size.at(1);
    float Sz = size.at(2);

    glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(Sx,Sy,Sz);
        glRotatef(xAngle, 1, 0, 0);
        glRotatef(yAngle, 0, 1, 0);
        glRotatef(zAngle, 0, 0, 1);
        glColor3f(r,g,b);
        Cube();
    glPopMatrix();
}

void Draw::Sphere(int sectors)
{
  int nTheta = sectors+1;
  int nPhi = sectors+1;
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
        //glColor3f(   1.0, 0.0, 0.0 );
        x = sin(theta_im1)*cos(phi_jm1);
        y = sin(theta_im1)*sin(phi_jm1);
        z = cos(theta_im1);
        glVertex3f(  x, y, z );


        //glColor3f(   1.0, 0.5, 0.0 );
        x = sin(theta_im1)*cos(phi_j);
        y = sin(theta_im1)*sin(phi_j);
        z = cos(theta_im1);
        glVertex3f(  x, y, z );


        //glColor3f(   1.0, 1.0, 0.0 );
        x = sin(theta_i)*cos(phi_j);
        y = sin(theta_i)*sin(phi_j);
        z = cos(theta_i);
        glVertex3f(  x, y, z );


        //glColor3f(   0.5, 1.0, 0.0 );
        x = sin(theta_i)*cos(phi_jm1);
        y = sin(theta_i)*sin(phi_jm1);
        z = cos(theta_i);
        glVertex3f(  x, y, z );
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

    float Sx = size.at(0);
    float Sy = size.at(1);
    float Sz = size.at(2);

    glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(Sx,Sy,Sz);
        glRotatef(xAngle, 1, 0, 0);
        glRotatef(yAngle, 0, 1, 0);
        glRotatef(zAngle, 0, 0, 1);
        glColor3f(r,g,b);
        Sphere(sectors);
    glPopMatrix();
}
void Draw::Sphere(int sectors, unsigned int texture)
{
  int nTheta = sectors+1;
  int nPhi = sectors+1;

  float theta_i, theta_im1, phi_j, phi_jm1;
  float tex_i, tex_j, tex_im1, tex_jm1;
  float x,y,z;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
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

      glBegin(GL_POLYGON);
        glColor3f( 1.0, 1.0, 1.0 );

        // Left Up
        x = sin(theta_im1)*cos(phi_jm1);
        y = sin(theta_im1)*sin(phi_jm1);
        z = cos(theta_im1);
        glTexCoord2f(tex_jm1, tex_im1); //glTexCoord2f(0, 0);
        glVertex3f(  x, y, z );

        // Right Up
        x = sin(theta_im1)*cos(phi_j);
        y = sin(theta_im1)*sin(phi_j);
        z = cos(theta_im1);
        glTexCoord2f(tex_j, tex_im1); //glTexCoord2f(1, 0);
        glVertex3f(  x, y, z );

        // Right Down
        x = sin(theta_i)*cos(phi_j);
        y = sin(theta_i)*sin(phi_j);
        z = cos(theta_i);
        glTexCoord2f(tex_j, tex_i); //glTexCoord2f(1, 1);
        glVertex3f(  x, y, z );

        // Left Down
        x = sin(theta_i)*cos(phi_jm1);
        y = sin(theta_i)*sin(phi_jm1);
        z = cos(theta_i);
        glTexCoord2f(tex_jm1, tex_i); //glTexCoord2f(0, 1);
        glVertex3f(  x, y, z );
      glEnd();
      
    }
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

    float Sx = size.at(0);
    float Sy = size.at(1);
    float Sz = size.at(2);

    glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(Sx,Sy,Sz);
        glRotatef(xAngle, 1, 0, 0);
        glRotatef(yAngle, 0, 1, 0);
        glRotatef(zAngle, 0, 0, 1);
        glColor3f(r,g,b);
        Sphere(sectors, texture);
    glPopMatrix();
}

void Draw::ChessBoard(unsigned int texture)
{
    for (int i = -4; i < 4; i++)
        for (int j = -4; j < 4; j++){
            glPushMatrix();
                glTranslatef(2*i,2*j,0);
                Square(texture);
                //Square(abs(i+j)%2, abs(i+j)%2, abs(i+j)%2);
            glPopMatrix();
        }
    
}


void Draw::Word(std::string text, Screen screen, unsigned int textureSymbol, int xPixel, int yPixel)
{
  glDisable(GL_DEPTH_TEST);

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
        glColor3f(1,1,1);

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
  glEnable(GL_DEPTH_TEST); 
}
void Draw::Word(std::string text, Screen screen, unsigned int textureSymbol, float xNorm, float yNorm)
{
  glDisable(GL_DEPTH_TEST);

  //glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();

  glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, textureSymbol);
      glPushMatrix();

        glLoadIdentity();
        float param =  (screen.width) / float (screen.height);
        glTranslatef(xNorm,yNorm,0);
        //glTranslatef(,-1,0);
        glScalef(0.05/param,0.05,0.05);
        glColor3f(1,1,1);

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

  //float aspect =  (screen.width) / float (screen.height);
  //
  //glMatrixMode(GL_PROJECTION);
  //glLoadIdentity();
  //float aspect =  (screen.width) / float (screen.height);
  //glFrustum(-aspect,aspect,-1/aspect,1/aspect,2,500);

  glEnable(GL_DEPTH_TEST); 
}


