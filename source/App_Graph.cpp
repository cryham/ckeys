#include "App.h"
#include "Util.h"


//  Graphics draw
///-----------------------------------------------------------------------------
void App::Graph()
{
	//  background
	pWindow->clear(sf::Color(6,5,20));

	if (set.bFps)
	{
		Clr(155,215,255);
		str =  "Fps: " + f2s(1/dt,1,3);
		Txt(set.xwSize-120, 2/*set.ywSize - set.iFontH-2*/);
	}

	//  draw keyboard  ----
	const float sc = set.fScale;
	if (set.bLayout)
	for (auto& k : keys.keys)
	{
		int x = k.x * sc + (set.bList ? 190 : 0), y = k.y * sc,
			x2 = x + k.w * sc, y2 = y + k.h * sc;
		//if (set.bList)  x += 190;

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
		text.setCharacterSize(k.sc * sc);  //-
		Txt(x + 4, y + 4);
	}


	//  keys pressed list  ----
	if (!set.bList)  return;

	#ifdef _WIN32
	text.setCharacterSize(set.iFontH);
	int x = 10, y = 10;
	char s[200];

	//  header
	Clr(110,140,170);
	str = "VK  SC  ext  Name";
	Txt(x,y);

	y += set.iFontH + 8;
	Clr(140,210,255);

	//  list
	sf::Lock(keys.mutex);
	for (auto& kc : keys.keyCodes)
	{
		sprintf(s, "%0X  %0X  %d", kc.vk, kc.sc, kc.ext);
		std::string sk = keys.vk2str[kc.vk];
		//sk = replK(sk, "N_", "Num ");
		if (sk.length() > 2 && sk[0]=='N' && sk[1]=='_')
			sk = "Num " + sk.substr(2);
		str = s;  str += "  " + sk;

		Txt(x,y);
		y += set.iFontH + 2;
	}
	#endif
}
