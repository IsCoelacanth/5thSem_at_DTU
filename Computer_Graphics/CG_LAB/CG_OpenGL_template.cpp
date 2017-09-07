#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
using namespace std;

/*
	Use a structure to hold coordinates
	Use global variables 
	Define a drawing function to execute the graphics
*/

void setpX(GLint XCv, GLint yCv)
{
	glBegin (GL_POINTS);
		glVertex2i(XCv,yCv);
	glEnd();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640,640);
	glutCreateWindow("<--Name of Window-->");
	glClearColor(255,255,255,0.f);
	glColor3f(0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(<--Name of Drawing Function-->);
	gluOrtho2D(640,0,640,0);
	glutMainLoop();
	return 0;
}