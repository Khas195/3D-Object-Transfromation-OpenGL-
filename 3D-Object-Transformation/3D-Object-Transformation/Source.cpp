#include <iostream>
using namespace std;
#include <GL\glut.h>
#include <chrono>
#include <time.h>

#include <math.h>      // For math routines (such as sqrt & trig).

clock_t pyramidLastRotateTime;
clock_t pyramidTimeBetweenRotate = 2.0f;
GLfloat rtri; // Angle For The Triangle ( NEW )
GLfloat pyramidDelta = 0.5f;

clock_t cubeLastRotateTime;
clock_t cubeTimeBetweenRotate = 2.0f;
GLfloat rquad; // Angle For The Quad ( NEW )
GLfloat cubeDelta = 0.5f;


GLdouble radius = 2;
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 5.0 };
GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

// Light source position
GLfloat qaLightPosition[] = { 1.0, 1.0, 1.0, 0 };
//www.codemiles.com/c-opengl-examples/rotate-sphere-in-a-circle-with-light-t9130.html#sthash.VJ7slDdC.dpuf
GLfloat xRotated, yRotated, zRotated;


void init(void)
{
	glShadeModel(GLU_SMOOTH); // Enable Smooth Shading (7)
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Black Background (8)
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
	// Set lighting intensity and color
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


}

void displayPyramid(void)
{
	glLoadIdentity(); // Reset The Current Modelview Matrix (1)
	glTranslatef(-1.5f, -1.5f, -6.0f); // Move Left and Down 1.5 Units And Into The Screen 6.0
	
	// (2)
	glRotatef(rtri, 0.0f, 1.0f, 0.0f); // Rotate The Triangle On The Y axis ( NEW )
	// (3)
	glBegin(GL_TRIANGLES); // Start Drawing A Triangle (4)
	glColor3f(1.0f, 0.0f, 0.0f); // Red (5)
	glVertex3f(0.0f, 1.0f, 0.0f); // Top Of Triangle (Front) (6)

	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(-1.0f, -1.0f, 1.0f); // Left Of Triangle (Front)

	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(1.0f, -1.0f, 1.0f); // Right Of Triangle (Front)

	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(0.0f, 1.0f, 0.0f); // Top Of Triangle (Right)

	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(1.0f, -1.0f, 1.0f); // Left Of Triangle (Right)

	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(1.0f, -1.0f, -1.0f); // Right Of Triangle (Right)
	
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(0.0f, 1.0f, 0.0f); // Top Of Triangle (Back)
		
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(1.0f, -1.0f, -1.0f); // Left Of Triangle (Back)
	
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f); // Right Of Triangle (Back)
	
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(0.0f, 1.0f, 0.0f); // Top Of Triangle (Left)
	
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f); // Left Of Triangle (Left)
	
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(-1.0f, -1.0f, 1.0f); // Right Of Triangle (Left)
	glEnd(); //(4)
		// Done Drawing The Pyramid
}

