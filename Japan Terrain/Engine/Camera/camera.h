#ifndef CAMERA_H
#define CAMERA_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>




struct SCamera
{
	float x,y,z;
	float Xrot, Zrot;
};

void Camera_Apply();
void Camera_Rotation(float xAngle, float zAngle);

#endif //CAMERA_H
