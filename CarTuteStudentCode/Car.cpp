// sphere.cpp

#include "car.h"
double l = 2;			//longth of the car 车长
double w = 0.8;			//half width of the 车宽一半
double wheelW = 0.2*w;	//wheel width
double wheelH = 0.15*l;	//wheel hight

Car::Car()
{
	quadric1 = gluNewQuadric();
	gluQuadricDrawStyle(quadric1, GLU_LINE); //wireframe mode
}

Car::~Car()
{
	gluDeleteQuadric(quadric1);
}

void Car::drawCylinder(double slices, double stacks, double l)
{
	glColor3f(1, 0, 0);
	gluCylinder(quadric1, 0.15, 0.15, l, slices, stacks);
}

int Car::render()
{
	glPushMatrix();
	drawCar();
	glPopMatrix();
	return true;
}

void Car::drawCar()
{
	drawCylinder(10, 3, 2);
}

void Car::drawBaseWheel()
{
	glPushMatrix();
	gluCylinder(quadric1, wheelH, wheelH, wheelW, 20, 5);
	glRotatef(90, 1, 0, 0);

	glPopMatrix();
}

void Car::drawWheel()
{
	glPushMatrix();

	glTranslatef(w, 0, 0);
	glRotatef(90, 0, 1, 0);
	drawBaseWheel();		//right front

	glTranslatef(-l, 0, 0);
	drawBaseWheel();		//right back
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-w - wheelW, 0, 0);
	glRotatef(90, 0, 1, 0);
	drawBaseWheel();		//left front

	glTranslatef(-l, 0, 0);
	drawBaseWheel();		//right back
	glPopMatrix();
}

void Car::drawTransmission()
{
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	gluCylinder(quadric1, 0.06*l, 0.06*l, w + wheelW, 16, 4);//right front
	glRotatef(180, 0, 1, 0);
	gluCylinder(quadric1, 0.06*l, 0.06*l, w + wheelW, 16, 4);//left front
	glPopMatrix();
	glColor3f(0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(l, 0, 0);
	gluCylinder(quadric1, 0.06*l, 0.06*l, w, 20, 10);//left back
	glRotatef(180, 0, 1, 0);
	gluCylinder(quadric1, 0.06*l, 0.06*l, w + wheelW, 20, 10);//rignt back
}

//void car::drawAxel()
//{
//}