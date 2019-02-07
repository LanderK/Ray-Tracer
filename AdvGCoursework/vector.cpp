#include <math.h>

#include "vector.h"

Vector::Vector()
{
  x = 0.0;
  y = 0.0;
  z = 0.0;
}

void Vector::set(double px, double py, double pz)
{
  x = px;
  y = py;
  z = pz;
}

void Vector::set(double px, double py, double pz,double pw)
{
	x = px;
	y = py;
	z = pz;
	w = pw;
}

void Vector::normalise(void)
{
  double l;

  // get the length of the vector
  l = x*x+y*y+z*z;
  l = sqrt(l);

  // divide elements by length to transform vector to unit length
  x = x/l;
  y = y/l;
  z = z/l;
}

double Vector::norm(void)
{
	double l;

	// get the length of the vector
	l = x*x + y*y + z*z;
	return l;
}

// compute the dot product of the vector.
double Vector::dot(const Vector &b)
{
  return (x*b.x)+(y*b.y)+(z*b.z);
}

double Vector::dot(const Vertex &b)
{
	return (x*b.x) + (y*b.y) + (z*b.z);
}

double Vector::homoDot(const Vector &b)
{
	return (x*b.x) + (y*b.y) + (z*b.z) + (w*b.w);
}

double Vector::homoDot(const Vertex &b)
{
	return (x*b.x) + (y*b.y) + (z*b.z) + (w*b.w);
}

Vector Vector::cross(const Vector &b) {

	Vector crossP;
	crossP.set(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
	return crossP;
}

void Vector::scale(const double s) {

	

}

void Vector::resetHomo() {

	x = x / w;
	y = y / w;
	z = z / w;
	w = w / w;

}