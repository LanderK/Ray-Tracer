#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector.h"
#include "ray.h"

class Camera {
public:
	Vector Eye;
	Vector Look;
	Vector Up;
	Vector w;
	Vector u;
	Vector v;
	float sWidth;
	float sHeight;
	Camera(Vector &e,Vector &L,Vector &up, float sWidth, float sHeight);
	Ray generateRay(double x, double y);
};

#endif;