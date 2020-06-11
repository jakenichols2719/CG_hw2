#include "hh_fabs.h"

void OrbHolder::draw()
{
  glPushMatrix();
  transform(); //standard set of transforms
  //draw
  base.draw();
  claw1.draw();
  claw2.draw();
  claw3.draw();
  claw4.draw();
  glPopMatrix();
}

void Reactor::draw()
{
  glPushMatrix();
  transform(); //standard set of transforms
  //draw
  bot.draw();
  top.draw();
  energy.draw();
  glPopMatrix();
}

void SurfaceOct::draw()
{
  glPushMatrix();
  transform(); //standard transformation
  //draw
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3,GL_FLOAT,0,vertices);
  if(solidColor[0] == -1) {
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
  } else {
    glColor3fv(solidColor);
  }
  glDrawElements(GL_TRIANGLE_FAN,10,GL_UNSIGNED_BYTE,indices);
  glPopMatrix();
}

//===TERRAIN OBJECTS===
void OctRoom::draw()
{
  glPushMatrix();
  transform();
  //draw
  bot.draw(); //floor
  top.draw(); //ceiling
  wall0.draw();
  wall1.draw();
  wall2.draw();
  wall3.draw();
  wall4.draw(); //door
  wall5.draw();
  wall6.draw();
  wall7.draw();
  glPopMatrix();
}
