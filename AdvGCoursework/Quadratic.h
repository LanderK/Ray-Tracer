#ifndef _QUADRATIC_H_
#define _QUADRATIC_H_

#include "object.h"
class Quadratic : public Object {
	double A, B, C, D, E, F, G, H, I, J;
		//M[4][4];
public:
	Quadratic(double a, double b, double c, double d, double e, double f, double g,double h,double i, double j);
	bool intersect(Ray &ray, Hit *h);
};

#endif
