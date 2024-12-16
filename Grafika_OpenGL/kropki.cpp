#include <stdio.h>
#include <GL/freeglut.h> //laduje biblioteke gl.h, glu.h i glut.h

GLint n = 0;
GLint points[10000][2];

GLint winHeight = 300;
GLint winWidth = 400;
GLint winXPos = 100;
GLint winYPos = 100;
GLint xmin = 0;
GLint xmax = 200;
GLint ymin = 0;
GLint ymax = 150;

GLfloat alfa = 0.0;

// inicjalizacja okienka
void init(void)
{

	glClearColor(1.0, 1.0, 1.0, 0.0); // ustawia kolor tla na bialy

	glMatrixMode(GL_PROJECTION); // nastepne operacje dotyczna macierzy projekcji

	gluOrtho2D(xmin, xmax, ymin, ymax); // ustala zakres wspolrzednych na ekranie
}

void displayFcn(void)
{

	GLint i;

	glClear(GL_COLOR_BUFFER_BIT); // czysci bufor

	glColor3f(1.0, 0.0, 0.0); // ustawia kolor na czerwony
	glPointSize(3.0);

	glBegin(GL_POINTS);
	for (i = 0; i < n; i++)
		glVertex2i(points[i][0], points[i][1]);
	glEnd();
}

void resizeWindow(GLint x, GLint y)
{

	winWidth = x;
	winHeight = y;

	glViewport(0, 0, winWidth, winHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(xmin, xmax, ymin, ymax);

	glutPostRedisplay();
}

void plotPoint(GLint x, GLint y)
{

	points[n][0] = x;
	points[n][1] = y;

	printf("x=%i, y=%i\n", x, y);

	n++;

	glutPostRedisplay();
}

void mouseFcn(GLint button, GLint action, GLint x, GLint y)
{

	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
		plotPoint((GLint)((1.0 * (xmax - xmin) / winWidth) * x), (GLint)((1.0 * (ymax - ymin) / winHeight) * (winHeight - y)));
}

void keyboardFcn(GLint key, GLint xMouse, GLint yMouse)
{

	if (key == GLUT_KEY_RIGHT)
	{
		printf("right\n");

		alfa += 0.1;

		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_LEFT)
	{
		printf("left\n");

		alfa -= 0.1;

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

	glutReshapeFunc(resizeWindow);

	glutMouseFunc(mouseFcn);

	glutSpecialFunc(keyboardFcn);

	glutMainLoop(); // rysuje bufor i czeka na zdarzenia

	return 1;
}
