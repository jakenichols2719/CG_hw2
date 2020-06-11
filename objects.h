#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <iostream>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//trig macros, stolen from ex8
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

/*
 * TObject Class
 * To be inherited by any drawn object. Controls position, rotation, and scale.
 * Individual classes provide coordinates for objects.
*/
class TObject
{
  //manip variables
protected:
  float rotation[3]; //rotation per axis in degrees
  float scale[3]; //scale by axis, pre-rotation;
  float position[3]; //position coordinates
  float solidColor[3] = {-1,-1,-1}; //set to -1,-1,-1 by default to signal disuse
public:
  TObject(); //void constructor, default values
  TObject(float rx, float ry, float rz,
          float sx, float sy, float sz,
          float px, float py, float pz); //parameter constructor, no color
  TObject(float rx, float ry, float rz,
          float sx, float sy, float sz,
          float px, float py, float pz,
          float c0, float c1, float c2); //parameter constructor, color
  TObject(float* r, float* s, float* p); //parameter constructor with arrays
  float* getRotation() { return rotation; };
  float* getScale() { return scale; };
  float* getPosition() { return position; };
  float* getSolidColor() { return solidColor; };
  void setRotation(float* rot);
  void setScale(float* sca);
  void setPosition(float* pos);
  void setSolidColor(float* col);
  void transform(); //sets all transforms. remember to push/pop matrices!
};

/*
 * Surface object
 * 1x1 surface in xz plane. Counterclockwise from above.
*/
class SurfaceRect : public TObject
{
  using TObject::TObject;
private:
  //spatial data
  float vertices[12] = {0,0,0, 1,0,0, 1,0,-1, 0,0,-1};
  float colors[12] = {.5,.5,.5, .5,.5,.5, .5,.5,.5, .5,.5,.5};
  GLubyte indices[4] = {0,1,2,3};
public:
  void draw(); //draws the cuboid
};

/*
 * Cuboid shape
 * 1x1x1 cube
*/
class Cuboid : public TObject
{
  using TObject::TObject;
private:
  //spatial data
  float vertices[24] = {0,0,0,  1,0,0,  1,1,0,  0,1,0,
                        0,0,-1, 1,0,-1, 1,1,-1, 0,1,-1};
  float colors[24] = {1,1,1, 1,1,1, .5,.5,.5, .5,.5,.5,
                      1,1,1, 1,1,1, .5,.5,.5, .5,.5,.5};
  GLubyte indices[24] = {0,1,2,3, 1,5,6,2, 5,4,7,6,
                        4,0,3,7, 4,5,1,0, 3,2,6,7};
public:
  void draw(); //draws the cuboid
};

/*
 * Pyramid shape
 * 1x1 square base, height 1
*/
class Pyramid : public TObject
{
  using TObject::TObject;
private:
  //spatial data
  float vertices[15] = {0,0,0, 1,0,0, 1,0,-1, 0,0,-1, .5,1,-.5};
  float colors[15] = {1,1,1, 1,1,1, 1,1,1, 1,1,1, .5,.5,.5};
  GLubyte indices[18]= {0,1,4, 1,2,4, 2,3,4, 3,0,4, 3,2,1,3,1,0};
public:
  void draw(); //draws the cuboid
};

/*
 * Sphere shape
 * Radius .5, high resolution
*/
class Sphere: public TObject
{
  using TObject::TObject;
private:
  float res = 10; //angle step, lower = higher resolution
public:
  //set resolution call
  void setRes(float r) { res = r; };
  void draw();
};

/*
 * House object
 * Mostly for testing purposes with combining objects.
*/
class House : public TObject
{
  using TObject::TObject;
private:
  //spatial data
  Cuboid base = Cuboid (0,0,0, 1,.8,1, .1,0,-.1);
  Pyramid roof = Pyramid (0,0,0, 1.2,.4,1.2, 0,.8,0);
  int i = 1;
  /*
  float vertices[15] = {0,0,0, 1,0,0, 1,0,-1, 0,0,-1, .5,1,-.5};
  float colors[15] = {1,1,1, 1,1,1, 1,1,1, 1,1,1, .5,.5,.5};
  GLubyte indices[12]= {0,1,4, 1,2,4, 2,3,4,  3,0,4};
  */
public:
  void initShapes();
  void draw(); //draws the cuboid
};
