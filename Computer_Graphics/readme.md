# Installing and running graphics.h on Linux

- - -

(tested on ubuntu 16.04)

1. Launch a terminal window and run the following commands:  
	* sudo apt-get install build-essential
	* sudo apt-get install aptitude
	* sudo aptitude install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev libpulse-dev libxt-dev
	* sudo apt-get install guile-1.8-dev guile-1.8-libs

	(additionally you can also install guile-2.0-dev and guile-2.0-libs)

2. Then download the library from [here](http://download.savannah.gnu.org/releases/libgraph/libgraph-1.0.2.tar.gz) and extract it and cd into the folder
	* Run the following commands:
		* ./configure
		* make
		* sudo make install
		* sudo cp /usr/local/lib/libgraph.* /usr/lib
3. Test you code :
``` cpp
#include <stdio.h>
#include <graphics.h>
int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"");
    line(1,1,255,255);
    getch();
    closegraph();
    return 0;
}
```
	Compile the code using this 
``` 
	g++ -o >name< >sourceCode.cpp< -lgraph
	./>name<
```