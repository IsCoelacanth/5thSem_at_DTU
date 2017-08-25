#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <iostream>
using namespace std;

void Bline(int x1, int x2, int y1, int y2)
{
	int x = x1, y = y1;
	int gd=DETECT,gm; 
	initgraph(&gd,&gm,"");
	// putpixel(x1,y1,7);
	int dx = abs(x2-x1);
	int dy = abs(y2-y1);
	int P = 2*dy-dx;
	int points = dx;
	while(points--)
	{
		putpixel(x,y,7);
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
	getch();
	closegraph();
}


int main()
{
	int x1,x2,y1,y2;
	printf("Enter the start and end points:\n(x1,y1),(x2,y2)\n");
	cin>>x1>>y1;
	cin>>x2>>y2;
	Bline(x1,x2,y1,y2);
	return 0;
}