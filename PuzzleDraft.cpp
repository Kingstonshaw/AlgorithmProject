////////////////////////////////////////////////////////////////////////////////////        
// hw2.cpp
// William Shaw
// This program allows the user to order and display food on a plate
//
// Interaction:
// 
// 'n' for noodles, 'p' for pasta, 'r' for rice
// '+' to zoom in and '-' to zoom out
// '<' to rotate the plate around z axis in clockwise and '>' counterclockwise
// Right click for menu options
// 
//////////////////////////////////////////////////////////////////////////////////// 

#include <cstdlib>
#include <vector>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif



#define INACTIVE 0
#define Fries 1
#define Chips 2
#define Corn 3
#define Sweet_peas 4
#define Cucumber 5
#define Carrot 6
#define Random 7
#define Noodles 8
#define Rice 9
#define Pasta 10

#define PI 3.14159265


// Use the STL extension of C++.
using namespace std;

// Globals.
static int v = 30; // Number of longitudinal (verticle) slices.
static int h = 20; // Number of latitudinal (horizontal) slices 
				  //on hemisphere.
static float zoom = 1.0;
static bool selected_side = false;
static bool selected_main = false;
static GLsizei width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point
//static int SideType = INACTIVE; // Current drawing SideType.
static int SideType = INACTIVE;
static int MainType = INACTIVE;
static int pointCount = 0; // Number of  specified points.
static int tempX, tempY; // Co-ordinates of clicked point.
static int isGrid = 0; // Is there grid?
static int id1, id2; // Window identifiers.
static int NumOfSideTypes = 8;
static int rand1;
static int rand2;
const float ratio = float(width) / (height);
static int sides[5];
static int index = 0;
static float Xangle = 0;
static float Yangle = 0;
static float Zangle = 0;
static bool ColorScheme = false;
static float colors[6][3] =
{
	{0.0, 0.0, 0.0},
	{1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0},
	{1.0, 0.0, 1.0},

};
static float Xtrans = 0;
static float Ytrans = 0;
static float Ztrans = 0;



void drawCross(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x1, y2, 0.0);
	glVertex3f(x2, y1, 0.0);
	glEnd();
	//selected_side = false;

}

//void drawCheckCircle(float)
//{   glColor3f(0.6,0.6,0.6)
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	drawCircle(0.6*width, 0.775*height, 0.025*width, 20);
//}


void drawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * PI * float(i) / float(num_segments);//get the current angle
		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component
		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();

}



void displaytext(int x, int y, const char* string)
{
	glColor3f(0, 0, 0);
	glRasterPos2f(x, y);
	int l, i;
	l = (int)strlen(string);
	for (i = 0; i < l; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, string[i]);
	}
}

