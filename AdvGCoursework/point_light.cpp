#include <math.h>

#include "point_light.h"

// specified by a Position and a colour and optionally a Direction

PointLight::PointLight(Vertex &p,Vector &d, Colour &i)
{
	position.x = p.x;
	position.y = p.y;
	position.z = p.z;
	position.w = p.w;

	direction.x = -d.x;
	direction.y = -d.y;
	direction.z = -d.z;
	direction.normalise();

	intensity.set(i.getRed(), i.getGreen(), i.getBlue(), i.getAlpha());

	type = 1;
}

PointLight::PointLight(Vertex &p, Colour &i)
{
	position.x = p.x;
	position.y = p.y;
	position.z = p.z;
	position.w = p.w;

	intensity.set(i.getRed(), i.getGreen(), i.getBlue(), i.getAlpha());
}

// provide the intensity and direction from which light arrives at given vertex



void PointLight::getLightProperties(Vertex &pos, Vector *ldir, Colour *i)
{
	Vector LightToObject;
	LightToObject.set(pos.x - position.x, pos.y - position.y, pos.z - position.z);
	LightToObject.normalise();
	//Dirrection not set
	if (direction.norm() == 0) {

		ldir->x = LightToObject.x;
		ldir->y = LightToObject.y;
		ldir->z = LightToObject.z;
		ldir->normalise();

		// the intensity is always the same (not dependent on where it's going
		i->set(intensity.getRed(), intensity.getGreen(), intensity.getBlue(), intensity.getAlpha());
	
	}
	else {
		ldir->x = direction.x;
		ldir->y = direction.y;
		ldir->z = direction.z;

		double n = 200;
		double scale = pow(LightToObject.dot(direction),n);

		i->set(intensity.getRed() * scale, intensity.getGreen()*scale, intensity.getBlue()*scale, intensity.getAlpha());
	}
	
}

