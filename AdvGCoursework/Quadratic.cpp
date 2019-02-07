
#include <math.h>
#include "Quadratic.h"

Quadratic::Quadratic(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j) {

	A = a;
	B = b;
	C = c;
	D = d;
	E = e;
	F = f;
	G = g;
	H = h;
	I = i;
	J = j;

}

bool Quadratic::intersect(Ray &ray, Hit *hit) {
/*
Quadratic f(v) = v^TQv is eqivalent to f(v) = v.dot(Qv) 
hence if we sub in v = P + tD we get a quadratic equation At^2 +bt +c=0 
 */
	
	double t;
	double a = A*ray.D.x*ray.D.x + B *ray.D.y*ray.D.y + C *ray.D.z*ray.D.z + D*ray.D.x*ray.D.y + E*ray.D.x*ray.D.z + F*ray.D.y*ray.D.z;

	double b =	 2 * A*ray.P.x*ray.D.x + 2 * B*ray.P.y*ray.D.y + 2 * B*ray.P.z*ray.D.z
				+ D*(ray.P.x*ray.D.y + ray.P.y*ray.D.x) + E*(ray.P.x*ray.D.z + ray.P.z*ray.D.x) + F*(ray.P.y*ray.D.z + ray.D.y*ray.P.z) + G*ray.D.x + H*ray.D.y + I*ray.D.z;

	double c = A*ray.P.x*ray.P.x + B *ray.P.y*ray.P.y + C *ray.P.z*ray.P.z + D*ray.P.x*ray.P.y + E*ray.P.x*ray.P.z + F*ray.P.y*ray.P.z + G*ray.P.x + H*ray.P.y + I*ray.P.z + J;
		

	double diss = (b*b - 4*a*c);
	if (diss < 0.0) {
		return false;
	}

	if (a == 0) {
		t = -c / b;
	}
	else {

		double t0 = (-b - sqrt(diss)) / (2 * a);

		if (t0 > 0) {
			t = t0;
		}
		else {
			t = (-b + sqrt(diss)) / (2 * a);
		}

	}

	hit->obj = this;

	hit->t = t;

	hit->p.x = ray.P.x + t * ray.D.x;
	hit->p.y = ray.P.y + t * ray.D.y;
	hit->p.z = ray.P.z + t * ray.D.z;
	hit->p.w = 1.0;
	hit->n.x = 2 * A*hit->p.x + D*hit->p.y + E*hit->p.z + G;
	hit->n.y = 2 * B*hit->p.y + D*hit->p.x + F*hit->p.z + H;
	hit->n.z = 2 * C*hit->p.z + E*hit->p.x + F*hit->p.y + I;
	hit->n.normalise();

	return true;
	

}