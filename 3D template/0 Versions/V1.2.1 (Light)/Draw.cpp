#include "Draw.h"

// Draw
//const std::vector<float>& color
void Draw::Square( const std::vector<float>& color )
{
    float red = color.at(0);
    float green = color.at(1);
    float blue = color.at(2);

  glEnableClientState(GL_VERTEX_ARRAY);  
  glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &squareVert);
    glNormalPointer(GL_FLOAT, 0, squareNormal);
    glColor3f( red , green , blue);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY); 
}
void Draw::Square( float red, float green, float blue)
{
  glEnableClientState(GL_VERTEX_ARRAY);  
  glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &squareVert);
    glNormalPointer(GL_FLOAT, 0, squareNormal);
    glColor3f( red , green , blue);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY); 
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
  glEnableClientState(GL_NORMAL_ARRAY);

  // Old with Index
  //glVertexPointer(3, GL_FLOAT, 0, &cubeVert);
  //glNormalPointer(GL_FLOAT, 0, &cubeNormal);
  //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &cubeInd);
  
        // Желтая сторона — ПЕРЕДНЯЯ
        glBegin(GL_POLYGON);
          //glColor3f(   1.0, 1.0, 0.0 );
          glNormal3f(0, 1, 0);
          glVertex3f(  -0.5, 0.5, 0.5 );
          glVertex3f(  0.5, 0.5, 0.5 );
          glVertex3f(  0.5, 0.5, -0.5 );
          glVertex3f(  -0.5, 0.5, -0.5 );
        glEnd();

        // Белая сторона — ЗАДНЯЯ
        glBegin(GL_POLYGON);
          //glColor3f(   1.0,  1.0, 1.0 );
          glNormal3f(0, -1, 0);
          glVertex3f(  -0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, -0.5 );
          glVertex3f(  -0.5, -0.5, -0.5 );
        glEnd();

        // Фиолетовая сторона — ПРАВАЯ
        glBegin(GL_POLYGON);
          //glColor3f(  1.0,  0.0,  1.0 );
          glNormal3f(1, 0, 0);
          glVertex3f(  0.5, 0.5, 0.5 );
          glVertex3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, -0.5 );
          glVertex3f(  0.5, 0.5, -0.5 );
        glEnd();

        // Зеленая сторона — ЛЕВАЯ
        glBegin(GL_POLYGON);
          //glColor3f(   0.0,  1.0,  0.0 );
          glNormal3f(-1, 0, 0);
          glVertex3f(  -0.5, 0.5, 0.5 );
          glVertex3f(  -0.5, -0.5, 0.5 );
          glVertex3f(  -0.5, -0.5, -0.5 );
          glVertex3f(  -0.5, 0.5, -0.5 );
        glEnd();

        // Синяя сторона — ВЕРХНЯЯ
        glBegin(GL_POLYGON);
          //glColor3f(   0.0,  0.0,  1.0 );
          glNormal3f(0, 0, 1);
          glVertex3f(  -0.5, -0.5, 0.5 );
          glVertex3f(  0.5, -0.5, 0.5 );
          glVertex3f(  0.5, 0.5, 0.5 );
          glVertex3f(  -0.5, 0.5, 0.5 );
        glEnd();

        // Красная сторона — НИЖНЯЯ
        glBegin(GL_POLYGON);
          //glColor3f(   1.0,  0.0,  0.0 );
          glNormal3f(0, 0, -1);
          glVertex3f(  -0.5, -0.5, -0.5 );
          glVertex3f(  0.5, -0.5,  -0.5 );
          glVertex3f( 0.5, 0.5,  -0.5 );
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
  int nTheta = sectors;
  int nPhi = sectors;
  float theta_i,theta_im1, phi_j, phi_jm1;
  float x1,y1,z1, 
        x2,y2,z2, 
        x3,y3,z3, 
        x4,y4,z4;
  float det1, det2, det3;

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
        x1 = sin(theta_im1)*cos(phi_jm1);
        y1 = sin(theta_im1)*sin(phi_jm1);
        z1 = cos(theta_im1);

        x2 = sin(theta_im1)*cos(phi_j);
        y2 = sin(theta_im1)*sin(phi_j);
        z2 = cos(theta_im1);

        x3 = sin(theta_i)*cos(phi_j);
        y3 = sin(theta_i)*sin(phi_j);
        z3 = cos(theta_i);

        x4 = sin(theta_i)*cos(phi_jm1);
        y4 = sin(theta_i)*sin(phi_jm1);
        z4 = cos(theta_i);

        det1 = (y2-y1)*(z3-z1)-(z2-z1)*(y3-y1);
        det2 = (z2-z1)*(x3-x1)-(x2-x1)*(z3-z1);
        det3 = (x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);
        glNormal3f(-det1, -det2, -det3);
        glVertex3f( x1, y1, z1 );       
        glVertex3f( x2, y2, z2 );  
        glVertex3f( x3, y3, z3 );
        glVertex3f( x4, y4, z4 );

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

void Draw::ChessBoard()
{
    for (int i = -4; i < 4; i++)
        for (int j = -4; j < 4; j++){
            glPushMatrix();
                glTranslatef(2*i,2*j,0);
                Square(abs(i+j)%2, abs(i+j)%2, abs(i+j)%2);
            glPopMatrix();
        }
    
}

