#ifndef __CarA__
#define __CarA__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GLUT_DISABLE_ATEXIT_HACK
#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "utility.h"
#include "glUtils.h"

class Car 
{
protected:

GLUquadricObj *quadric1;	
void drawCylinder(double slices, double stacks,double l);


void drawCar();

void drawBaseWheel();

//void drawAxel();

public:
virtual int render();
Car();
~Car();
void drawWheel();
void drawTransmission();
};

#endif
