#ifndef DRAW_H
#define DRAW_H

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>


class Draw
{
    public:
    void ChessBoard();

    void Square( const std::vector<float>& color );
    void Square( float red, float green, float blue );

    void Pyramid();
    void Pyramid(const std::vector<float>& position, const std::vector<float>& angle, const std::vector<float>& color, const std::vector<float>& size);
    
    void Cube();
    void Cube(const std::vector<float>& position, const std::vector<float>& angle, const std::vector<float>& color, const std::vector<float>& size);
    
    void Sphere(int sectors);
    void Sphere(int sectors, const std::vector<float>& position, const std::vector<float>& angle, const std::vector<float>& color, const std::vector<float>& size);
    
    


    private:
    float pyramidVert[15]  = { 0,0,1,   1,  1  ,0,   1,-1,0,    -1,-1,0,   -1,1,0 };
    uint  pyramidInd[18]   = { 0,3,2,   0,  1  ,2,   0, 4,1,     0, 3,4,    1,2,3,   1,4,3 };
    float pyramidColor[15] = { 1,0,0,   1, 0.5, 0,   1, 1,0,   0.5, 1,0,    0,1,0};

    float squareNormal[12] = {1,1,3,   1,-1,3,   -1,-1,3,   -1,1,3};
    float squareVert[12]   = {1,1,0,   1,-1,0,   -1,-1,0,   -1,1,0};


    //float cubeVert[24]   = {-0.5, -0.5, -0.5,   0.5, -0.5, -0.5,   0.5, 0.5, -0.5,   -0.5, 0.5, -0.5, 
    //                         -0.5, -0.5, 0.5,    0.5, -0.5, 0.5,    0.5, 0.5, 0.5,    -0.5, 0.5, 0.5 };
    //uint  cubeInd[36]    = { 2,3,7,   2,6,7,  0,1,5,  0,4,5,  1,2,6,  1,5,6,  0,3,7,  0,4,7,  4,5,6,  4,7,6,  0,1,2,  0,3,2  };
    //float cubeNormal[36] = { 0,1,0,  0,1,0,  0,-1,0,  0,-1,0, 1,0,0,  1,0,0, -1,0,0, -1,0,0,  0,0,1,  0,0,1,  0,0,-1, 0,0,-1};
    //float cubeNormal[24] = { -1,-1,-1,  -1,1,1,  -1,-1,1,  1,-1,1,  1,1,-1,  1,-1,1,  1,1,1,  -1,1,1 }; 

};





#endif //DRAW_H