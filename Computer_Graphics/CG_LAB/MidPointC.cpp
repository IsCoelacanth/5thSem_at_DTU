#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
using namespace std;


GLint Xc, Yc, R;

struct pts
{
	GLint X, Y, R;
};

void initpt(pts &p)
{
	p.X = p.Y = p.R = 0;
}

void incX(pts &p)
{
	p.X++;
}

void decY(pts &p)
{
	p.Y--;
}

void setdata()
{
	printf("Enter X, Y and Radius\n");
	cin>>Xc>>Yc>>R;
}

void setpX(GLint XCv, GLint yCv)
{
	glBegin (GL_POINTS);
		glVertex2i(XCv,yCv);
	glEnd();
}

void setCords(pts &p, GLint xCv, GLint yCv)
{
	p.X = xCv;
	p.Y = yCv;
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
	    initpt(cpt);
		GLint p = 1-R;

		setCords(cpt,0,R);
		cirPlotPts(Xc,Yc,cpt);

		while(cpt.X < cpt.Y)
		{
			incX(cpt);
			if(p < 0)
				p += 2*cpt.X + 1;
			else
			{
				decY(cpt);
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