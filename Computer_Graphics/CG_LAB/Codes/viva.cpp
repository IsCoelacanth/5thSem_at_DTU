#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> point;

point p1;
point p2;
point p3;
point p4;
point c;
int r;

void getdata()
{
	cout<<"Enter points of rectangle : x1, y1 :"<<endl;
	cin>>p1.first;
	cin>>p1.second;
	cout<<"Enter points of rectangle : x2, y2 :"<<endl;
	cin>>p2.first;
	cin>>p2.second;
	cout<<"Enter points of rectangle : x3, y3 :"<<endl;
	cin>>p3.first;
	cin>>p3.second;
	cout<<"Enter points of rectangle : x4, y4 :"<<endl;
	cin>>p4.first;
	cin>>p4.second;

	cout<<"Enter radius of circle : "<<endl;
	cin>>r;
}

void setpX(GLint XCv, GLint yCv)
{
	glBegin (GL_POINTS);
		glVertex2i(XCv,yCv);
	glEnd();
}

void draw_circle() {
	GLint step = 1 / r;
	GLint x, y;
	for (GLint theta = 0; theta <= 360; theta += step) {
		x = c.first + (r * cos(theta));
		y = c.second + (r * sin(theta));
		glVertex2i(x,y);
	}
}


void DDA(point p1, point p2)
{
	float dx = p2.first-p1.first;
	float dy = p2.second-p1.second;
	float len = abs(dx) > abs(dy) ? abs(dx) : abs(dy) ; 
	float delx = dx/(float)len;
	float dely = dy/(float)len;
	float x = p1.first, y = p1.second;
	// x = x + 0.5*sign(dx);
	// y = y + 0.5*sign(dy);
	glVertex2i(x,y);
	while(len--)
	{
		glVertex2i(round(x),round(y));
		x = x+delx;
		y = y+dely;
	}
}

struct pts
{
	GLint X, Y, R;
};

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

void setCords(pts *p, GLint xCv, GLint yCv)
{
	p->X = xCv;
	p->Y = yCv;
}

void cirPlotPts(GLint X, GLint Y, pts circ)
{
	glVertex2i(X+circ.X, Y+circ.Y);
	glVertex2i(X-circ.X, Y+circ.Y);
	glVertex2i(X+circ.X, Y-circ.Y);
	glVertex2i(X-circ.X, Y-circ.Y);
	glVertex2i(X+circ.Y, Y+circ.X);
	glVertex2i(X-circ.Y, Y+circ.X);
	glVertex2i(X+circ.Y, Y-circ.X);
	glVertex2i(X-circ.Y, Y-circ.X);

}

void CircleMidPointHc()
{
    pts cpt;
    initpt(&cpt);
	GLint p = 1-r;

	setCords(&cpt,0,r);
	cirPlotPts(c.first,c.second,cpt);

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
		cirPlotPts(c.first,c.second,cpt);
	}
}

void display()
{
	while(1)	//draw rectangle
{	c.first = p1.first+r;
	c.second = p1.second+r;	
	for(int i = c.first; c.first <= p2.first-r;i++){
		// for (int j = 0; j < 10000000;j++);
		glClearColor(255,255,255,0.f);	
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glBegin(GL_POINTS);
			DDA(p1,p2);
			DDA(p2,p3);
			DDA(p3,p4);
			DDA(p4,p1);
			c.first++;
		CircleMidPointHc();
	}
	for(int i = c.second; c.second <= p3.second-r;i++){
		// for (int j = 0; j < 10000000;j++);
		glClearColor(255,255,255,0.f);	
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glBegin(GL_POINTS);
			DDA(p1,p2);
			DDA(p2,p3);
			DDA(p3,p4);
			DDA(p4,p1);
			c.second++;
		CircleMidPointHc();
	}
	for(c.first; c.first >= p4.first+r;){
		// for (int j = 0; j < 10000000;j++);
		glClearColor(255,255,255,0.f);	
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glBegin(GL_POINTS);
			DDA(p1,p2);
			DDA(p2,p3);
			DDA(p3,p4);
			DDA(p4,p1);
			c.first--;
		CircleMidPointHc();
	}
	for(c.second; c.second >= p1.second+r;){
		// for (int j = 0; j < 10000000;j++);
		glClearColor(255,255,255,0.f);	
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glBegin(GL_POINTS);
			DDA(p1,p2);
			DDA(p2,p3);
			DDA(p3,p4);
			DDA(p4,p1);
			c.second--;
		CircleMidPointHc();
	}

	c.first = p1.first-r;
	c.second = p1.second-r;	
	for(int i = c.first; c.first <= p2.first+r;i++){
		// for (int j = 0; j < 10000000;j++);
		glClearColor(255,255,255,0.f);	
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glBegin(GL_POINTS);
			DDA(p1,p2);
			DDA(p2,p3);
			DDA(p3,p4);
			DDA(p4,p1);
			c.first++;
		CircleMidPointHc();
	}
	for(int i = c.second; c.second <= p3.second+r;i++){
		// for (int j = 0; j < 10000000;j++);
		glClearColor(255,255,255,0.f);	
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glBegin(GL_POINTS);
			DDA(p1,p2);
			DDA(p2,p3);
			DDA(p3,p4);
			DDA(p4,p1);
			c.second++;
		CircleMidPointHc();
	}
	for(c.first; c.first >= p4.first-r;){
		// for (int j = 0; j < 10000000;j++);
		glClearColor(255,255,255,0.f);	
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glBegin(GL_POINTS);
			DDA(p1,p2);
			DDA(p2,p3);
			DDA(p3,p4);
			DDA(p4,p1);
			c.first--;
		CircleMidPointHc();
	}
	for(c.second; c.second >= p1.second-r;){
		// for (int j = 0; j < 10000000;j++);
		glClearColor(255,255,255,0.f);	
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glBegin(GL_POINTS);
			DDA(p1,p2);
			DDA(p2,p3);
			DDA(p3,p4);
			DDA(p4,p1);
			c.second--;
		CircleMidPointHc();
	}


}
	glEnd();
    glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	getdata();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640,640);
	glutCreateWindow("Viva");
	glClearColor(255,255,255,0.f);
	glColor3f(0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	gluOrtho2D(640,0,640,0);
	glutMainLoop();
	return 0;
}