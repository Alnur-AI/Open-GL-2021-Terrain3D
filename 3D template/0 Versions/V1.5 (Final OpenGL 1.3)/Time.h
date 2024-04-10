#ifndef TIME_H
#define TIME_H

#define FPScount 120

class Time
{
public:
    int FPS[FPScount];
    int indFPS = 0;
    int averFPS;
    double currentFrame  = 0.0f;
    double deltaTime = 0.0f;
    double lastFrame = 0.0f;
};

#endif //TIME_H
