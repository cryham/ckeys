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
		str =  f2s(fps,1,3);  // 1/dt
		Txt(set.xwSize - 70, 2);
	}


	//  draw keyboard
	//--------------------------------
	const float sc = set.fScale;
	const int xl = !set.bList ? 20 :  // left margin x
					set.bListSimple ? 110 : 200;
	struct rgb{
		uint8_t r,g,b;
	};
	//  [function], [pressed/normal], [rect,frame,text]
	const static rgb kc[2][2][3] = {{
		{{ 77,115,153},{204,235,255},{227,242,255}},  // cyan
		{{ 26, 51, 77},{ 51,102,153},{179,217,254}}},{
	//	{{ 95,115,163},{215,235,255},{222,242,255}},  // steel
	//	{{ 35, 51, 87},{ 82,102,163},{197,217,254}}}};
		{{105,115,163},{225,235,255},{222,242,255}},  // viol blue
		{{ 45, 51, 87},{ 92,102,163},{197,217,254}}}};
	xMax = 0;  yMax = 0;

	if (set.bLayout)
	for (auto& k : keys.keys)
	{
		int x = k.x * sc + xl, y = k.y * sc + 20,
			x2 = x + k.w * sc, y2 = y + k.h * sc;

		//  key
		int f = set.bKLL ? (k.inKll? 0: 1) :
				set.bVK ? (k.inKll? 0: 1) : 0;  // test
		int o = k.on? 0: 1;
		const rgb* c;
		c = &kc[f][o][0];  Rect( x, y, x2, y2,    c->r,c->g,c->b);
		c = &kc[f][o][1];  Frame(x, y, x2, y2, 1, c->r,c->g,c->b);
		c = &kc[f][o][2];  Clr(c->r,c->g,c->b);

		//  label
		str = set.bKLL ? k.sk : k.s;
		text.setCharacterSize(k.sc * sc);
		Txt(x + 4, y + 4);

		//  layer label
//		if (set.bL2 && k.hasL2)
		#if 0
		str = "a";
		Clr(140,250,60);
		Txt(x + 4 + 10.5f*sc, y + 4 + set.iFontH);
		#endif

		//  get max size
		if (x2 > xMax)  xMax = x2;
		if (y2 > yMax)  yMax = y2;
	}


	//  keys pressed list
	//--------------------------------
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
		{
			//  full info  vk, sc, ext
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
