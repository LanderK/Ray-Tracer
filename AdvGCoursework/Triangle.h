#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "object.h"

// The  triangle object class, extends Object class.
class Triangle : public Object {
	Vertex a,b,c;
public:
	Triangle(Vertex p1, Vertex p2, Vertex p3);
	bool intersect(Ray &ray, Hit *h);
};

#endif