# <center><u>Program 7</u></center>
### AIM: To write a program for Cohen Sutherland Line Clipping algorithm.

### Description of Aim & Related Theory:

- #### The Cohen Sutherland Line Clipping Algorithm:  
    + Both endpoints are in the viewport region (bitwise OR of endpoints = 00): trivial accept.
    + Both endpoints share at least one non-visible region, which implies that the line does not cross the visible region. (bitwise AND of endpoints ≠ 0): trivial reject.
    + Both endpoints are in different regions: in case of this nontrivial situation the algorithm finds one of the two points that is outside the viewport region (there will be at least one point outside). The intersection of the outpoint and extended viewport border is then calculated (i.e. with the parametric equation for the line), and this new point replaces the outpoint. The algorithm repeats until a trivial accept or reject occurs.

---

### Algorithm:
1. Assign a region code for two endpoints of given line.
2. If both endpoints have a region code 0000 then given line is completely inside.
3. Else, perform the logical AND operation for both region codes.
    3.1 If the result is not 0000, then given line is completely outside.
    3.2 Else line is partially inside.
         3.2.1 Choose an endpoint of the line that is outside the given rectangle.
         3.2.2 Find the intersection point of the rectangular boundary (based on region code).
         3.2.3 Replace endpoint with the intersection point and update the region code.
         3.2.4 Repeat step 2 until we find a clipped line either trivially accepted or trivially rejected.
4. Repeat step 1 for other lines

---
### Code:    
``` cpp
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<iostream>

void display();
using namespace std;
float xmin=-100;
float ymin=-100;
float xmax=100;
float ymax=100;
float xd1,yd1,xd2,yd2;


void init(void)
{

    glClearColor(0.9,0.9,0.9,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300,300,-300,300);

}

int code(float x,float y)
{
    int c=0;
    if(y>ymax)c=8;
    if(y<ymin)c=4;
    if(x>xmax)c=c|2;
    if(x<xmin)c=c|1;
    return c;
}

void cohen_Line(float x1,float y1,float x2,float y2)
{
    int c1=code(x1,y1);
    int c2=code(x2,y2);
    float m=(y2-y1)/(x2-x1);
    while((c1|c2)>0)
    {
        if((c1 & c2)>0)
        {
            exit(0);
        }

        float xi=x1;float yi=y1;
        int c=c1;
        if(c==0)
        {
            c=c2;
            xi=x2;
            yi=y2;
        }
        float x,y;
        if((c & 8)>0)
        {
            y=ymax;
            x=xi+ 1.0/m*(ymax-yi);
        }
        else
        if((c & 4)>0)
        {
            y=ymin;
            x=xi+1.0/m*(ymin-yi);
        }
        else
        if((c & 2)>0)
        {
            x=xmax;
            y=yi+m*(xmax-xi);
        }
        else
        if((c & 1)>0)
        {
            x=xmin;
            y=yi+m*(xmin-xi);
        }

        if(c==c1)
        {
            xd1=x;
            yd1=y;
            c1=code(xd1,yd1);
        }

        if(c==c2)
        {
            xd2=x;
            yd2=y;
            c2=code(xd2,yd2);
        }
    }

    display();

}

void mykey(unsigned char key,int x,int y)
{
    if(key=='c')
    {  cout<<"Hello";
        cohen_Line(xd1,yd1,xd2,yd2);
        glFlush();
    }
}
void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);

    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin,ymin);
    glVertex2i(xmin,ymax);
    glVertex2i(xmax,ymax);
    glVertex2i(xmax,ymin);
    glEnd();
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(xd1,yd1);
    glVertex2i(xd2,yd2);
    glEnd();
    glFlush();


}


int main(int argc,char** argv)
{
    printf("Enter line co-ordinates:");
    cin>>xd1>>yd1>>xd2>>yd2;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Cohen Sutherland Line Clipping");
    glutDisplayFunc(display);
    glutKeyboardFunc(mykey);
    init();
    glutMainLoop();
    return 0;
}

```
---
### Results and outputs:  
the command line inputs.     

command line instructions:  

![Output GPH](H:\College stuff\College Stuff.Academic\College Stuff.Academic.Semesters\College.Stuff.Academic.Semesters.YEAR_3\SEM 5\Computer_Graphics\CG_LAB\Outputs\cslc_cli.png)

before coloring :  
![Output GPH](H:\College stuff\College Stuff.Academic\College Stuff.Academic.Semesters\College.Stuff.Academic.Semesters.YEAR_3\SEM 5\Computer_Graphics\CG_LAB\Outputs\cslc_bc.png)  
after coloring:  
![Output GPH](H:\College stuff\College Stuff.Academic\College Stuff.Academic.Semesters\College.Stuff.Academic.Semesters.YEAR_3\SEM 5\Computer_Graphics\CG_LAB\Outputs\cslc_ac.png)  

---
### Findings and Learnings:
1. The Cohen–Sutherland algorithm is a computer-graphics algorithm used for line clipping. The algorithm divides a two-dimensional space into 9 regions and then efficiently determines the lines and portions of lines that are visible in the central region of interest (the viewport).
2. The algorithm was developed in 1967 during flight-simulator work by Danny Cohen and Ivan Sutherland.
3. Implemented Cohen Sutherland Line Clipping algorithm using OpenGL in C++.

---
