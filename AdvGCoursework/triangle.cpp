// Triangle object

#include <math.h>

#include "triangle.h"
#include "plane.h"

// Sphere defined as vertex (in world space) and radius

Triangle::Triangle(Vertex p1, Vertex p2, Vertex p3)
{
	a = p1;
	b = p2;
	c = p3;
}

// Sphere intersection test

bool Triangle::intersect(Ray &ray, Hit *hit)
{
	Vector ca, ba;
	ca.set(c.x - a.x, c.y - a.y, c.z - a.z); 
	ba.set(b.x - a.x, b.y - a.y, b.z - a.z);
	Vector triNormal = ca.cross(ba);
	triNormal.normalise();
	double D = triNormal.dot(a);
	Plane Triplane(triNormal, D);

	//check intersection with plane
	if (Triplane.intersect(ray, hit) == false) {
		return false;
	}

	//Check if within Triangle
	Vector v1,ap1,C;

	v1.set(b.x - a.x, b.y - a.y, b.z - a.z);
	ap1.set(hit->p.x - a.x, hit->p.y - a.y, hit->p.z - a.z);

	C = ap1.cross(v1);
	if (triNormal.dot(C) < 0) return false;

	Vector v2, ap2;
	v2.set(c.x - b.x, c.y - b.y, c.z - b.z);
	ap2.set(hit->p.x - b.x, hit->p.y - b.y, hit->p.z - b.z);

	C = ap2.cross(v2);
	if (triNormal.dot(C) < 0) return false;

	Vector v3, ap3;
	v3.set(a.x - c.x, a.y - c.y, a.z - c.z);
	ap3.set(hit->p.x - c.x, hit->p.y - c.y, hit->p.z - c.z);

	C = ap3.cross(v3);
	if (triNormal.dot(C) < 0) return false;
	
	hit->obj = this;
	return true;
}