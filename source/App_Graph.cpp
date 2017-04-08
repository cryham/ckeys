#include "App.h"
#include "Util.h"


//  Graphics draw
///-----------------------------------------------------------------------------
void App::Graph()
{
	//  background
	pWindow->clear(sf::Color(6,5,20));

	#if 0
	Clr(155,215,255);
	str =  "Fps: " + f2s(1/dt,1,3);
	Txt(20, 70);
	#endif

	//sf::RectangleShape

	//  draw keyboard
	for (auto& k : keys.keys)
	{
		int x = k.x, y = k.y,
			x2 = x + k.w, y2 = y + k.h;

		//  key
		if (k.on)
		{	//  pressed
			Rect( x, y, x2, y2, 77,115,153);
			Frame(x, y, x2, y2, 1, 204,235,255);
			Clr(227,242,255);
		}else
		{	//  normal
			Rect( x, y, x2, y2, 26,51,77);
			Frame(x, y, x2, y2, 1, 51,102,153);
			Clr(179,217,254);
		}

		//  label
		str = k.s;
		text.setCharacterSize(k.sc);  //-
		Txt(x + 5, y + 3);
	}
}
