#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

// Vector3 
class Vector3{ 
public: 
	float x,y,z;
	void set(float dx, float dy, float dz){ x = dx; y = dy; z = dz;} 
	//void set(Vector3& v){ x = v.x; y = v.y; z = v.z;}
	void set(Vector3 v){ x = v.x; y = v.y; z = v.z;}
	void flip(){x = -x; y = -y; z = -z;} // reverse this vector
	void setDiff(Point3& a, Point3& b)//set to difference a - b
	{ x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;}
	void normalize()//adjust this vector to unit length
	{		
		double sizeSq = x * x + y * y + z * z;
		if(sizeSq < 0.0000001)
		{
			//cerr << "\nnormalize() sees vector (0,0,0)!";
			return; // does nothing to zero vectors;
		}
		float scaleFactor = 1.0/(float)sqrt(sizeSq);
		x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;
	}
	Vector3(float xx, float yy, float zz){x = xx; y = yy; z = zz;}
	Vector3(const Vector3& v){x = v.x; y = v.y; z = v.z;}
	Vector3(){x = y = z = 0;} //default constructor
	Vector3 cross(Vector3 b) //return this cross b
	{
	   Vector3 c(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
	   return c;
	}
	float dot(Vector3 b) // return this dotted with b
 {return x * b.x + y * b.y + z * b.z;}
};

#endif