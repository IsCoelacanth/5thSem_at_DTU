#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
using namespace std;


GLint Xc, Yc, R;

class pts
{
	GLint X, Y, R;
public:
	pts()
	{
		X = Y = R = 0;
	}

	void setCords(GLint XCv, GLint yCv)
	{
		X = XCv;
		Y = yCv;
	}

	GLint getX()
	{
		return X;	
	}

	GLint gety()
	{
		return Y;
	}

	void incX()
	{
		X++;
	}

	void decY()
	{
		Y--;
	}
	

};

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

void cirPlotPts(GLint X, GLint Y, pts circ)
{
	setpX(X+circ.getX(),Y+circ.gety());
	setpX(X-circ.getX(),Y+circ.gety());
	setpX(X+circ.getX(),Y-circ.gety());
	setpX(X-circ.getX(),Y-circ.gety());
	setpX(X+circ.gety(),Y+circ.getX());
	setpX(X-circ.gety(),Y+circ.getX());
	setpX(X+circ.gety(),Y-circ.getX());
	setpX(X-circ.gety(),Y-circ.getX());

}

void CircleMidPointHc()
	{
	    pts cpt;
		GLint p = 1-R;

		cpt.setCords(0,R);
		cirPlotPts(Xc,Yc,cpt);

		while(cpt.getX() < cpt.gety())
		{
			cpt.incX();
			if(p < 0)
				p += 2*cpt.getX() + 1;
			else
			{
				cpt.decY();
				p += 2*(cpt.getX() - cpt.gety()) + 1;
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640,640);
	glutCreateWindow("MidPointCirc");
	glutDisplayFunc(CircleMidPointHc);
	gluOrtho2D(640,0,640,0);
	glutMainLoop();
	return 0;
}