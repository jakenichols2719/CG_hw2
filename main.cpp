/*
 * Homework 2: Objects
 * Created by James Nichols
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <math.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "objects.h"
#include "hh_fabs.h"

//trig macros, stolen from ex8
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))


OctRoom room (0,0,0, 3,2,3, 0,0,0);
Reactor react (0,0,0, 2,2,2, 0,0,0);
ControlPanel c1 (0,0,0, 2,1,1, -3,0,-13);
ControlPanel c2 (0,0,0, 1,1,1, 1.5,0,-13);
ControlPanel c3 (0,0,0, 1,1,1, 3.6,0,-13);
Sconce s1 (0,0,0, 1.2,1.2,1.2, 0,7,-15);
Sconce s2 (0,0,0, 1.2,1.2,1.2, -15,7,0);
Sconce s3 (0,0,0, 1.2,1.2,1.2, 15,7,0);
int th = 0;
int ph = 0;

void drawObjects() {
  room.draw();
  react.draw();
  c1.draw();
  c2.draw();
  c3.draw();
  s1.draw();
  s2.draw();
  s3.draw();
}

//todo: linked list for objects
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0,1,7, 0,1,0, 0,1,0);
  glRotated(ph,1,0,0);
  glRotated(th,0,1,0);
  glPushMatrix();
  drawObjects();
  glPopMatrix();
  /*
  glBegin(GL_LINE_LOOP);
    glVertex3f(-2,-1,0);
    glVertex3f(0,-1,0);
    glVertex3f(0,0,0);
    glVertex3f(-1,0,0);
  glEnd();
  */
  glPointSize(10);
  glColor3f(1,0,0);
  glBegin(GL_POINTS);
  glVertex3f(0,0,0);
  glEnd();
  glutSwapBuffers();
}

//OpenGL reshape function
void reshape(int width,int height)
{
  //set viewport
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  //projection mode
  glMatrixMode (GL_PROJECTION);
  //reset transform
  glLoadIdentity ();
  //set up perspective
  glOrtho(0, 0, (GLsizei) width, (GLsizei) height, -1, 1);
  gluPerspective(60,(float)width/height,1,50);
  //set back to modelview
  glMatrixMode (GL_MODELVIEW);
  //reset modelview too for good measure
  glLoadIdentity();
}

//OpenGL special key function
void special(int key,int x,int y)
{
  //  Right arrow key - increase azimuth by 5 degrees
  if (key == GLUT_KEY_RIGHT)
    th += 5;
  //  Left arrow key - decrease azimuth by 5 degrees
  else if (key == GLUT_KEY_LEFT)
    th -= 5;
  //  Up arrow key - increase elevation by 5 degrees
  else if (key == GLUT_KEY_UP)
    ph += 5;
  //  Down arrow key - decrease elevation by 5 degrees
  else if (key == GLUT_KEY_DOWN)
    ph -= 5;
  //  Keep angles to +/-360 degrees
  th %= 360;
  ph %= 360;
  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}

void init() {
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv); //initialize glut
  //init with rgb, double buffer, depth test
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(600,600); //600x600 window
  glutCreateWindow("James Nichols"); //create window
  glutDisplayFunc(display); //display function
  glutReshapeFunc(reshape); //reshape function
  glutSpecialFunc(special);
  glEnable(GL_DEPTH_TEST); //enable depth test
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  init();
  glutMainLoop();
  return 0;
}
