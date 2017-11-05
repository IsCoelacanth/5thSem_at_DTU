# <center><u>Program 6</u></center>
### AIM: To write a C program to implement boundary fill polygon filling algorithm.

### Description of Aim & Related Theory:

- #### The Flood Fill Algorithm:  
    + The boundary fill algorithm works as its name. This algorithm picks a point inside an object and starts to fill until it hits the boundary of the object. The color of the boundary and the color that we fill should be different for this algorithm to work. In this algorithm, we assume that color of the boundary is same for the entire object. The boundary fill algorithm can be implemented by 4-connected pixels or 8-connected pixels.

---

### Algorithm:
1. BoundFill(X, Y, fill_color, bound_color):
2. ​    if (!(get_pixel(X,Y) == bound_color || get_pixel(X,Y) == fill_color)):
3. ​        put_pixel(X,Y,new_color)
4. ​        BoundFill(X-1, Y, fill_color, bound_color)
5. ​        BoundFill(X+1, Y, fill_color, bound_color)
6. ​        BoundFill(X, Y-1, fill_color, bound_color)
7. ​        BoundFill(X, Y+1, fill_color, bound_color)
8. ​    return

---
### Code:    
``` cpp
#include <math.h>
#include <GL/glut.h>
struct Point {
	GLint x;
	GLint y;
};
struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}
Color getPixelColor(GLint x, GLint y) {
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}
void setPixelColor(GLint x, GLint y, Color color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
void BoundaryFill(int x, int y, Color fillColor, Color boundaryColor) {
	Color currentColor = getPixelColor(x, y);
	if (currentColor.r != boundaryColor.r && currentColor.g != boundaryColor.g && currentColor.b != boundaryColor.b) {
		setPixelColor(x, y, fillColor);
		BoundaryFill(x + 1, y, fillColor, boundaryColor);
		BoundaryFill(x - 1, y, fillColor, boundaryColor);
		BoundaryFill(x, y + 1, fillColor, boundaryColor);
		BoundaryFill(x, y - 1, fillColor, boundaryColor);
	}
}
void onMouseClick(int button, int state, int x, int y)
{
	Color fillColor = { 1.0f, 0.0f, 0.0f }; // red color will be filled
	Color boundaryColor = { 0.0f, 0.0f, 0.0f }; // black- boundary
	Point p = { 321, 241 }; // a point inside the circle
	BoundaryFill(p.x, p.y, fillColor, boundaryColor);
}
void draw_circle(Point pC, GLfloat radius) {
	GLfloat step = 1 / radius;
	GLfloat x, y;
	for (GLfloat theta = 0; theta <= 360; theta += step) {
		x = pC.x + (radius * cos(theta));
		y = pC.y + (radius * sin(theta));
		glVertex2i(x, y);
	}
}
void display(void) {
	Point pt = { 320, 240 };
	GLfloat radius = 20;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	draw_circle(pt, 50);
	glEnd();
	glFlush();

}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open GL");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}
```
---
### Results and outputs:  
the command line inputs.     

before coloring :  
![Output GPH](../Outputs/bf_bc.png)  
after coloring:  
![Output GPH](../Outputs/bf_ac.png)  

---
### Findings and Learnings:
1. Boundary fill algorithm is for filling polygons. It's a basic recursion algorithm and requires a large stack for bigger polygons. For this reason it is generally not implemented as is. 
2. Implemented flood fill algorithm using OpenGL in C++. 

---
