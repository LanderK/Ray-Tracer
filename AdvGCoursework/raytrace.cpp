#include <iostream>
#include <fstream>
using namespace std;

#include "scene.h"
#include "sphere.h"
#include "Triangle.h"
#include "plane.h"
#include "quadratic.h"
#include "directional_light.h"
#include "point_light.h"
#include "camera.h"

#define XSIZE 512
#define YSIZE 512

Colour frame_buffer[YSIZE][XSIZE];

float frand()
{
  int x;
  float f;

  x = rand();
  f = (float)(x & 0xffff);
  f = f/65536.0f;

  return f;
}

void write_framebuffer()
{
  int x, y;
  float r, g, b;

  ofstream fout;

  fout.open("testSS3.ppm", ofstream::binary);

  fout << "P6" << std::endl << XSIZE << std::endl << YSIZE << std::endl << "255" << std::endl;

  for(y=YSIZE-1;y>=0;y-=1)
  {
    for(x=0;x<XSIZE;x+=1)
    {
      r = 255.0f * frame_buffer[y][x].getRed();
      g = 255.0f * frame_buffer[y][x].getGreen();
      b = 255.0f * frame_buffer[y][x].getBlue();
      if (r > 255.0) r = 255.0;
      if (g > 255.0) g = 255.0;
      if (b > 255.0) b = 255.0;
	  fout << (unsigned char)r << (unsigned char)g << (unsigned char)b;
    }
  }

  fout.close();
}

void clear_framebuffer()
{
  int x,y;

  for(y=0;y<YSIZE;y+=1)
  {
    for(x=0;x<XSIZE;x+=1)
    {
      frame_buffer[y][x].clear();
    }
  }
}

// The main raytacing entry point.

