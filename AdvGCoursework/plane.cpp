// Plane object

#include <math.h>

#include "plane.h"



Plane::Plane(double a, double b, double c, double dp)
{
	Normal.set(a,b,c); //To to confirm a^2+b^2+c^2 = 1
	d = dp;
}

Plane::Plane(Vector &N, double dp)
{
	Normal = N;
	d = dp;
}

// Plane intersection test

bool Plane::intersect(Ray &ray, Hit *hit)
{

	double ND = Normal.dot(ray.D);
	if (ND == 0.0) {
		return false;
	}

	double t0 = -(Normal.dot(ray.P) + d) / ND;

	hit->obj = this;

	hit->t = t0;

	hit->p.x = ray.P.x + t0 * ray.D.x;
	hit->p.y = ray.P.y + t0 * ray.D.y;
	hit->p.z = ray.P.z + t0 * ray.D.z;
	hit->p.w = 1.0;
	hit->n.x = Normal.x;
	hit->n.y = Normal.y;
	hit->n.z = Normal.z;
	hit->n.normalise();

	return true;
}
