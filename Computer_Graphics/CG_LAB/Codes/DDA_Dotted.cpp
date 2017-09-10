#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#define round(a) ((int)(a+0.5))

struct line
{
	int x1, y1;
	int x2, y2;
}L;

void init(line &l)
{
	l.x1 = l.x2 = l.y1 = l.y2 = 0;
}

void getline(line &l)
{
	printf("Enter the start and end points:\n(x1,y1),(x2,y2)\n");
	scanf("%d %d", &l.x1, &l.y1);
	scanf("%d %d", &l.x2, &l.y2);
}

int sign(int x)
{
	if (x==0)
		return 0;
	else
		return x<0? -1:1;
}

void setpX(GLint XCv, GLint yCv)
{
	glBegin (GL_POINTS);
		glVertex2i(XCv,yCv);
	glEnd();
}

int absl (int n)
{
    return ( (n>0) ? n : ( n * (-1)));
}

void DDA()
{
	int cnt = 0;
	bool flag = false;
	float dx = L.x2-L.x1;
	float dy = L.y2-L.y1;
	float len = absl(dx) > absl(dy) ? absl(dx) : absl(dy) ; 
	float delx = dx/(float)len;
	float dely = dy/(float)len;
	float x = L.x1, y = L.y1;
	// x = x + 0.5*sign(dx);
	// y = y + 0.5*sign(dy);
	setpX(x,y);
	while(len--)
	{
		if(cnt%5 == 0)
		{
			setpX(round(x),round(y));
		}
		cnt++;
		x = x+delx;
		y = y+dely;
	}
	
	glFlush();
	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	init(L);
	getline(L);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640,640);
	glutCreateWindow("DDA Line Algo");
	glutDisplayFunc(DDA);
	gluOrtho2D(640,0,640,0);
	glutMainLoop();
	return 0;
}