/****	car tute 	****/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GLUT_DISABLE_ATEXIT_HACK
#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>

//#include "utility.h"
//#include "glUtils.h"

#include "Axes.h"

#include "Car.h"

#define framesPerSecond 25
#define timerMSecs ((int)1000/framesPerSecond)  // compute time in miliseconds for a frame
bool timeForNextFrame = false;

//#define Near	 0.5
//#define Far	20.0

#define ESC	  27

#define cmdRed		 1
#define cmdGreen	 2
#define cmdExit		99

static int	WinWidth, WinHeight;
static int	AppMenu;
//static GLfloat	Spin;
static GLfloat	SpinAngle;

static GLfloat	eyePoint[3];
static GLfloat	lookAtPoint[3];
static GLfloat	upVec[3];//
static GLfloat  fov; // field of view
static GLfloat	near;
static GLfloat	far;

static GLfloat	color3[3];

static GLfloat	red[] = { 1.0, 0.0, 0.0 };
static GLfloat	blue[] = { 0.0, 1.0, 0.0 };
static GLfloat	green[] = { 0.0, 0.0, 1.0 };
static GLfloat	cyan[] = { 0.0, 1.0, 1.0 };
static GLfloat	magenta[] = { 1.0, 0.0, 1.0 };
static GLfloat	yellow[] = { 1.0, 1.0, 0.0 };
static GLfloat	black[] = { 0.0, 0.0, 0.0 };
static GLfloat	white[] = { 1.0, 1.0, 1.0 };

Axes *axes; //
Car *car;

static void setProjection()
{
	GLfloat aspect;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspect = (float)WinWidth / (float)WinHeight;
	gluPerspective(fov, aspect, near, far);
	/* Back to normal */
	glMatrixMode(GL_MODELVIEW);
}

static void seteyePoint()
{
	glLoadIdentity();
	gluLookAt(eyePoint[0], eyePoint[1], eyePoint[2],
		lookAtPoint[0], lookAtPoint[1], lookAtPoint[2],
		upVec[0], upVec[1], upVec[2]);
}

static void SetUp3D()
{
	setProjection();
	seteyePoint();
	/* Wireframe mode */
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(1, 1, 1, 1);
}

static void drawWorld()
{
	glPushMatrix();
	axes->render();
	//glRotatef(SpinAngle, 0.0, 1.0, 0.0);
	axes->drawAxesP(1);

	glColor3fv(color3);
	car->render();
	glPopMatrix();
	glPushMatrix();
	car->drawWheel();								// drawing Front Wheels
	glPopMatrix();
 
	glPushMatrix();
	car->drawTransmission();				// drawing Back Transmission
	glPopMatrix();
}

void CheckGL()
{
	int  err;
	char msg[256];

	err = glGetError();
	if (err != GL_NO_ERROR) {
		sprintf_s(msg, "OpenGL error: %s", (String)gluErrorString(err));
		fprintf(stderr, "%s\n", msg);
		exit(1);
	}
}

static void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetUp3D();
	drawWorld();

	/* Check everything OK and update screen */
	CheckGL();
	glutSwapBuffers();
}

static void resize(int width, int height)
{
	/* Save for event handlers */
	WinWidth = width;
	WinHeight = height;

	/* Reset view in window. */
	glViewport(0, 0, WinWidth, WinHeight);
}

/****		User events		****/

static void menuChoice(int item)
{
	switch (item) {
	case cmdRed:
		color3[0] = 1; // R
		color3[1] = 0; // G
		color3[2] = 0; // B
		break;
	case cmdGreen:
		color3[0] = 0; // R
		color3[1] = 1; // G
		color3[2] = 0; // B
		break;
	case cmdExit:
		exit(0);
		break;
	default:
		break;
	}
}

/* In most GUI systems we would write just one event handler
   for all kinds of keystrokes. In GLUT, we need one for the
   standard ASCII keys and one for special cursor or function
   style keys that vary from system to system. Because the
   GLUT special key code range overlaps with ASCII lowercase,
   it isn't safe to use the same function for both.        */

static void asciiKey(unsigned char key, int x, int y)
{
	if (key == ESC)
		menuChoice(cmdExit);
}

static void specialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_F2)
	{
		eyePoint[0] = 2.0;
		eyePoint[1] = 0.0; // changed
		eyePoint[2] = 4.0;

		lookAtPoint[0] = 0;
		lookAtPoint[1] = 0;
		lookAtPoint[2] = 0;

		upVec[0] = 0;
		upVec[1] = 1;
		upVec[2] = 0;

		fov = 160; // field of view
		near = 0.5;
		far = 20;
	}
}

/****		Startup			****/

static void initGraphics(void)
{
	/* Black background */
	glClearColor(0, 0, 0, 0);

	/* colour green */
	color3[0] = 0;
	color3[0] = 1;
	color3[0] = 0;

	/* Needed for vertex arrays */
	glEnableClientState(GL_VERTEX_ARRAY);

	/* Popup menu attached to right mouse button */
	AppMenu = glutCreateMenu(menuChoice);
	glutSetMenu(AppMenu);
	glutAddMenuEntry("Red", cmdRed);
	glutAddMenuEntry("Green", cmdGreen);
	glutAddMenuEntry("----", 0);
	glutAddMenuEntry("Exit", cmdExit);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* Start values */
	SpinAngle = 0.0;

	eyePoint[0] = 2.0;
	eyePoint[1] = 2.0;
	eyePoint[2] = 4.0;

	lookAtPoint[0] = 0;
	lookAtPoint[1] = 0;
	lookAtPoint[2] = 0;

	upVec[0] = 0;
	upVec[1] = 1;
	upVec[2] = 0;

	fov = 60; // field of view
	near = 0.5;
	far = 20;

	menuChoice(cmdGreen);

	car = new Car();
	axes = new Axes();
}

void timer(int value)
{
	timeForNextFrame = true;
	glutTimerFunc(timerMSecs, timer, 0);
}

/****		Main control		****/

static void spinDisplay(void)
{
	if (timeForNextFrame)
	{
		SpinAngle += 2.0;
		if (SpinAngle > 360.0)
			SpinAngle -= 360.0;
		glutPostRedisplay();
		timeForNextFrame = false;
	}
}

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 75);
	glutCreateWindow("Cube");

	initGraphics();

	glutDisplayFunc(display);
	glutReshapeFunc(resize);

	glutKeyboardFunc(asciiKey);
	glutSpecialFunc(specialKey);

	glutIdleFunc(spinDisplay);
	glutTimerFunc(timerMSecs, timer, 0);

	glutMainLoop();
	/* Should never get here, but keeps compiler happy */
	return 0;
}