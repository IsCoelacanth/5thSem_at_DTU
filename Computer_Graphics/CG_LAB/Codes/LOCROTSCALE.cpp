#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

int i;
double scalex, scaley, a[10], b[10], x, y, square_side;
double rads,theta;
double transx,transy,rotx,roty;

void line(float x, float y, float a, float b)
{
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(a, b);
	glEnd();
}

void translate()
{
    for(i = 0;i<4;i++)
	{
		a[i] =  a[i] + transx;
		b[i] =  b[i] + transy;
	}
}

void rot_translate()
{
    for(i = 0;i<4;i++)
	{
		a[i] =  a[i] + rotx;
		b[i] =  b[i] + roty;
	}
}

void rotation()
{
  	// Find the vertices of the rotated square
	double temp;
	rads = (double)((theta*3.1428)/180.0);
	for(i = 0;i<4;i++)
	{
		temp = a[i];
		a[i] =  a[i]*cos(rads) - b[i]*sin(rads);
		b[i] =  temp*sin(rads) + b[i]*cos(rads);
	}
}

void display_square()
{

	for(i = 0; i < 4; i++)
	{
		if(i != 3)
			line(a[i], b[i], a[i+1], b[i+1]);
		else
			line(a[i], b[i], a[0], b[0]);
	}
}

void scale()
{
	for(i = 0; i < 4; i++)
	{
		a[i] = a[i] * scalex;
		b[i] = b[i] * scaley;
	}
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

  	// (x, y) represents the upper left point
	x = 270.0; y = 290.0;

	a[0] = x; b[0] = y;
	a[1] = x + square_side; b[1] = y;
	a[2] = x + square_side; b[2] = y - square_side;
	a[3] = x; b[3] = y - square_side;

	rotx = -a[3];
	roty = -b[3];
  	// Draw original square
	display_square();

 	// Perform scaling
    	rot_translate();
	scale();
	rotation();
	rotx = -rotx; roty = -roty;
	rot_translate();
	translate();
  	// Draw scaled square using dotted lines
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF0F0);
	display_square();
	glDisable(GL_LINE_STIPPLE);

	glFlush();
}

int main(int argc, char **argv)
{

	square_side = 100;
	printf("Enter Length of the side of the square: ");
	scanf("%lf", &square_side);
	printf("Enter rotation amount in degrees: ");
	scanf("%lf", &theta);
	printf("Enter x and y translation: ");
	scanf("%lf %lf", &transx, &transy);

	scalex = 1.2;
	scaley = 1.2;
	printf("Scaling factor along both directions: ");
	scanf("%lf", &scalex);
	scaley = scalex;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutCreateWindow("SCALE");

	glClearColor(1, 1, 1, 0);
	glColor3f(0, 0, 0);
	gluOrtho2D(0, 640, 0, 480);

	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}
