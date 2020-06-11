#include "objects.h"

//===HH SCENERY OBJECTS===
class OrbHolder : public TObject
{
  using TObject::TObject;
private:
  //objects; work on a linked list implementation?
  Sphere base = Sphere(0,0,0, .8,.8,.8, -.5,-.5,.5, .3,.3,.3);
  Cuboid claw1 = Cuboid(20,270,0, .25,1.5,.25, -.125,0,0, .1,.1,.1);
  Cuboid claw2 = Cuboid(-20,90,0, .25,1.5,.25, .125,0,0, .1,.1,.1);
  Cuboid claw3 = Cuboid(0,0,-20, .25,1.5,.25, 0,0,.125, .1,.1,.1);
  Cuboid claw4 = Cuboid(0,180,20, .25,1.5,.25, 0,0,-.125, .1,.1,.1);
public:
  void draw(); //draws the cuboid
};

class Reactor : public TObject
{
  using TObject::TObject;
private:
  OrbHolder bot = OrbHolder(0,0,0, 1,1,1, 0,0,0);
  OrbHolder top = OrbHolder(0,0,180, 1,1,1, 0,4.5,0);
  Sphere energy = Sphere(0,0,0, 1.5,1.5,1.5, -.5,1.75,.5, 0,1,1);
public:
  void draw();
};

class SurfaceOct : public TObject
{
  using TObject::TObject;
private:
  float vertices[27] = {.5,0,-.5, .26,0,0, .74,0,0,
                        1,0,-.26, 1,0,-.74, .74,0,-1,
                        .26,0,-1, 0,0,-.74, 0,0,-.26};
  float colors[27] = {.5,.5,.5, 1,1,1, 1,1,1, 1,1,1, 1,1,1,
                      1,1,1, 1,1,1, 1,1,1, 1,1,1};
  GLubyte indices[10] = {0,1,2,3,4,5,6,7,8,1};
public:
  void draw();
};

//===HH TERRAIN OBJECTS===
class OctRoom : public TObject
{
  using TObject::TObject;
private:
  SurfaceOct bot = SurfaceOct(0,0,0, 10,10,10, -5,0,5); //floor, but that's reserved
  SurfaceOct top = SurfaceOct(180,0,0, 10,10,10, -5,7,-5); //ceiling but now this is a naming convention I guess
  //walls, starting at far end (from 0 0 +z view) and rotating CCW
  SurfaceRect wall0 = SurfaceRect(90,0,0,     4.8,1,10,   -2.4,0,-5, .9,.9,.9);
  SurfaceRect wall1 = SurfaceRect(45,90,-90,  3.677,1,10, -5,0,-2.4, .8,.8,.8);
  SurfaceRect wall2 = SurfaceRect(0,90,-90,   4.8,1,10,   -5,0,2.4,  .9,.9,.9);
  SurfaceRect wall3 = SurfaceRect(-45,90,-90, 3.677,1,10, -2.4,0,5,  .8,.8,.8);
  SurfaceRect wall4 = SurfaceRect(-90,180,0,  4.8,1,6,     2.4,4,5,  .9,.9,.9); //door
  SurfaceRect wall5 = SurfaceRect(-45,-90,90, 3.677,1,10,  5,0,2.4,  .8,.8,.8);
  SurfaceRect wall6 = SurfaceRect(0,-90,90,   4.8,1,10,    5,0,-2.4, .9,.9,.9);
  SurfaceRect wall7 = SurfaceRect(45,-90,90,  3.677,1,10,  2.4,0,-5, .8,.8,.8);
public:
  void draw();
};
