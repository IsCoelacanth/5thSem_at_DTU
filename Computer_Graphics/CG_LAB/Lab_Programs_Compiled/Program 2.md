# <center><u>Program 2</u></center>
### AIM: To write a C program to implement the Bresenham line drawing algorithm.

### Description of Aim & Related Theory:
- #### Line Drawing Algorithm:  
  - A straight-line segment in a scene is defined by the coordinate positions for the
    endpoints of the segment.  
    - To display the line on a raster monitor, the graphics system
      must first project the endpoints to integer screen coordinates and determine
      the nearest pixel positions along the line path between the two endpoints.   
    - Then the line color is loaded into the frame buffer at the corresponding pixel coordinates.  
    - Reading from the frame buffer, the video controller plots the screen pixels. This
      process digitizes the line into a set of discrete integer positions that, in general,
      only approximates the actual line path
- #### The Bresenham Algorithm:  
    - an accurate and efficient raster line-generating algorithm, developed by Bresenham, that uses only incremental integer calculations. In addition, Bresenham’s line algorithm can be adapted to display circles and other curves. 

    - The basic principle is to find the optimum raster location to represent the straight line. To accomplish this, the algorithm always increments either x or y by one unit based on the flow of the line.  

    - Once that is done, the increment in other variable is found on the basis of the distance between the actual line location and the nearest pixel. this is called the <i>Decision variable</i>.  

    -  Sampling at unit x intervals, we need to decide which of two possible pixel positions is closer to the line path at each sample step.

    - To illustrate Bresenham’s approach, we first consider the scan-conversion process for lines with positive slope less than 1.0. Pixel positions along a line path are then determined by sampling at unit x intervals.

    - Starting from the left endpoint (x0, y0) of a given line, we step to each successive column (x position) and plot the pixel whose scan-line y value is closest to the line path

    - The Kth step represents the Kth point to be plotted. Next we need to check which is picked (Xk+1,Yk) or (Xk+1, Yk+1).

    - At sampling position Xk + 1, we label vertical pixel separations from the mathematical line path as d1 and d2. The y coordinate on the mathematical line at pixel column position Xk + 1 is calculated as

      <center>y = m(xk + 1) + b</center>

      Then, <center> d1 = m(Xk + 1) + b − Yk</center>

      and, <center> d2 = Yk + 1 − m(Xk + 1) − b</center>

    - To determine which of the two pixels is closest to the line path, we can set up an efficient test that is based on the difference between the two pixel separations as follows:

      <center> d2-d1 = 2m(xk + 1) − 2yk + 2b − 1</center>

      <center> Pk = 2δy · xk − 2δx · yk + c</center>

      and, <center> Pk+1 = Pk + 2δy − 2δx(yk+1 − yk)</center>

      initially P0 is <center>p0 = 2δy − δx<center>

    - Using these parameters a line is plotted for δx points.

    ​    
---

### Algorithm:
``` psuedo
1. Input the two line endpoints and store the left endpoint in (x0, y0).
2. Set the color for frame-buffer position (x0, y0); i.e., plot the first point.
3. calculate δx, δy, 2δy and 2δy-δx
4. obtain P0 as follows:
5. 	P0 = 2δy - δx
6. 	δx = |X2-X1|
7. 	δy = |Y2-Y1|
8. At each xk along the line, starting at k = 0, perform the following test:
9. 	if(Pk < 0):
10. 		next_point = (Xk+1,Yk)
11. 		Pk+1 = Pk + 2δy
12.	else:
13. 		next_point = (Xk+1,Yk+1)
14.			Pk+1 = Pk + 2δy -2δx
15. Repeat lines 9-14 for δx-1 times.
```
---
### Code:    
``` cpp
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
```
---
### Results and outputs:  
the command line inputs.  

![Output CLI](H:\College stuff\College Stuff.Academic\College Stuff.Academic.Semesters\College.Stuff.Academic.Semesters.YEAR_3\SEM 5\Computer_Graphics\CG_LAB\Outputs\BHM_CLI.png)   
The generated line.   
![Output GPH](H:\College stuff\College Stuff.Academic\College Stuff.Academic.Semesters\College.Stuff.Academic.Semesters.YEAR_3\SEM 5\Computer_Graphics\CG_LAB\Outputs\BHM_GPH.png)  

---
### Findings and Learnings:
1. The Bresenham Algorithm only uses integers and operations on them, therefore it is much faster and precise.  
2. As there is no rounding function there's not scope for the line to move away from the actuacl line.
4. Compared to DDA it's a faster increment algorithm. 

---
