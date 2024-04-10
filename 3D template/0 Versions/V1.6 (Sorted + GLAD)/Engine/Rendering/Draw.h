#ifndef DRAW_H
#define DRAW_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "Screen.h"




class Draw
{
    public:// DRAWING OBJECTS
    void ChessBoard(unsigned int texture, float alpha);

    void Square( const std::vector<float>& color );
    void Square( float red, float green, float blue, float alpha);
    void Square( unsigned int texture, float alpha);

    void Pyramid();
    void Pyramid(const std::vector<float>& position, const std::vector<float>& angle, const std::vector<float>& color, const std::vector<float>& size);
    
    void Cube();
    void Cube(const std::vector<float>& position, const std::vector<float>& angle, const std::vector<float>& color, const std::vector<float>& size);
    
    void Sphere(int sectors);
    void Sphere(int sectors, const std::vector<float>& position, const std::vector<float>& angle, const std::vector<float>& color, const std::vector<float>& size);
    void Sphere(int sectors, unsigned int texture, float alpha);
    void Sphere(int sectors, unsigned int texture, const std::vector<float>& position, const std::vector<float>& angle, const std::vector<float>& color, const std::vector<float>& size);
    
    public:// WORK WITH TEXT
    float *charWidthArray;
    void Word(std::string text, Screen screen, unsigned int textureSymbol, int x, int y,const std::vector<float>& color);
    void Word(std::string text, Screen screen, unsigned int textureSymbol, float xNorm, float yNorm,const std::vector<float>& color);
    


    private:
    // pyramid
    float pyramidNormal[15]= { 0,0,2/3.0f,   1,1,-1/3.0f, 1,-1,-1/3.0f, -1,-1,-1/3.0f, -1,1,-1/3.0f };
    float pyramidVert[15]  = { 0,0,1,  1,  1  ,0,  1,-1,0,   -1,-1,0,  -1,1,0 };
    uint  pyramidInd[18]   = { 0,3,2,  0,  1  ,2,  0, 4,1,    0, 3,4,  1,2,3,   1,4,3 };
    float pyramidColor[15] = { 1,0,0,  1, 0.5, 0,  1, 1,0,  0.5, 1,0,  0,1,0};

    // square
    float squareVert[12] = {1,1,0,   1,-1,0,   -1,-1,0,   -1,1,0};
    float squareNorm[12] = {1,1,3,   1,-1,3,   -1,-1,3,   -1,1,3};

};





#endif //DRAW_H