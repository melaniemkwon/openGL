#ifndef POINT3_H
#define POINT3_H

// Point3 class 
class Point3{ 
public: 
	float x,y,z;
	void set(float dx, float dy, float dz){x = dx; y = dy; z = dz;}
	//void set(Point3& p){x = p.x; y = p.y; z = p.z;} 	
	void set(Point3 p){x = p.x; y = p.y; z = p.z;} 

    Point3(float xx,     float yy, float zz){x = xx; y = yy; z = zz;}
	Point3(){x = y = z = 0;}
	
	void build4tuple(float v[])
	{// load 4-tuple with this color: v[3] = 1 for homogeneous
		v[0] = x; v[1] = y; v[2] = z; v[3] = 1.0f;
	}	
};

#endif