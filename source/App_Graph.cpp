#include "App.h"
#include "Util.h"


//  Graphics draw
///-----------------------------------------------------------------------------
void App::Graph()
{

	//  background
	pWindow->clear(sf::Color(6,5,20));

	//  Fps
	if (set.bFps)
	{
		text.setCharacterSize(set.iFontH);
		Clr(155,215,255);
		//str =  "Fps: " + f2s(1.f/dt,1,3);
		str =  "Fps: " + f2s(fps,1,3);
		Txt(set.xwSize - 120, 2);
	}


	//  draw keyboard  --------
	const float sc = set.fScale;
	const int xl = !set.bList ? 20 :  // left margin x
					set.bListSimple ? 110 : 200;

	if (set.bLayout)
	for (auto& k : keys.keys)
	{
		int x = k.x * sc + xl, y = k.y * sc + 20,
			x2 = x + k.w * sc, y2 = y + k.h * sc;

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
		text.setCharacterSize(k.sc * sc);
		Txt(x + 4, y + 4);
	}


	//  keys pressed list  --------
	if (!set.bList)  return;

	#ifdef _WIN32
	text.setCharacterSize(set.iFontH - 3);
	int x = 10, x1 = x + 95, y = 25;
	char s[200];

	//  header
	Clr(110,140,170);
	if (set.bListSimple)
	{	str = "Pressed";  x1 = x;  }
	else
		str = "VK  SC  ext  Name";
	Txt(x,y);

	text.setCharacterSize(set.iFontH);
	y += set.iFontH + 8;
	Clr(140,210,255);

	//  list
	sf::Lock(keys.mutex);
	for (auto& kc : keys.keyCodes)
	{
		if (!set.bListSimple)
		{	//  full info  vk, sc, ext
			sprintf(s, "%02X  %02X", kc.vk, kc.sc);
			str = s;
			Clr(140,210,255);  bold = false;
			Txt(x,y);

			str = i2s(kc.ext);
			Clr(110,180,235);
			Txt(x1 - 25, y);
		}

		//  key name
		std::string sk = keys.vk2str[kc.vk];

		//  replace N_ with Num
		if (sk.length() > 2)
		if (sk[0]=='N' && sk[1]=='_')
			sk = "Num " + sk.substr(2);
		if (sk[1]=='_')  // _ to space, for L_ R_
			sk[1] = ' ';
		if (sk == "Backspace")  // too long
			sk = "Backspc";

		str = sk;
		Clr(200,230,255);  bold = true;
		Txt(x1, y);
		y += set.iFontH + 2;
	}
	bold = false;
	#endif
}