int main(int argc, const char *argv[])
{
  Scene *scene;
  Vector v;
  int x,y;
  int n;
  DirectionalLight *dl;
  PointLight *pl;
  Colour cl;
  Vertex pp;
  float ca, cr, cg,cb;

  cout << "Starting ...\n";

  srand(3115);

  clear_framebuffer();

  // SETUP SCENE

  // Create a new scene to render
  scene = new Scene();

  // Create and add a directional light to the scene
  v.set(-1.0,-1.0,1.0);
  cl.set(1.0,1.0,1.0,1.0);
  pp.set(50.0, 50.0, -48.25, 1.0);
  
  dl = new DirectionalLight(v, cl);
  pl = new PointLight(pp, v, cl);

  scene->addLight(*pl);

  // Add 10 random spheres to the scene
  
  for (n = 0; n < 10; n += 1)
  {
    Sphere *s;
    Material *m;
    Vertex p;

    // position
    p.set(frand()-0.5,frand()-0.5,frand()+1.0,1.0);

    // create with random radius
    s = new Sphere(p, frand()/2.0f);

    // create new material with shared random Ka and Kd
    m = new Material();

    cr = frand(); cg = frand(); cb = frand(); ca = frand();

    m->ka.red = cr * 0.1f;
    m->ka.green = cg * 0.1f;
    m->ka.blue = cb * 0.1f;
    m->kd.red = cr * 0.5f;
    m->kd.green = cg * 0.5f;
    m->kd.blue = cb * 0.5f;
    m->kr.red =  0.0f;
    m->kr.green = 0.0f;
    m->kr.blue = 0.0f;
    m->ks.red = 0.5f;
    m->ks.green =  0.5f;
    m->ks.blue = 0.5;
    m->kt.red = 0.0;
    m->kt.green = 0.0;
    m->kt.blue = 0.0;
    m->n = 400.0;

    // set spheres material
    s->setMaterial(m);

    // as sphere to scene
    scene->addObject(*s);
  }
  

  Triangle *t1,*t2;
  Material *m;
  Vertex p1,p2,p3,p4;

  // Vertices for triangle
  p1.set(10.0, 1.0, -10.0, 1.0);
  p2.set(10.0, 1.0, 10.0, 1.0);
  p3.set(-10.0, 1.0, -10.0, 1.0);
  p4.set(-10.0, 1.0, 10.0, 1.0);

  // Create new Triangle
  t1 = new Triangle(p1,p2,p3);
  t2 = new Triangle(p2,p3,p4);

  // create new material with shared random Ka and Kd
  m = new Material();

  m->ka.red = 0.1f;
  m->ka.green = 0.1f;
  m->ka.blue = 0.1f;
  m->kd.red =  0.5f;
  m->kd.green = 0.5f;
  m->kd.blue = 0.5f;
  m->kr.red = 0.0f;
  m->kr.green = 0.0f;
  m->kr.blue = 0.0f;
  m->ks.red = 0.0f;
  m->ks.green = 0.0f;
  m->ks.blue = 0.0;
  m->kt.red = 0.0;
  m->kt.green = 0.0;
  m->kt.blue = 0.0;
  m->n = 400.0;

  // set Triangles material
  t1->setMaterial(m);
  t2->setMaterial(m);

  // add triangle to scene
  scene->addObject(*t1);
  scene->addObject(*t2);

  Quadratic *q;

  // Create new Quadratic Shpere 
  q = new Quadratic(1.0,1.0,1.0,0.0,0.0,0.0,-0.25,0.0,0.0,-0.01);

  // create new material with shared random Ka and Kd
  m = new Material();
  cr = frand(); cg = frand(); cb = frand(); ca = frand();

  m->ka.red = cr * 0.1f;
  m->ka.green = cg * 0.1f;
  m->ka.blue = cb * 0.1f;
  m->kd.red = cr * 0.5f;
  m->kd.green = cg * 0.5f;
  m->kd.blue = cb * 0.5f;
  m->kr.red = 0.1f;
  m->kr.green = 0.1f;
  m->kr.blue = 0.1f;
  m->ks.red = 0.5f;
  m->ks.green = 0.5f;
  m->ks.blue = 0.5;
  m->kt.red = 0.75;
  m->kt.green = 0.75;
  m->kt.blue = 0.75;
  m->n = 400.0;
  m->c = 0.95;

  // set quadratic material
  q->setMaterial(m);

  // add quadratic to scene
  scene->addObject(*q);

  Vector Eye;
  Eye.set(0, 0, -1.0);
  Vector Look;
  Look.set(0.0, 0.0, -2.0);
  Vector Up;
  Up.set(0.0, 1.0, 0.0);

   Camera viewPoint(Eye, Look, Up, XSIZE, YSIZE);
  // RAYTRACE SCENE

  cout << "Raytracing ...\n";

  int samples=4; // can only be square number
  double sampleWidth = 1 / sqrt(samples);
  double samplestart = 1 / (sqrt(samples) * 2);

  for(y=0;y<YSIZE;y+=1)
  {
	  
    for(x=0;x<XSIZE;x+=1)
    {
		for (int i = 0; i < sqrt(samples) ; i++) {
			for (int j = 0; j < sqrt(samples); j++) {

				double samplex, sampley;

				//set samplepoints to unifom locations
				samplex = (x - 0.5 + samplestart) + i*sampleWidth;
				sampley = (y - 0.5 + samplestart) + j*sampleWidth;

				//Add Jitter
				double randx, randy;
				randx = (rand() % 201) / 100 - 1; //Random number between -1 to 1
				randy = (rand() % 201) / 100 - 1;
				samplex += randx*samplestart;
				sampley += randy*samplestart;

				//Generate Ray
				Ray ray = viewPoint.generateRay(samplex, sampley);

				// Trace primary ray
				Colour col = scene->raytrace(ray, 4);

				// Save result in frame buffer
				frame_buffer[y][x].red += col.red;
				frame_buffer[y][x].green += col.green;
				frame_buffer[y][x].blue += col.blue;
			}
		}

		frame_buffer[y][x].red /= samples;
		frame_buffer[y][x].green /= samples;
		frame_buffer[y][x].blue /= samples;
	
    }
  }

  // OUTPUT IMAGE
 
  cout << "Outputing ...\n";

  write_framebuffer();

  cout << "Done.\n";
}
