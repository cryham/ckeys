#include "App.h"
#include "Util.h"


//  Graphics draw
///-----------------------------------------------------------------------------
void App::Graph()
{

	//  background
	pWindow->clear(sf::Color(6,5,20));
	int yF = set.iFontH;

	//  Fps
	if (set.bFps)
	{
		text.setCharacterSize(yF);
		Clr(155,215,255);
		str =  f2s(fps,1,3);  // 1/dt
		Txt(set.xwSize - 70, 2);
	}


	//  draw keyboard
	//----------------------------------------------------------------
	const float sc = set.fScale;
	const int xl = !set.bList ? 20 :  // left margin x
					set.bListSimple ? 110 : 230;
	struct rgb{
		uint8_t r,g,b;
	};
//	ImGui::ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b)
	//  [KClr], [pressed/normal], [rect,frame,text]
	const static rgb kc[4][2][3] = {{
		{{ 77,115,153},{204,235,255},{227,242,255}},  // cyan
		{{ 26, 51, 77},{ 51,102,153},{179,217,254}}},{
		{{ 95,115,163},{215,235,255},{222,242,255}},  // steel
		{{ 35, 51, 87},{ 82,102,163},{197,217,254}}},{
		{{105,115,163},{225,235,255},{222,242,255}},  // viol blue
		{{ 45, 41,107},{112,102,193},{227,217,254}}},{
		{{ 65, 47, 32},{122,102, 83},{254,187,104}},  // orange
		{{ 65, 47, 32},{122,102, 83},{254,187,104}}}};
//		{{165,115, 63},{255,235,155},{255,242,155}},  // orange
//		{{ 95, 51, 27},{182,112, 83},{254,217,154}}}};
//		{{ 77,153,153},{204,255,255},{217,255,255}},  // cyan
//		{{ 26, 77, 77},{ 51,152,153},{179,255,255}}}};
//		{{123, 65, 25},{215,125, 35},{255,222, 42}},  // orange
//		{{ 83, 45, 25},{115, 65, 35},{155, 82, 42}}}};
	const static rgb  // layer frame
		kl2 = {60,150,20}, kl3 = {130,130,20}, kov = {220,230,240};
	xMax = 0;  yMax = 0;

	//  key under mouse, for info
	Key* km = 0;
	if (set.bBold)
		bold = true;

	if (set.bLayout)
	for (auto& k : keys.keys)
	{
		int x = k.x * sc + xl, y = k.y * sc + 20,
			x2 = x + k.w * sc, y2 = y + k.h * sc;

		//  key
		int f = k.clr, r = 1;
		if (f == KC_Normal)
		if (set.bKLL && !k.inKll ||
			set.bVK && !k.inVK)  f = KC_Missing;

		int o = k.on? 0: 1;
		bool l2 = set.bL2 && !k.strL2.isEmpty();
		bool l3 = set.bL3 && !k.strL3.isEmpty();

		//  draw  []
		const rgb* c;
		c = &kc[f][o][0];  Rect( x, y, x2, y2,    c->r,c->g,c->b);
		c = &kc[f][o][1];  Frame(x, y, x2, y2, r, c->r,c->g,c->b);
		c = &kc[f][o][2];  Clr(c->r,c->g,c->b);
		if (!k.on)
		{
			if (l2) {  c = &kl2;  Frame(x, y, x2, y2, r, c->r,c->g,c->b);  }
			if (l3) {  c = &kl3;  Frame(x, y, x2, y2, r, c->r,c->g,c->b);  }
		}
		//  mouse over
		if (xm >= x && xm <= x2 && ym >= y && ym <= y2)
		{	km = &k;
			c = &kov;  Frame(x, y, x2, y2, 1, c->r,c->g,c->b);
		}

		//  caption  ----
		str = set.bKLL ? k.sKll : k.str;
		bool ln2 = str.find("\n") != sf::String::InvalidPos;

		bool lon = !set.bL1 && (l2 || l3);
		text.setCharacterSize(k.sc * sc);
		if (!lon)  Txt(x + 4, y + 4);

		//  layer label(s)  ----
		int xl = x + 4 + (!lon && ln2 ? 18.f*sc : 0);
		int yl = y + 4 + (!lon ? yF : 0);

		if (l2)
		{	str = k.strL2;
			Clr(120,240,60);
			Txt(xl, yl);
		}
		if (l3)
		{	str = k.strL3;
			Clr(220,220,60);
			if (l2)  yl += yF;
			Txt(xl, yl);
		}

		//  get max size
		if (x2 > xMax)  xMax = x2;
		if (y2 > yMax)  yMax = y2;
	}


	//  key info
	//--------------------------------
	int x,y, x1,y1;
	//bold = true;
	text.setCharacterSize(yF-1);  yF += 4;
	x = set.xGuiSize + 30;  x1 = x + 170;
	y = set.ywSize - set.yGuiSize + 20;  y1 = y;

	if (!km)
	{	str = "Key info";// +i2s(xm)+ " "+i2s(ym);
		Clr(150,180,220);  Txt(x, y);  y += 3*yF;
	}else
	{	//  1st col  ----
		str = "Key:  " + km->str;  str.replace("\n","  ");
		Clr(190,220,250);  Txt(x, y);  y += yF;
		if (!km->strL2.isEmpty())
		{	str = "L2:  " + km->strL2;
			Clr(100,190,40);  Txt(x+9, y);  y += yF;  }
		if (!km->strL3.isEmpty())
		{	str = "L3:  " + km->strL3;
			Clr(180,180,40);  Txt(x+9, y);  y += yF;  }

		//  2nd col  ----
		str = "Kll: " + km->sKll;
		Clr(100,170,250);  Txt(x1+15, y1);  y1 += yF;
		str = "Json: " + km->sJson;
		Clr(165,165,240);  Txt(x1, y1);  y1 += yF;
		str = "Scan: " + keys.kll2scan[km->sKll];
		Clr(140,160,200);  Txt(x1-6, y1);  y1 += yF;
		str = "  VK: ";  str += km->sVK;  //km->inVK ? "1" : "0";
		Clr(140,140,180);  Txt(x1+4, y1);  y1 += yF;
	}


	//  keys pressed list
	//--------------------------------
	if (!set.bList)  return;

	#ifdef _WIN32
	text.setCharacterSize(yF - 3);
	x = 10;  x1 = x + 110;  y = 25;
	char s[200];

	//  header
	Clr(110,140,170);
	if (set.bListSimple)
	{	str = "Pressed";  x1 = x;  }
	else
		str = "VK  SC  ext  Name";
	Txt(x,y);

	text.setCharacterSize(yF);
	y += yF + 8;
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
			Clr(140,150,155);
			Txt(x1 - 25, y);
		}

		//  key name
		std::string sk = keys.vk2str[kc.vk];

		///****  replace N_ with Num
		if (sk.length() > 2)
		if (sk[0]=='N' && sk[1]=='_')
			sk = "Num " + sk.substr(2);
		if (sk[1]=='_')  // _ to space, for L_ R_
			sk[1] = ' ';
		if (sk == "Backspace")  // too long
			sk = "Backspc";
		///****

		str = sk;
		Clr(200,230,255);  bold = true;
		Txt(x1, y);
		y += yF + 2;
	}
	bold = false;
	#endif
}
