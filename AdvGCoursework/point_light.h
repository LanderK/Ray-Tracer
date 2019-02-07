#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "light.h"

class PointLight : public Light {
	Vertex position;
	Vector direction;
	Colour intensity;
public:
	PointLight(Vertex &p,Vector &d, Colour &c);
	PointLight(Vertex &p,Colour &c);
	virtual void getLightProperties(Vertex &pos, Vector *ldir, Colour *i);
};

#endif