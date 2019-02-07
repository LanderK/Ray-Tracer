#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "vertex.h"

class Vector {
 public:
  double x;
  double y;
  double z;
  double w = 1.0; //for homogeneous coordinates eg. Quadratric Surfaces
  Vector(void);
  void set(double x, double y, double z);
  void set(double x, double y, double z, double w);
  void resetHomo(void);
  void normalise(void);
  double norm(void);
  double dot(const Vector &b);
  double dot(const Vertex &b);
  double homoDot(const Vector &b);
  double homoDot(const Vertex &b);
  Vector cross(const Vector &b);
  void scale(double s);
};


#endif
