#include "App.h"
#include "Util.h"


//  Graphics draw
///-----------------------------------------------------------------------------
void App::Graph()
{
	//  clear screen
	//Rect(0,0, xWindow,yWindow, 0,0,0);

	//  test
	Clr(155,215,255);
	s =  "Fps: " + f2s(1/dt,1,3);
	Txt(10, 0);

}
