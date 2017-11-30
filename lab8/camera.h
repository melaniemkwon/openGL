#ifndef CAMERA_H
#define CAMERA_H

#include "Point3.h"
#include "Vector3.h"

class Camera {
  private:
	Point3 eye;
	Vector3 u,v,n;
	double viewAngle, aspect, nearDist, farDist; // view volume shape
	void setModelViewMatrix(); // tell OpenGL where the camera is	

  public:
	Camera(); // default constructor
	~Camera();
	void set(Point3 eye, Point3 look, Vector3 up); // like gluLookAt()	
    void slide(float delU, float delV, float delN); // slide it	
	void roll(float angle); // roll it

	void pitch(float angle); // increase pitch
	void yaw(float angle); // yaw it
    
    void rotate(float &angle);
    void translate(float angle);
    
    void setShape(float vAng, float asp, float nearD, float farD);
};

#endif