void displaytext2(int x, int y, const char* string)
{
	glColor3f(0, 0, 0);
	glRasterPos2f(x, y);
	int l, i;
	l = (int)strlen(string);
	for (i = 0; i < l; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void drawMySelectionBox(void)
{
	//drawcheckbox
	glColor3f(1, 1, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.05 * width, 0.19 * height, 0.1 * width, 0.24 * height);
	glRectf(0.4 * width, 0.19 * height, 0.45 * width, 0.24 * height);
	glRectf(0.66 * width, 0.19 * height, 0.71 * width, 0.24 * height);


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.05 * width, 0.19 * height, 0.1 * width, 0.24 * height);
	glRectf(0.4 * width, 0.19 * height, 0.45 * width, 0.24 * height);
	glRectf(0.66 * width, 0.19 * height, 0.71 * width, 0.24 * height);
	//text 
	displaytext2(0.1 * width, 0.9 * height, "which one of the following is a projection");
	displaytext2(0.1 * width, 0.85 * height, "of the shown polyhedron?");
	displaytext2(0.1 * width, 0.2 * height, "Next Problem");
	displaytext2(0.45 * width, 0.2 * height, "Rotate Hint");
	displaytext2(0.72 * width, 0.2 * height, "Show Solution");
	//draw check marks

	//if ((SideType == Fries) && (selected_side == true)) drawCross(0.2 * width, 0.8 * height, 0.25 * width, 0.75 * height);
	//else if ((SideType == Chips) && (selected_side == true)) drawCross(0.2 * width, 0.7 * height, 0.25 * width, 0.65 * height);
	//else if ((SideType == Corn) && (selected_side == true)) drawCross(0.2 * width, 0.6 * height, 0.25 * width, 0.55 * height);
	//else if ((SideType == Sweet_peas) && (selected_side == true)) drawCross(0.2 * width, 0.5 * height, 0.25 * width, 0.45 * height);
	//else if ((SideType == Cucumber) && (selected_side == true)) drawCross(0.2 * width, 0.4 * height, 0.25 * width, 0.35 * height);
	//else if ((SideType == Carrot) && (selected_side == true)) drawCross(0.2 * width, 0.3 * height, 0.25 * width, 0.25 * height);
	//else if ((SideType == Random) && (selected_side == true)) drawCross(0.2 * width, 0.2 * height, 0.25 * width, 0.15 * height);


	//draw radio
	glColor3f(1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawCircle(0.6 * width, 0.775 * height, 0.025 * width, 20);
	drawCircle(0.6 * width, 0.675 * height, 0.025 * width, 20);
	drawCircle(0.6 * width, 0.575 * height, 0.025 * width, 20);
	drawCircle(0.6 * width, 0.475 * height, 0.025 * width, 20);


	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawCircle(0.6 * width, 0.775 * height, 0.025 * width, 20);
	displaytext2(0.7 * width, 0.775 * height, "A.");
	drawCircle(0.6 * width, 0.675 * height, 0.025 * width, 20);
	displaytext2(0.7 * width, 0.675 * height, "B.");
	drawCircle(0.6 * width, 0.575 * height, 0.025 * width, 20);
	displaytext2(0.7 * width, 0.575 * height, "C.");
	drawCircle(0.6 * width, 0.475 * height, 0.025 * width, 20);
	displaytext2(0.7 * width, 0.475 * height, "D.");

	//draw check marks
	glColor3f(0.6, 0.6, 0.6);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (MainType == Noodles) drawCircle(0.6 * width, 0.775 * height, 0.020 * width, 20);
	if (MainType == Rice) drawCircle(0.6 * width, 0.675 * height, 0.020 * width, 20);
	if (MainType == Pasta) drawCircle(0.6 * width, 0.575 * height, 0.020 * width, 20);
	if (MainType == Random) drawCircle(0.6 * width, 0.475 * height, 0.020 * width, 20);
}


// Function to draw temporary point.
void drawTempPoint(void)
{
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	glVertex3f(tempX, tempY, 0.0);
	glEnd();
}


void drawPyramid(void)
{
	glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
		  // Front
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Right
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Back
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Left
	glColor3f(1.0f, 0.0f, 0.0f);       // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);       // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);       // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();   // Done drawing the pyramid
	glEnd();


}
// Function to draw a grid.
void drawGrid(void)
{
	int i;

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x5555);
	glColor3f(0.75, 0.75, 0.75);

	glBegin(GL_LINES);
	for (i = 2; i <= 9; i++)
	{
		glVertex3f(i * 0.1 * width, 0.0, 0.0);
		glVertex3f(i * 0.1 * width, height, 0.0);
	}
	for (i = 1; i <= 9; i++)
	{
		glVertex3f(0.1 * width, i * 0.1 * height, 0.0);
		glVertex3f(width, i * 0.1 * height, 0.0);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	//if(mainType== RICE)
	//if(mainTyoe== Noodle)
	//if(mainType ==Pasta)
}
//
//float cx=0,
//float cy=0,
//float cz=-20

// Drawing routine.
void drawScene1(void)
{
	glutSetWindow(id1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0, 0.0, 0.0);
	if (isGrid) drawGrid();
	//cout << width << height << "width and height";
	drawMySelectionBox();
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	//coordinates in the 
	//glTranslatef(250, 300, 0);
	glTranslatef(0.75*width, 0.775 * height, 0);
	glScalef(1, 1, 0.01);
	glutSolidCube(50); // Box.
	glPopMatrix();
	//drawPyramid();
	
	
	glutSwapBuffers();
}

// Drawing routine for second window.
void drawScene2(void)
{
	// Choose window.
	glutSetWindow(id2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

  
	///////
	glTranslatef(0.0, 0.0, -15.0);
	glutWireCube(5.0); // Box.

	///////
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
	//glFlush();
}

void pickSide(int y)
{
	if (y < (0.8 - NumOfSideTypes * 0.1) * height) SideType = INACTIVE;
	else if (y < (0.8 - 6 * 0.1) * height) SideType = Random;
	else if (y < (0.8 - 5 * 0.1) * height) SideType = Carrot;
	else if (y < (0.8 - 4 * 0.1) * height) SideType = Cucumber;
	else if (y < (0.8 - 3 * 0.1) * height) SideType = Sweet_peas;
	else if (y < (0.8 - 2 * 0.1) * height) SideType = Corn;
	else if (y < (0.8 - 1 * 0.1) * height) SideType = Chips;
	else if (y < (0.8) * height) SideType = Fries;
	else
	{
		SideType = INACTIVE;
		//selected_side = false;
	}
}

void pickMain(int y)
{
	if (y < (0.8 - 4 * 0.1) * height) MainType = INACTIVE;
	else if (y < (0.8 - 3 * 0.1) * height) MainType = Random;
	else if (y < (0.8 - 2 * 0.1) * height) MainType = Pasta;
	else if (y < (0.8 - 1 * 0.1) * height) MainType = Rice;
	else if (y < (0.8) * height) MainType = Noodles;
	else MainType = INACTIVE;
}


// The mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cout << "x: " << x << " y: " << y << endl;
		y = height - y; // Correct from mouse to OpenGL co-ordinates.

		// Click outside canvas - do nothing.
		if (x < 0 || x > width || y < 0 || y > height);

		else if (x < 0.3 * width && x > 0.15 * width)
		{
			pickSide(y);
			selected_side = !selected_side;
			sides[index++] = SideType;
		}
		else if (x < 0.7 * width && x > 0.55 * width)
		{
			pickMain(y);
			selected_main = !selected_main;
		}


	}

	glutSetWindow(id1);
	glutPostRedisplay();

	glutSetWindow(id2);
	glutPostRedisplay();
}

void mouseControl2(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		y = height - y; // Correct from mouse to OpenGL co-ordinates.

		// Click outside canvas - do nothing.
		if (x < 0 || x > width || y < 0 || y > height);

		else
		{
			Xtrans = x;
			Ytrans = y;
		}

	}
	glutSetWindow(id1);
	glutPostRedisplay();

	//glutSetWindow(id2);
	//glutPostRedisplay();
}



