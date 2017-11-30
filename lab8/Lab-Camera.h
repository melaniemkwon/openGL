#ifndef LAB_CAMERA_H
#define LAB_CAMERA_H

#include "camera.h"
#include "mesh.h"

#include <vector>

//Global Variables
const int screenWidth = 700;	   // width of screen window in pixels
const int screenHeight = 700;	   // height of screen window in pixels
const float worldWidth = 100.0;
const float worldHeight = 100.0; 

Camera cam; // global camera object
bool cameraAnimation = false;
int cameraAnimFrame = 0;
float cameraAngle = 0;

// Point class.
class Point
{
public:
    Point(int x, int y)
    {
        xVal = x; yVal = y;
    }
    Point(){};
    void setCoords(int x, int y)
    {
        xVal = x; yVal = y;
    }
    
    int xVal, yVal; // x and y co-ordinates of point.
};

int displayMode = 0;
//Point3 base[3];
std::vector<Point3> base(10);
auto it = base.begin();
int NoOfPts=0;
Mesh triPrism;

bool objectScaleMode = false;
bool objectRotateMode = false;
int objectRotateModeIndex = 0;

float objectScale = 1;
float objectRotateX = 0;
float objectRotateY = 0;
float objectRotateZ = 0;

// define some colors
//GLfloat amb0[] = {0.2, 0.4, 0.6, 1.0};
//GLfloat diff0[] = {0.8, 0.9, 0.5, 1.0};
//GLfloat spec0[] = {1.0, 0.8, 1.0, 1.0};
//
//GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
//GLfloat shininess[] = {50.0f};

// place the light
GLfloat litePos[] = {0, 0, 0, 1.0f};
GLfloat model_ambient[] = {0.4f, 0.4f, 0.4f, 1.0f};

#endif
