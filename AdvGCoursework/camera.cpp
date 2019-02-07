// a simple directional light source

#include <math.h>
#include "camera.h"


Camera::Camera(Vector &e, Vector &l, Vector &up,float Width, float Height)
{
	Eye = e;
	Look = l;
	Up = up;

	sWidth = Width;
	sHeight = Height;

	//Make Orthonormal Basis

	w.x = Eye.x - Look.x;
	w.y = Eye.y - Look.y;
	w.z = Eye.z - Look.z;
	w.normalise();

	u = Up.cross(w);
	u.normalise();

	v = w.cross(u);
}



Ray Camera::generateRay(double x, double y)
{
	Ray newRay;

	newRay.P.set(Eye.x, Eye.y, Eye.z,1.0);

	double normx = (x / sWidth) -0.5;
	double normy = (y / sHeight) -0.5;
	
	newRay.D.set(normx*u.x + normy*v.x + w.x, normx*u.y + normy*v.y + w.y, normx*u.z + normy*v.z + w.z);
	newRay.D.normalise();

	return newRay;
}