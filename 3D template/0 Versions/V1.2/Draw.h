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
    float pyramidVert[15]  = { 0,0,1,  1,  1  ,0,  1,-1,0,   -1,-1,0,  -1,1,0 };
    uint  pyramidInd[18]   = { 0,3,2,  0,  1  ,2,  0, 4,1,    0, 3,4,  1,2,3,   1,4,3 };
    float pyramidColor[15] = { 1,0,0,  1, 0.5, 0,  1, 1,0,  0.5, 1,0,  0,1,0};

    float squareVert[12] = {1,1,0,   1,-1,0,   -1,-1,0,   -1,1,0};
};





#endif //DRAW_H