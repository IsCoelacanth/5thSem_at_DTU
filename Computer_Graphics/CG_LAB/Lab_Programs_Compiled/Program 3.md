# <center><u>Program 3</u></center>
### AIM: To write a C program to implement the Mid Point Circle Algorithm.

### Description of Aim & Related Theory:
- #### Circles in Computer Graphics: 
    - Just like lines, circles are another primitive shape used in computer graphics.
    - A circle is defined as the set of points that are all at a given distance r from a center position (xc , yc ). For any circle point (x, y), this distance relationship is expressed by the Pythagorean theorem in Cartesian coordinates as:  
    <center>(x − xc)2 + (y − yc)2 = r 2</center>
    - We could use this equation to calculate the position of points on a circle circumference by stepping along the x axis in unit steps from xc −r to xc +r and calculating the corresponding y values at each position as:
    <center>y = yc ± root(r 2 − (xc − x)2)</center>
    - However, this is not the best method for generating a circle. One problem with this approach is that it involves considerable computation at each step. Moreover, the spacing between plotted pixel positions is not uniform.  
    - Alternativly one could use the polar coordinates, but yet again they come at a higher computational cost, Thus more efficient algorithms have been designed to draw circles.
    .
    
    
- #### The Mid Point Circle Drawing Algorithm: 
    - Bresenham’s line algorithm for raster displays is adapted to circle generation by setting up decision parameters for finding the closest pixel to the circumference at each sampling step 
    - The circle equation nonlinear, so square-root evaluations would be required to compute pixel distances from a circular path. Bresenham’s circle algorithm avoids these square-root calculations by comparing the squares of the pixel separation distances.
    - it is possible to perform a direct distance comparison without a squaring operation. The basic idea in this approach is to test the halfway position between two pixels to determine if this midpoint is inside or outside the circle boundary. This method is applied more easily to other conics; and for an integer circle radius, the midpoint approach generates the same pixel positions as the
Bresenham circle algorithm.
	- To apply the mid point algorithm we define the circle equation as :
	<center>fcirc(x, y) = x^2 + y^2 − r^2</center>
    - the relative position of any point (x, y) can be determined by checking the sign of the circle function as follows:
    ```
    		    < 0 if(x,y) is inside the boundary
    Fcirc = { = 0 if(x,y) is on the boundary
                > 0 if(x,y) is outside the boundary
    ```
    -Our decision parameter is the circle function evaluated at the midpoint between these two pixels:
    <center>Pk = (xk + 1)^2 + (yk − 1/2)^2 − r^2</center>
    - If pk < 0, this midpoint is inside the circle and the pixel on scan line yk is closer to the circle boundary. Otherwise, the midposition is outside or on the circle boundary, and we select the pixel on scan line yk − 1.
    - The initial decision parameter is obtained by evaluating the circle function at the start position (x0, y0) = (0, r ):
    <center>p0 = 5/4 − r</center>
    - For the K+1th step we get Pk+1 as:
     <center>pk+1 = pk + 2(xk + 1) + (y^2k+1 − y^2k) − (yk+1 − yk) + 1
     > yk+1 is either Yk or Yk-1
    - As in Bresenham’s line algorithm, the midpoint method calculates pixel positions along the circumference of a circle using integer additions and subtractions, assuming that the circle parameters are specified in integer screen coordinates. 
---

### Algorithm:
``` psuedo
1. Input radius r and circle center (xc , yc )
2. Set the coordinates for first point as:
3. 	(X0,Y0) = (0,r)
4. Calculate the initial value of the decision parameter as:
5. 	P0 = 5/4 - r
6. At each xk position, starting at k = 0, perform the following test:
7. if(Pk < 0):
8. 	next_point = (Xk+1,Yk)
9. 	Pk+1 = Pk + 2Xk+1 + 1
10. else:
11.	next_point = (Xk+1, Yk-1)
12.	Pk+1 = Pk + 2Xk+1 + 1 - 2Yk+1
13. //2xk+1 = 2xk + 2 and 2yk+1 = 2yk − 2.
14. Determine symmetry points in the other seven octants.
15. Move each calculated pixel position (x, y) onto the circular path centered at (xc , yc ) and plot the coordinate values as follows:
16. 	x = x + Xc
17. 	y = y + Yc
18. repeat Lines 6-17 until x>=y

```
---
### Code:    
``` cpp
#include <GL/glut.h>
#include <stdio.h>
int Xc, Yc, R;

struct pts
{
	GLint X, Y, R;
};
typedef pts pts;

void initpt(pts *p)
{
	p->X = p->Y = p->R = 0;
}

void incX(pts *p)
{
	p->X++;
}

void decY(pts *p)
{
	p->Y--;
}

void setdata()
{
	printf("Enter X, Y and Radius\n");
	scanf("%d %d %d",&Xc,&Yc,&R);
}

void setpX(GLint XCv, GLint yCv)
{
	glBegin (GL_POINTS);
		glVertex2i(XCv,yCv);
	glEnd();
}

void setCords(pts *p, GLint xCv, GLint yCv)
{
	p->X = xCv;
	p->Y = yCv;
}

void cirPlotPts(GLint X, GLint Y, pts circ)
{
	setpX(X+circ.X, Y+circ.Y);
	setpX(X-circ.X, Y+circ.Y);
	setpX(X+circ.X, Y-circ.Y);
	setpX(X-circ.X, Y-circ.Y);
	setpX(X+circ.Y, Y+circ.X);
	setpX(X-circ.Y, Y+circ.X);
	setpX(X+circ.Y, Y-circ.X);
	setpX(X-circ.Y, Y-circ.X);

}

void CircleMidPointHc()
	{
	    pts cpt;
	    initpt(&cpt);
		GLint p = 1-R;

		setCords(&cpt,0,R);
		cirPlotPts(Xc,Yc,cpt);

		while(cpt.X < cpt.Y)
		{
			incX(&cpt);
			if(p < 0)
				p += 2*cpt.X + 1;
			else
			{
				decY(&cpt);
				p += 2*(cpt.X - cpt.Y) + 1;
			}
			cirPlotPts(Xc,Yc,cpt);
		}
		glFlush();
		glutSwapBuffers();
	}

int main(int argc, char** argv)
{
	setdata();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640,640);
	glutCreateWindow("MidPointCirc");
	glutDisplayFunc(CircleMidPointHc);
	gluOrtho2D(640,0,640,0);
	glutMainLoop();
	return 0;
}
}
```
---
### Results and outputs:  
the command line inputs.  

![Output CLI](/mnt/40D2F30DD2F305C6/College stuff/College Stuff.Academic/College Stuff.Academic.Semesters/College.Stuff.Academic.Semesters.YEAR_3/SEM 5/Computer_Graphics/CG_LAB/Outputs/MPC_CLI.png)   
The generated line.   
![Output GPH](/mnt/40D2F30DD2F305C6/College stuff/College Stuff.Academic/College Stuff.Academic.Semesters/College.Stuff.Academic.Semesters.YEAR_3/SEM 5/Computer_Graphics/CG_LAB/Outputs/MPC_GPH.png)  

---
### Findings and Learnings:
1. The midpoint method is used for deriving efficient scan-conversion algorithms to draw geometric curves on raster displays.  
2. The method is general and is used to transform the nonparametric equation f(x,y) = 0, which describes the curve, into an algorithms that draws the curve.
4. time consumption is high.
5. the distance between the pixels is not equal so we wont get smooth circle. 

---
