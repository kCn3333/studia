#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/freeglut.h> //laduje biblioteke gl.h, glu.h i glut.h

GLint n = 0;
GLint points[10000][2];

GLint winHeight = 500;
GLint winWidth = 500;
GLint winXPos = 100;
GLint winYPos = 100;
GLint xmin = 0;
GLint xmax = 200;
GLint ymin = 0;
GLint ymax = 150;

GLfloat alfa = 0.1;
GLfloat r = 10.0;

// inicjalizacja okienka
void init(void)
{

	glClearColor(1.0, 1.0, 1.0, 0.0); // ustawia kolor tla na bialy

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cos(alfa) * r, 0.0, sin(alfa) * r, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);

	glMatrixMode(GL_MODELVIEW);
}

void displayFcn(void)
{

	GLint i;
	glClear(GL_COLOR_BUFFER_BIT); // czysci bufor
	glColor3f(0.0, 0.0, 1.0);	  // ustawia kolor na niebieski
	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	// gluLookAt(cos(alfa)*r, 0.0, sin(alfa)*r, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glutWireTeapot(6.0);
	glTranslatef(0.0, 0.0, 20.0);
	glutWireTeapot(6.0);
	// glScalef(3.0,3.0,3.0);
	glColor3f(1.0, 0.0, 0.0); // ustawia kolor na niebieski
	// glutWireDodecahedron();
	glFlush();
}

void keyFcn(GLubyte key, GLint x, GLint y)
{

	if (key == 'q')
	{
		exit(1);
	}
	else if (key == 'a')
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0, 0.0, 60.0, 0.0, 0.0, -20.0, 0.0, 1.0, 0.0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(20, 1.0, 0.0, 70.0);

		glMatrixMode(GL_MODELVIEW);

		glutPostRedisplay();
	}
	else if (key == 'b')
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(160.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(20, 1.0, 0.0, 70.0);

		glMatrixMode(GL_MODELVIEW);

		glutPostRedisplay();
	}
	else if (key == '1')
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);

		glMatrixMode(GL_MODELVIEW);

		glutPostRedisplay();
	}
	else if (key == '2')
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);

		glMatrixMode(GL_MODELVIEW);

		glutPostRedisplay();
	}
	else if (key == '3')
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);

		glMatrixMode(GL_MODELVIEW);

		glutPostRedisplay();
	}
}

void keyboardFcn(GLint key, GLint xMouse, GLint yMouse)
{

	if (key == GLUT_KEY_RIGHT)
	{

		alfa += 0.1;
		if (alfa > 3.14)
			alfa = -3.14;
		printf("%f\n", alfa);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(cos(alfa) * r, 0.0, sin(alfa) * r, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);

		glMatrixMode(GL_MODELVIEW);

		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_LEFT)
	{

		alfa -= 0.1;
		if (alfa < -3.14)
			alfa = 3.14;
		printf("%f\n", alfa);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(cos(alfa) * r, 0.0, sin(alfa) * r, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);

		glMatrixMode(GL_MODELVIEW);

		glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv); // inicjalizuje GLUT

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // ustawia tryb wyswietlania

	glutInitWindowPosition(winXPos, winYPos); // ustawia lewy,gorny rog okienka

	glutInitWindowSize(winWidth, winHeight); // ustawia wysokosc i szerokosc okienka

	glutCreateWindow("Tytul okienka"); // tworzy okienko

	init(); // inicjalizujemy wyswietlanie

	glutDisplayFunc(displayFcn); // tworzy grafike

	glutSpecialFunc(keyboardFcn);

	glutKeyboardFunc(keyFcn);

	glutMainLoop(); // rysuje bufor i czeka na zdarzenia

	return (0);
}