void mouseMotion(int x, int y)
{
	Xtrans += x;
	Ytrans += y;

	//glutPostRedisplay();
}


// Initialization routine.
void setup1(void)
{
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
}

// Initialization routine. Second window
void setup2(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}


// OpenGL window reshape routine.
void resize1(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set viewing box dimensions equal to window dimensions.
	glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);
	//glOrtho(-5, 5, -5, 5, 5, 100);
	//glFrustum(-5.0, 5.0, -5.0, 5.0, -50.0, 100.0);
	// Pass the size of the OpenGL window to globals.
	width = w;
	height = h;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
// OpenGL window reshape routine. Second window
// Reshape routine for second window.
void resize2(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Clear the canvas and reset for fresh drawing.
void clearAll(void)
{

	SideType = INACTIVE;
	MainType = INACTIVE;
	//pointCount = 0;
}

// The right button menu callback function.
void rightMenu(int id)
{
	if (id == 1)
	{
		clearAll();
		glutPostRedisplay();
	}
	if (id == 2) exit(0);
}

// The sub-menu callback function.
void grid_menu(int id)
{
	if (id == 3) isGrid = 1;
	if (id == 4) isGrid = 0;
	glutSetWindow(id1);
	glutPostRedisplay();

	glutSetWindow(id2);
	glutPostRedisplay();
}

void color_menu(int id)
{
	if (id == 5) ColorScheme = true;
	if (id == 6) ColorScheme = false;
	glutSetWindow(id1);
	glutPostRedisplay();

	glutSetWindow(id2);
	glutPostRedisplay();
}
// Function to create menu.
void makeMenu(void)
{
	int sub_menu;
	int sub_menub;
	sub_menu = glutCreateMenu(grid_menu);
	glutAddMenuEntry("On", 3);
	glutAddMenuEntry("Off", 4);

	sub_menub = glutCreateMenu(color_menu);
	glutAddMenuEntry("Royal", 5);
	glutAddMenuEntry("Aqua", 6);

	glutCreateMenu(rightMenu);
	glutAddSubMenu("Grid", sub_menu);
	glutAddSubMenu("ColorScheme", sub_menub);
	glutAddMenuEntry("Clear", 1);
	glutAddMenuEntry("Quit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	cout << "Interaction:" << endl;
	cout << "Left click on a box on the left to select a side and a main dish." << endl
		<< "Press 'n' for noodles, 'p' for pasta, 'r' for rice." << endl
		<< " The dish should visualize in the right window." << endl
		<< "Right click for menu options." << endl;
}

// Main routine.
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	// Create the first window and return id.
	id1 = glutCreateWindow("Puzzle");
	setup1();
	glutDisplayFunc(drawScene1);
	glutReshapeFunc(resize1);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);
	makeMenu(); // Create menu.

	// Second top-level window definition.
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(600, 100);

	// Create the second window and return id.
	id2 = glutCreateWindow("Shape(for testing)");
	// Initialization, display, and other routines of the second window. 
	setup2();
	glutDisplayFunc(drawScene2);
	glutReshapeFunc(resize2);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl2);
	glutMotionFunc(mouseMotion);
	makeMenu(); // Create menu.

	glutMainLoop();

	return 0;
}
