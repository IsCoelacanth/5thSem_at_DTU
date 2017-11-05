# <center><u>Program 8</u></center>
### AIM: To write a program for Liang Barsky Line Clipping algorithm.

### Description of Aim & Related Theory:

- #### The Cohen Sutherland Line Clipping Algorithm:  
    + The Liang–Barsky algorithm uses the parametric equation of a line and inequalities describing the range of the clipping window to determine the intersections between the line and the clip window. With these intersections it knows which portion of the line should be drawn. 
    + This algorithm is significantly more efficient than Cohen–Sutherland. 
    + The idea of the Liang–Barsky clipping algorithm is to do as much testing as possible before computing line intersections.

---

### Algorithm:
1. Set tmin=0 and tmax=0
2. Calculate the values of tL, tR, tT, and tB (tvalues).
       2.1 if t < tmin or t > tmax ignore it and go to the next edge
       2.2 otherwise classify the tvalue as entering or exiting value (using inner product to classify)
       2.3 if t is entering value set tmin = t ; if t is exiting value set tmax = t
3. If tmin < tmax  then draw a line from (x1 + dx*tmin, y1 + dy*tmin) to (x1 + dx*tmax, y1 + dy*tmax)
4. If the line crosses over the window, you will see (x1 + dx*tmin, y1 + dy*tmin) and (x1 + dx*tmax, y1 + dy*tmax) are intersection between line and edge.

---
### Code:    
``` cpp
#include<GL/glut.h>

int x1=-80,x2=0,y3=-80,y2=0;
float u1=0,u2=1;
int xmin=-50,ymin=-50,xmax=50,ymax=50;
double p[4],q[4];
void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-320,320,-240,240);
}
void clip(int x1,int y1,int x2,int y2)
{
    int dx=x2-x1,dy=y2-y1,i;
    double t;
    p[0]=-dx;q[0]=x1-xmin;
    p[1]=dx;q[1]=xmax-x1;
    p[2]=-dy;q[2]=y1-ymin;
    p[3]=dy;q[3]=ymax-y1;

    for(i=0;i<4;i++)
    {
        if(p[i]==0 && q[i]<0)
            return;
        if(p[i]<0)
        {
            t=(q[i])/(p[i]);
            if(t>u1 && t<u2)
            {u1=t;}
        }
        else if(p[i]>0)
        {
            t=(q[i])/(p[i]);
            if(t>u1 && t<u2)
            {u2=t;}
        }
    }
    if(u1<u2)
    {
        x1=x1+u1*(x2-x1);
        y1=y1+u1*(y2-y1);
        x2=x1+u2*(x2-x1);
        y2=y1+u2*(y2-y1);
        glBegin(GL_LINES);
        glVertex2i(x1,y1);
        glVertex2i(x2,y2);
        glEnd();
        glFlush();
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(x1,y3);
    glVertex2i(x2,y2);
    glEnd();
    glFlush();
}
void myKey(unsigned char key,int x,int y)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(key=='c')
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_LINES);
        glVertex2i(-50,-50);
        glVertex2i(-50,50);
        glVertex2i(-50,50);
        glVertex2i(50,50);
        glVertex2i(50,50);
        glVertex2i(50,-50);
        glVertex2i(50,-50);
        glVertex2i(-50,-50);
        glEnd();
        glFlush();
        clip(::x1,y3,x2,y2);
    }


}
int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Liang-Barsky Line Clipping");
    glutDisplayFunc(display);
    glutKeyboardFunc(myKey);
    init();
    glutMainLoop();
    return 0;
}

```
---
### Results and outputs:  
the command line inputs.   

before clipping :  
![Output GPH](../Outputs/lblc_bc.png)  
after clipping:  
![Output GPH](../Outputs/lblc_ac.png)  

---
### Findings and Learnings:
1. Liang and Barsky have created an algorithm that uses floating-point arithmetic but finds the appropriate end points with at most four computations. 
2. This algorithm uses the parametric equations for a line and solves four inequalities to find the range of the parameter for which the line is in the viewport.
3. Implemented Liang Barsky Line Clipping algorithm using OpenGL in C++.

---
