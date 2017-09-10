#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
using namespace std;

struct line
{
	int x1, y1;
	int x2, y2;
}L;

typedef struct line line;

void init(line *l)
{
	l->x1 = l->x2 = l->y1 = l->y2 = 0;
}

void getLine(line *l)
{
	printf("Enter the start and end points:\n(x1,y1),(x2,y2)\n");
	scanf("%d %d", &l->x1, &l->y1);
	scanf("%d %d", &l->x2, &l->y2);
}

void setpX(GLint XCv, GLint yCv)
{
	glBegin (GL_POINTS);
		glVertex2i(XCv,yCv);
	glEnd();
}

void Bline()
{
	int x = L.x1, y = L.y1;
	int dx = abs(L.x2-L.x1);
	int dy = abs(L.y2-L.y1);
	int P = 2*dy-dx;
	int points = dx;
	while(points--)
	{
		setpX(x,y);
		if(P < 0)
		{
			x = x+1;
			y = y;
			P = P + 2*dy;
		}
		else
		{
			x = x+1;
			y = y+1;
			P = P + 2*dy - 2*dx;
		}
	}
	glFlush();
	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	init(&L);
	getline(&L);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640,640);
	glutCreateWindow("Bresenham's Line Algo");
	glutDisplayFunc(Bline);
	gluOrtho2D(640,0,640,0);
	glutMainLoop();
	return 0;
}