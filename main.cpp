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

//camera settings for perspective modes
struct CameraPos {
  float x,y,z; //position
  float lx,ly,lz; //look
};

//objects; I need a better way to do this but not for now
OctRoom room (0,0,0, 3,2,3, 0,0,0);
Reactor react (0,0,0, 2,2,2, 0,0,0);
ControlPanel c1 (0,0,0, 2,1,1, -3,0,-13);
ControlPanel c2 (0,0,0, 1,1,1, 1.5,0,-13);
ControlPanel c3 (0,0,0, 1,1,1, 3.6,0,-13);
Sconce s1 (0,0,0, 1.2,1.2,1.2, 0,7,-15);
Sconce s2 (0,0,0, 1.2,1.2,1.2, -15,7,0);
Sconce s3 (0,0,0, 1.2,1.2,1.2, 15,7,0);

//camera variables
int th = 15;
int ph = 45;
int mode = 3; //1st person, perspective, ortho
CameraPos cam;
float gWidth, gHeight; //window size

//Draws a specified list of objects. Makes my life easier.
void drawObjects()
{
  room.draw();
  react.draw();
  c1.draw();
  c2.draw();
  c3.draw();
  s1.draw();
  s2.draw();
  s3.draw();
}

//reset camera to a position based on mode
void resetCamera()
{
  if(mode == 1) {
    cam.x = 0;
    cam.y = 1;
    cam.z = 7;
    cam.lx = 0;
    cam.ly = 1;
    cam.lz = 6;
    th = 0;
    ph = 0;
  }
  if(mode == 2) {
    cam.x = 0;
    cam.y = 45;
    cam.z = 15;
    cam.lx = 0;
    cam.ly = 3.5;
    cam.lz = 0;
    th = 15;
    ph = -30;
  }
  if(mode == 3) {
    th = 15;
    ph = 45;
  }
}

//transform function for different camera modes
void transformCamera()
{
  switch(mode) {
    case 1: //first person
      //limit vertical rotation (ph)
      if(ph >= 90) {
        ph = 89.9;
      }
      if(ph <= -90) {
        ph = -89.9;
      }
      //set rotation
      cam.lx = cam.x + Sin(th) * Cos(ph);
      cam.ly = cam.y + Sin(ph);
      cam.lz = cam.z - Cos(th) * Cos(ph);
      gluLookAt(cam.x,cam.y,cam.z, cam.lx,cam.ly,cam.lz, 0,1,0);
      break;
    case 2: //perspective
      gluLookAt(cam.x,cam.y,cam.z, cam.lx,cam.ly,cam.lz, 0,1,0);
      glRotated(ph,1,0,0);
      glRotated(th,0,1,0);
      break;
    case 3: //ortho
      glRotated(ph,1,0,0);
      glRotated(th,0,1,0);
      break;
    default:
      break;
  }
}

//gl display function
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  transformCamera();
  glPushMatrix();
  drawObjects();
  glPopMatrix();
  glPointSize(10);
  glColor3f(1,0,0);
  glBegin(GL_POINTS);
  glVertex3f(0,0,0);
  glEnd();
  glutSwapBuffers();
}

//projection function for mode shift
void project(float asp, float dim)
{
  switch(mode) {
    case 1:
      gluPerspective(60,asp,1,32);
      break;
    case 2:
      gluPerspective(60,asp,1,64);
      break;
    case 3:
      glOrtho(-asp*dim, asp*dim, -dim, dim, -dim, dim);
      break;
    default:
      break;
  }
}

//OpenGL reshape function
void reshape(int width,int height)
{
  gWidth = width;
  gHeight = height;
  //set viewport
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  //projection mode
  glMatrixMode (GL_PROJECTION);
  //reset transform
  glLoadIdentity ();
  //set up perspective
  //glOrtho(0, 0, (GLsizei) width, (GLsizei) height, -1, 1);
  float asp = (float)width/height;
  project(asp, 25);
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

void keyboard(unsigned char key, int x, int y)
{
  //mode change
  switch(key) {
    case '0':
      resetCamera();
      break;
    case '1':
      mode = 1;
      resetCamera();
      break;
    case '2':
      mode = 2;
      resetCamera();
      break;
    case '3':
      mode = 3;
      resetCamera();
      break;
    case 27: //exit case
      exit(0);
    default:
      break;
  }
  //first-person movement
  if(mode == 1) {
    float dx = cam.lx - cam.x;
    float dz = cam.lz - cam.z;
    switch(key) {
      case 'w':
        cam.x += dx;
        cam.z += dz;
        break;
      case 'a':
        cam.x += dz;
        cam.z -= dx;
        break;
      case 's':
        cam.x -= dx;
        cam.z -= dz;
        break;
      case 'd':
        cam.x -= dz;
        cam.z += dx;
        break;
      default:
        break;
    }
  }
  //reshape so that projection changes properly
  reshape(gWidth,gHeight);
  //redisplay
  glutPostRedisplay();

}

void init()
{
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv); //initialize glut
  //init with rgb, double buffer, depth test
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(600,600); //600x600 window
  glutCreateWindow("James Nichols"); //create window
  glutDisplayFunc(display); //display function
  glutReshapeFunc(reshape); //reshape function
  glutSpecialFunc(special); //arrow keys, esc
  glutKeyboardFunc(keyboard); //keyboard controls
  glEnable(GL_DEPTH_TEST); //enable depth test
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  init();
  glutMainLoop();
  return 0;
}
