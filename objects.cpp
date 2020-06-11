#include "objects.h"

//===TObject DEFINITIONS===
TObject::TObject()
{
  rotation[0] = 0; rotation[1] = 0; rotation[2] = 0;
  scale[0] = 1; scale[1] = 1; scale[2] = 1;
  position[0] = 0; position[1] = 0; position[2] = 0;
}

TObject::TObject(float rx, float ry, float rz,
                 float sx, float sy, float sz,
                 float px, float py, float pz)
{
  rotation[0] = rx; rotation[1] = ry; rotation[2] = rz;
  scale[0] = sx; scale[1] = sy; scale[2] = sz;
  position[0] = px; position[1] = py; position[2] = pz;
}

TObject::TObject(float rx, float ry, float rz,
                 float sx, float sy, float sz,
                 float px, float py, float pz,
                 float c0, float c1, float c2)
{
  rotation[0] = rx; rotation[1] = ry; rotation[2] = rz;
  scale[0] = sx; scale[1] = sy; scale[2] = sz;
  position[0] = px; position[1] = py; position[2] = pz;
  solidColor[0] = c0, solidColor[1] = c1, solidColor[2] = c2;
}

void TObject::setRotation(float* rot)
{
  rotation[0] = rot[0];
  rotation[1] = rot[1];
  rotation[2] = rot[2];
}

void TObject::setScale(float* sca)
{
  scale[0] = sca[0];
  scale[1] = sca[1];
  scale[2] = sca[2];
}

void TObject::setPosition(float* pos)
{
  position[0] = pos[0];
  position[1] = pos[1];
  position[2] = pos[2];
}

void TObject::setSolidColor(float* col)
{
  solidColor[0] = col[0];
  solidColor[1] = col[1];
  solidColor[2] = col[2];
}

void TObject::transform()
{
  //transforms
  //translation
  glTranslatef(position[0], position[1], position[2]);
  //rotation (horribly inefficient, fix this.)
  //rotation around y first makes x/z more predictable
  glRotatef(rotation[2],0,0,1);
  glRotatef(rotation[0],1,0,0);
  glRotatef(rotation[1],0,1,0);
  //scale
  glScalef(scale[0], scale[1], scale[2]);
}

//===individual draw functions===

void SurfaceRect::draw()
{
  glPushMatrix();
  transform(); //standard set of transformations
  //draw
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  if(solidColor[0] == -1) {
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
  } else {
    glColor3fv(solidColor);
  }
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
  glPopMatrix();
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

void Cuboid::draw()
{
  glPushMatrix();
  transform(); //standard set of transformations
  //draw
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  if(solidColor[0] == -1) {
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
  } else {
    glColor3fv(solidColor);
  }
  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
  glPopMatrix();
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

void Pyramid::draw()
{
  glPushMatrix();
  transform(); //standard set of transformations
  //draw
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  if(solidColor[0] == -1) {
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
  } else {
    glColor3fv(solidColor);
  }
  glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, indices);
  glPopMatrix();
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

//vertex calculator for spheres
static void SphereVertex(double th,double ph)
{
  //glColor3f(Cos(th)*Cos(th) , Sin(ph)*Sin(ph) , Sin(th)*Sin(th));
  glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
}

void Sphere::draw()
{
  glPushMatrix();
  //needs custom transformations
  //translate, keep in unit position for consistency
  glTranslatef(position[0]+.5, position[1]+.5, position[2]-.5);
  //rotation (horribly inefficient, fix this.);
  glRotatef(rotation[2],0,0,1);
  glRotatef(rotation[0],1,0,0);
  glRotatef(rotation[1],0,1,0);
  //scale
  glScalef(.5,.5,.5); //keep sphere in unit size with default values
  glScalef(scale[0], scale[1], scale[2]);
  //color
  if(solidColor[0] == -1) {
    glColor3f(1.0,1.0,1.0);
  } else {
    glColor3fv(solidColor);
  }
  //draw
  //iterate through yz angle (vertical)
  for(int a_yz=0; a_yz<=360; a_yz+=res) {
    //iterate through xz angle (horizontal), draw latitude band
    glBegin(GL_QUAD_STRIP);
    for(int a_xz=0; a_xz<=360; a_xz+=res) {
      SphereVertex(a_xz, a_yz);
      SphereVertex(a_xz, a_yz+res);
    }
    glEnd();
  }
  glPopMatrix();
}

void House::draw()
{
  glPushMatrix();
  transform(); //standard set of transforms (test)
  //draw
  base.draw();
  roof.draw();
  glPopMatrix();
}
