#include <GL/glut.h> //laduje biblioteke gl.h, glu.h i glut.h

double **piktab;
int ile = 0;
GLint windowWidth, windowHeight;

// inicjalizacja okienka
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);	// ustawia kolor tla na bialy
	glMatrixMode(GL_PROJECTION);		// nastepne operacje dotyczna macierzy projekcji
	gluOrtho2D(0.0, 300.0, 0.0, 300.0); // ustala zakres wspolrzednych na ekranie
}

void rysuj(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // czysci bufor
	for (int i = 0; i < ile; ++i)
	{
		glPointSize(5);
		glBegin(GL_POINTS);						// zaczynamy rysowac odcinki
		glColor3f(1.0, 0.0, 1.0);				// ustawia kolor na czerwony
		glVertex2d(piktab[i][0], piktab[i][1]); // wspolrzedne drugiego wierzcholka
		glEnd();								// konczymy rysowanie
	}
	glFlush(); // oprozniamy bufor
}

void pik(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		glPointSize(5);
		glBegin(GL_POINTS);																		  // zaczynamy rysowac odcinki
		glColor3f(1.0, 0.0, 1.0);																  // ustawia kolor na czerwony
		glVertex2d(xMouse * 300.0 / windowWidth, (windowHeight - yMouse) * 300.0 / windowHeight); // wspolrzedne drugiego wierzcholka
		piktab[ile][0] = xMouse * 300.0 / windowWidth;
		piktab[ile][1] = (windowHeight - yMouse) * 300.0 / windowHeight;
		if (ile < 1000 - 1)
		{
			ile++;
		}
		glEnd();   // konczymy rysowanie
		glFlush(); // oprozniamy bufor
	}
}

void resize(GLint width, GLint height)
{
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, windowWidth, windowHeight); // zakres rysowania w ramach mojego okienka
	rysuj();
}

int main(int argc, char **argv)
{

	piktab = new double *[1000];
	for (int i = 0; i < 1000; ++i)
	{
		piktab[i] = new double[2];
	}

	glutInit(&argc, argv);						 // inicjalizuje GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // ustawia tryb wyswietlania
	glutInitWindowPosition(50, 100);			 // ustawia lewy,gorny rog okienka
	windowWidth = 400;
	windowHeight = 400;
	glutInitWindowSize(windowWidth, windowHeight); // ustawia wysokosc i szerokosc okienka
	glutCreateWindow("MOJA GRAFIKA");			   // tworzy okienko
	glutReshapeFunc(resize);

	init(); // inicjalizujemy wyswietlanie

	glutDisplayFunc(rysuj); // tworzy grafike TODO: zrobic tablice punktow, zeby je zapamietac i rysowac za kazdym razem
	glutMouseFunc(pik);
	glutMainLoop(); // rysuje bufor i czeka na zdarzenia
	return (0);
}
