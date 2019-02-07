#include <math.h>

#include "scene.h"

Scene::Scene()
{
  scache = 0;
  obj_list = (Object *)0;
  light_list = (Light *)0;
}

void Scene::addObject(Object &obj)
{
	// add object to list of objects in scene
  obj.link(obj_list);
  obj_list = &obj;
}

void Scene::addLight(Light &lt)
{
	// add light to list of objects in scene
  lt.link(light_list);
  light_list = &lt;
}

Colour Scene::raytrace(Ray &ray, int level)
{
  float ta,t;
  Colour col;
  Object *obj;
  Object *closest;
  Light *lt;
  Hit   hit;
  Vertex position;
  Vector normal;


  if (level == 0)
  {
    col.clear();
    return col; // stop if recursed deep enough
  }

  // TEST EACH OBJECT AGAINST RAY, FIND THE CLOSEST

  t = 1000000000.0; // a long way aways
  closest = (Object *)0;
  obj = obj_list;

  while (obj != (Object *)0)
  {
    if(obj->intersect(ray, &hit) == true)
    {
      if (hit.t < t)
      {
	closest = hit.obj;
	t = hit.t;
	normal = hit.n;
	position = hit.p;
      }
    }

    obj = obj->next();
  }

  col.clear();

  if (closest != (Object *)0)
  {
    lt = light_list;

    Colour ocol;

    Colour ka = closest->obj_mat->ka;
    Colour kd = closest->obj_mat->kd;
    Colour ks = closest->obj_mat->ks;
    Colour kr = closest->obj_mat->kr;
    Colour kt = closest->obj_mat->kt;
	double n = closest->obj_mat->n;
	double c = closest->obj_mat->c;
    Ray sray;
	double small_e = 1e-2;

    while (lt != (Light *)0)
    {
      Vector ldir;
      Vector xldir;
      Colour lcol;

	  lt->getLightProperties(position, &xldir, &lcol);
	 
	  xldir.normalise();
      //Set Shadow Test Ray
	  sray.D.set(xldir.x, xldir.y, xldir.z);
	  sray.P.set(position.x + small_e*sray.D.x, position.y + small_e*sray.D.y, position.z + small_e*sray.D.z, 1.0);
	  double tmax = 1000000.0;
	  double vis = shadowtrace(sray,tmax);


      // calculate diffuse component

      float dlc = xldir.dot(normal);

      if (dlc < 0.0)
      {
	    dlc = 0.0;
      }

      // calculate specular component here

	  Vector R; //Refleced Ray Vector
	  float reflectScale = 2.0*xldir.dot(normal);
	  R.set(xldir.x - reflectScale*normal.x, xldir.y - reflectScale*normal.y, xldir.z - reflectScale*normal.z);
	  R.normalise();
	  float slc = pow(R.dot(ray.D),n);

      // combine components
	  float shadowScale;
	  if (vis == 0.0) {
		  shadowScale = 0.25;
	  } 
	  else {
		  shadowScale = vis;
	  }

      col.red += shadowScale*(ka.red) + vis*(lcol.red*(dlc * kd.red + slc * ks.red));
      col.green += shadowScale*(ka.green) + vis*(lcol.green*(dlc * kd.green + slc * ks.green));
      col.blue += shadowScale*(ka.blue) + vis*(lcol.blue*(dlc * kd.blue + slc * ks.blue));

      lt = lt->next(); // next light
    }

	Colour refCol;

   //REFLECTION
	if (kr.red + kr.green + kr.green > 0.0) {

		Ray rray; //Reflected Ray
		float reflectScale = 2.0*ray.D.dot(normal);
		rray.D.set(ray.D.x - reflectScale*normal.x, ray.D.y - reflectScale*normal.y, ray.D.z - reflectScale*normal.z);
		rray.D.normalise();
		rray.P.set(position.x + small_e * rray.D.x, position.y + small_e * rray.D.y, position.z + small_e * rray.D.z, 1.0);

		refCol = raytrace(rray, level - 1);

	}
	
	Colour refactCol;

    //REFRACION
	if (kt.red + kt.green + kt.green > 0.0){

		Ray tray;
		Vector I, Nrefract;
		Nrefract = normal;
		I.set(-ray.D.x, -ray.D.y, -ray.D.z);
		double c1 = 1;
		double cosThetai = Nrefract.dot(I);
		if (cosThetai < 0) {
			// Outside , Needs to be  Positive 
			cosThetai = -cosThetai;
		}
		else {
			//Inside Object , Reverse Normal and Swap speed of light indexs
			Nrefract.set(-normal.x, -normal.y, -normal.z);
			double temp = c1;
			c1 = c;
			c = temp;
		}
		double refIndex = c / c1;
		double k = 1 - (1 / (refIndex*refIndex))*(1 - (cosThetai*cosThetai));

		//Check for Total Internal Reflection, if not continue with computation
		if (k > 0) {

			double cosThetat = sqrt(k);

			tray.D.set((1 / refIndex)*(I.x) - (cosThetat - (1 / refIndex)*cosThetai)*Nrefract.x,
				(1 / refIndex)*(I.y) - (cosThetat - (1 / refIndex)*cosThetai)*Nrefract.y,
				(1 / refIndex)*(I.z) - (cosThetat - (1 / refIndex)*cosThetai)*Nrefract.z);
			tray.P.set(position.x + small_e * tray.D.x, position.y + small_e * tray.D.y, position.z + small_e * tray.D.z, 1.0);

			refactCol = raytrace(tray, level - 1);

			//Use Auguestin-Jean Fresnel for complex object 
	
			float rpar = (refIndex*cosThetai - cosThetat) / (refIndex*cosThetai + cosThetat);
			float rper = (cosThetai - refIndex*cosThetat) / (cosThetai + refIndex*cosThetat);

			kr.red = 0.5*(rpar*rpar + rper*rper);
			kr.green = 0.5*(rpar*rpar + rper*rper);
			kr.blue = 0.5*(rpar*rpar + rper*rper);

			kt.red = 1 - kr.red;
			kt.green = 1 - kr.green;
			kt.blue = 1 - kr.blue;
	
		}

		col.red += kt.red * refactCol.red + kr.red * refCol.red;
		col.green += kt.green * refactCol.green + kr.green * refCol.green;
		col.blue += kt.blue * refactCol.blue + kr.blue * refCol.blue;
	}
	

  }

  return col;
}


double Scene::shadowtrace(Ray &ray, double tlimit)
{
  Object *obj;
  Hit   hit;
  double trans = 1;

  // TEST EACH OBJECT AGAINST SRAY TO SEE IF IT CASTS A SHADOW

  obj = obj_list;

  while (obj != (Object *)0)
  {
	  if (obj->intersect(ray, &hit) == true)
	  {
		  if (hit.t > 0 && hit.t < tlimit)
		  {
			  if (hit.obj->obj_mat->kt.red + hit.obj->obj_mat->kt.blue + hit.obj->obj_mat->kt.red == 0.0) {
				  //Object is not transparent hence casting full shadow
				  return 0.0;
			  }
			  else {
				//Oject is transparent so doesn't cast full shadow, and continue looking for intersection of objects
				  trans *= hit.obj->obj_mat->kt.red;
			  }
		  }
	  }

	  obj = obj->next();
  }
 
  return trans;
}
