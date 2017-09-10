#include <GL/glut.h>
#include <stdio.h>

inline int round(float a) {return int(a+0.5);}

int Xc, Yc, Rx, Ry;

void setdata()
{
	printf("Enter The Center Xc, Yc\n");
	scanf("%d %d",&Xc,&Yc);
	printf("Enter the two radii\n");
	scanf("%d %d",&Rx,&Ry);
}

void setpX(GLint XCv, GLint yCv)
{
	glBegin (GL_POINTS);
		glVertex2i(XCv,yCv);
	glEnd();
}



void ElipPlotPts(GLint X, GLint Y, GLint x, GLint y)
{
	setpX(X+x, Y+y);
	setpX(X-x, Y+y);
	setpX(X+x, Y-y);
	setpX(X-x, Y-y);
}

void ElipMidPointHc()
{
    int Rx2 = Rx * Rx;
    int Ry2 = Ry * Ry;
    int Trx = 2*Rx2;
    int Try = 2*Ry2;
    int p;
    int x = 0;
    int y = Ry;
    int px = 0;
    int py = Trx * y;
    ElipPlotPts(Xc,Yc,x,y);
    //Region 1
    p = round(Ry2 + 0.25*Rx2 - (Ry*Rx2));
    while(px < py)
    {
    	x++;
    	px += Try;
    	if(p<0)
    	{
    		p += Ry2 + px;
    	}
    	else
    	{
    		y--;
    		py -= Trx;
    		p += Try + px - py;
    	}
    	printf("X = %d, Y = %d\n",x,y );
    	ElipPlotPts(Xc,Yc,x,y);
    }
    //Region 2;

    p = round(Ry2 * (x+0.5)*(x+0.5)+Rx2 * (y-1)*(y-1) - Rx2*Ry2);
    while(y > 0)
    {
    	y--;
    	py -= Trx;
    	if (p > 0)
    	{
    		p += Rx2 - py;
    	}
    	else
    	{
    		x++;
    		px += Try;
    		p += Rx2 - py + px;
    	}
    	printf("X = %d, Y = %d\n",x,y );
    	ElipPlotPts(Xc,Yc,x,y);
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
	glutCreateWindow("MidPointElip");
	glClearColor(255,255,255,0.f);
	glColor3f(0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(ElipMidPointHc);
	gluOrtho2D(640,0,640,0);
	glutMainLoop();
	return 0;
}