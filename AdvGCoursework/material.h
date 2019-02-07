#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "colour.h"

class Material {
 public:
  Colour ka; // ambient
  Colour kd; // diffuse
  Colour ks; // specular
  Colour kr; // reflection
  Colour kt; // refraction
  double n;  // phong power term
  double c; // speed of light in object
};

#endif
