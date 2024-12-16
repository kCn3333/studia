#include <GL/glut.h> //laduje biblioteke gl.h, glu.h i glut.h

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
	glBegin(GL_TRIANGLES);		  // zaczynamy rysowac odcinki
	glColor3f(0.0, 0.0, 1.0);	  // ustawia kolor na czerwony
	glVertex2i(50, 250);		  // wspolrzedne pierwszego wierzcholka
	glColor3f(0.0, 1.0, 1.0);	  // ustawia kolor na czerwony
	glVertex2i(250, 50);		  // wspolrzedne drugiego wierzcholka
	glColor3f(0.0, 0.0, 0.0);	  // ustawia kolor na czerwony
	glVertex2i(250, 250);		  // wspolrzedne pierwszego wierzcholka
	glEnd();					  // konczymy rysowanie
	glFlush();					  // oprozniamy bufor
}

void obrot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
	{
		glRotatef(30, 0, 0, 1); // obraca o kat 30 stopni
	}
	rysuj();
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);						 // inicjalizuje GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // ustawia tryb wyswietlania
	glutInitWindowPosition(50, 100);			 // ustawia lewy,gorny rog okienka
	glutInitWindowSize(400, 400);				 // ustawia wysokosc i szerokosc okienka
	glutCreateWindow("MOJA GRAFIKA");			 // tworzy okienko

	init(); // inicjalizujemy wyswietlanie

	glutDisplayFunc(rysuj); // tworzy grafike
	glutMouseFunc(obrot);	// o
	glutMainLoop();			// rysuje bufor i czeka na zdarzenia
	return (0);
}
