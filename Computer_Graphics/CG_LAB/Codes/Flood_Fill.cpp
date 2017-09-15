#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using namespace std;

//Structure to store circle details.
struct Circle {
	GLint x;
	GLint y;
	GLfloat R;
};
Circle P;

//Structure to store the color details
struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

//Function to input the circle values
void get_Circle()
{
	printf("Enter the center\n");
	scanf("%d %d",&P.x,&P.y);
	printf("Enter the radius\n");
	scanf("%f",&P.R);
}

//Initializes the OpenGL window to white BG origin bottom left.
void init() 
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 640);
}

//Function to read pixel from screen and return its RGB values
Color getPixelColor(GLint x, GLint y) 
{
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

//Function to set the pixel to new color
void setPixelColor(GLint x, GLint y, Color color) 
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

//The Flood Fill algorithm
void floodFill(GLint x, GLint y, Color oldColor, Color newColor) 
{
	Color color;
	color = getPixelColor(x, y);

	if(color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b)
	{
		setPixelColor(x, y, newColor);
		floodFill(x+1, y, oldColor, newColor);
		floodFill(x, y+1, oldColor, newColor);
		floodFill(x-1, y, oldColor, newColor);
		floodFill(x, y-1, oldColor, newColor);
	}
	return;
}

//Function to draw circle using the polar coordinates
void draw_circle() 
{
	GLfloat step = 1/P.R;
	GLfloat x, y;

	for(GLfloat theta = 0; theta <= 360; theta += step) {
		x = P.x + (P.R * cos(theta));
		y = P.y + (P.R * sin(theta));
		glVertex2i(x, y);
	}
}

//Calls the flood fill on mouse click
void onMouseClick(int button, int state, int x, int y)
{
	Color newColor = {0.45f, 0.77f, 0.5f};
	Color oldColor = {1.0f, 1.0f, 1.0f};

	floodFill(320, 240, oldColor, newColor);
}

//The main display function
void display() {

	//Draw the circle
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		draw_circle();
	glEnd();
	glFlush();
	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	get_Circle();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutCreateWindow("FloodFill");
	init();
	glutDisplayFunc(display);	
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}