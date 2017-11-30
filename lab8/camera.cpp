//Camera Class
#ifdef _WIN32
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#elif __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/Gl.h>
#include <GLUT/GLUT.h>
#include <unistd.h>
#endif

#include "camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera :: setModelViewMatrix(void)
{ // load modelview matrix with existing camera values
	float m[16];
	Vector3 eVec(eye.x, eye.y, eye.z); // a vector version of eye 
	m[0] =  u.x; m[4] =  u.y; m[8]  =  u.z;  m[12] = -eVec.dot(u);
	m[1] =  v.x; m[5] =  v.y; m[9]  =  v.z;  m[13] = -eVec.dot(v);
	m[2] =  n.x; m[6] =  n.y; m[10] =  n.z;  m[14] = -eVec.dot(n);
	m[3] =  0;   m[7] =  0;   m[11] =  0;    m[15] = 1.0;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m); // load OpenGL’s modelview matrix
}
void Camera:: set(Point3 Eye, Point3 look, Vector3 up)
{	// create a modelview matrix and send it to OpenGL
	eye.set(Eye); // store the given eye position

    n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z); // make n
	
	u.set(up.cross(n)); // make u = up X n
	
	n.normalize(); 
	u.normalize(); // make them unit length
	
	v.set(n.cross(u));  // make v =  n X u
	
	setModelViewMatrix(); // tell OpenGL 
}

void Camera :: slide(float delU, float delV, float delN )
{
	eye.x += delU*u.x + delV*v.x + delN*n.x;
	eye.y += delU*u.y + delV*v.y + delN*n.y;
	eye.z += delU*u.z + delV*v.z + delN*n.z;

	setModelViewMatrix(); // tell OpenGL 
}

void Camera :: roll(float angle)
{ // roll the camera through angle degrees. rotate it about its own n-axis.
	float cs = (float) cos(3.14159265/180 * angle);
	float sn = (float) sin(3.14159265/180 * angle);
	Vector3 t(u); // remember old u
    // u' = cos(angle)u + sin(angle)v
	u.set(cs*t.x + sn*v.x, cs*t.y + sn*v.y, cs*t.z + sn*v.z);
    // v' = -sin(angle)u + cos(angle)v
	v.set(-sn*t.x + cs*v.x, -sn*t.y + cs*v.y, -sn*t.z + cs*v.z);

	setModelViewMatrix();
}

//Add methods for pitch and yaw
void Camera::yaw(float angle)
{ // yaw the camera through angle degrees. rotate it about its own v-axis
    float cs = (float) cos(3.14159265/180 * angle);
    float sn = (float) sin(3.14159265/180 * angle);
    
    Vector3 t(n); // remember old n
    // n' = cos(angle)n + sin(angle)u
    n.set(cs*t.x + sn*u.x, cs*t.y + sn*u.y, cs*t.z + sn*u.z);
    // u' = -sin(angle)n + cos(angle)u
    u.set(-sn*t.x + cs*u.x, -sn*t.y + cs*u.y, -sn*t.z + cs*u.z);
    
    setModelViewMatrix();
}

void Camera::pitch(float angle)
{ // pitch the camera through angle degrees. rotate it about its own u-axis
    float cs = (float) cos(3.14159265/180 * angle);
    float sn = (float) sin(3.14159265/180 * angle);
    
    Vector3 t(v); // remember old v
    // v' = cos(angle)v + sin(angle)n
    v.set(cs*t.x + sn*n.x, cs*t.y + sn*n.y, cs*t.z + sn*n.z);
    // n' = -sin(angle)v + cos(angle)n
    n.set(-sn*t.x + cs*n.x, -sn*t.y + cs*n.y, -sn*t.z + cs*n.z);
    
    setModelViewMatrix();
}

void Camera::rotate(float &angle) {
    eye.x = 25 * cos(angle);
    eye.z = 25 * sin(angle);
    angle += 2 * 3.14159265 / 1000;
}

void Camera::translate(float angle) {
    
}

void setShape(float vAng, float asp, float nearD, float farD)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(vAng, asp, nearD, farD);
}
