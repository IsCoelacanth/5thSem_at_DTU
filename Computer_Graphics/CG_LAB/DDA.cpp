#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <iostream>
#define round(a) ((int)(a+0.5))
using namespace std;

int sign(int x)
{
	if (x==0)
		return 0;
	else
		return x<0? -1:1;
}

void DDA(int x1, int x2, int y1, int y2)
{
	// int x = x1, y = y1;
	int gd=DETECT,gm; 
	initgraph(&gd,&gm,NULL);
	int dx = abs(x2-x1);
	int dy = abs(y2-y1);
	int len = dx>dy? dx:dy;
	float delx = (x2-x1)/len;
	float dely = (y2-y1)/len;
	float x = x1, y = y1;
	x = x + 0.5*sign(dx);
	y = y + 0.5*sign(dy);
	putpixel(x,y,7);
	while(len--)
	{
		putpixel(round(x),round(y),7);
		x = x+delx;
		y = y+dely;
	}
	getch();
	closegraph();
}


int main()
{
	int x1,x2,y1,y2;
	printf("Enter the start and end points:\n(x1,y1),(x2,y2)\n");
	cin>>x1>>y1;
	cin>>x2>>y2;
	DDA(x1,x2,y1,y2);
	return 0;
}