void displayCube()
{
	glLoadIdentity(); // Reset The Current Modelview Matrix
	glTranslatef(1.5f, -1.5f, -7.0f); // Move Right and down 1.5 Units And Into The Screen 7.0
	glRotatef(rquad, 1.0f, 1.0f, 1.0f); // Rotate The Quad On The X axis ( NEW )

	glBegin(GL_QUADS); // Draw A Quad

	glColor3f(0.0f, 1.0f, 0.0f); // Set The Color To Green

	glVertex3f(1.0f, 1.0f, -1.0f); // Top Right Of The Quad (Top)

	glVertex3f(-1.0f, 1.0f, -1.0f); // Top Left Of The Quad (Top)

	glVertex3f(-1.0f, 1.0f, 1.0f); // Bottom Left Of The Quad (Top)

	glVertex3f(1.0f, 1.0f, 1.0f); // Bottom Right Of The Quad (Top)

	glColor3f(1.0f, 0.5f, 0.0f); // Set The Color To Orange

	glVertex3f(1.0f, -1.0f, 1.0f); // Top Right Of The Quad (Bottom)

	glVertex3f(-1.0f, -1.0f, 1.0f); // Top Left Of The Quad (Bottom)

	glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Left Of The Quad (Bottom)

	glVertex3f(1.0f, -1.0f, -1.0f); // Bottom Right Of The Quad (Bottom)

	glColor3f(1.0f, 0.0f, 0.0f); // Set The Color To Red

	glVertex3f(1.0f, 1.0f, 1.0f); // Top Right Of The Quad (Front)

	glVertex3f(-1.0f, 1.0f, 1.0f); // Top Left Of The Quad (Front)

	glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Left Of The Quad (Front)

	glVertex3f(1.0f, -1.0f, 1.0f); // Bottom Right Of The Quad (Front)

	glColor3f(1.0f, 1.0f, 0.0f); // Set The Color To Yellow

	glVertex3f(1.0f, -1.0f, -1.0f); // Top Right Of The Quad (Back)

	glVertex3f(-1.0f, -1.0f, -1.0f); // Top Left Of The Quad (Back)

	glVertex3f(-1.0f, 1.0f, -1.0f); // Bottom Left Of The Quad (Back)

	glVertex3f(1.0f, 1.0f, -1.0f); // Bottom Right Of The Quad (Back)

	glColor3f(0.0f, 0.0f, 1.0f); // Set The Color To Blue

	glVertex3f(-1.0f, 1.0f, 1.0f); // Top Right Of The Quad (Left)

	glVertex3f(-1.0f, 1.0f, -1.0f); // Top Left Of The Quad (Left)

	glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Left Of The Quad (Left)

	glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Right Of The Quad (Left)

	glColor3f(1.0f, 0.0f, 1.0f); // Set The Color To Violet

	glVertex3f(1.0f, 1.0f, -1.0f); // Top Right Of The Quad (Right)

	glVertex3f(1.0f, 1.0f, 1.0f); // Top Left Of The Quad (Right)

	glVertex3f(1.0f, -1.0f, 1.0f); // Bottom Left Of The Quad (Right)

	glVertex3f(1.0f, -1.0f, -1.0f); // Bottom Right Of The Quad (Right)

	glEnd();

	// Done Drawing The Quad
}

void displaySphere()
{
	glLoadIdentity(); // Reset The Current Modelview Matrix
	glTranslatef(0.0f, 1.5f, -10.0f); 
	// Red color used to draw.
	glColor3f(0.9, 0.3, 0.2);
	// changing in transformation matrix.
	// rotation about X axis
	glRotatef(xRotated, 1.0, 0.0, 0.0);
	// rotation about Y axis
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	// rotation about Z axis
	glRotatef(zRotated, 0.0, 0.0, 1.0);
	// scaling transfomation 
	glScalef(1.0, 1.0, 1.0);
	glColor3f(.5f, .5f, .5f);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.2); 
	glutSolidSphere(1, 25, 25);
}
void display(void)

{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer	
	glPushMatrix(); //(9)
	displayPyramid();
	displayCube();
	displaySphere();
	glPopMatrix();//(10)
	glutSwapBuffers();//(11)
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (float)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27: //ESC
		exit(0);
		break;
	default:
		break;
	}

}
void idle()
{
	zRotated += 0.02;
	if (clock() - cubeLastRotateTime >= cubeTimeBetweenRotate)
	{
		rquad += cubeDelta;
		cubeLastRotateTime = clock();
	}
	if (clock() - pyramidLastRotateTime >= pyramidTimeBetweenRotate)
	{
		rtri += pyramidDelta;
		pyramidLastRotateTime = clock();
		
	}
	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	xRotated = yRotated = zRotated = 30.0;
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display); //(13)
	glutReshapeFunc(reshape); //(14)
	glutKeyboardFunc(keyboard);//(15)
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}