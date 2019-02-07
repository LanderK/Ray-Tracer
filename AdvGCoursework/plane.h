#ifndef _PLANE_H_
#define _PLANE_H_

#include "object.h"

// The Plane object class, extends Object class.
//ax +by+cz+d =0
class Plane : public Object {
	Vector Normal; //[a,b,c]
	double d;
public:
	Plane(double a, double b, double c, double d);
	Plane(Vector &N, double d);
	bool intersect(Ray &ray, Hit *h);
};

#endif