#pragma once
#include <string>
#include <stdint.h>
namespace sf {  class Window;  }


enum KClr
{	KC_Normal, KC_Pressed, KC_Missing, KC_Display, KC_Layer, KC_Lnum };

struct rgb
{
	uint8_t r,g,b;
};


//  App Settings
//------------------------------------------------
class Settings
{
public:
	const static int ver = 111;  // version

	const static int Lmax = 9;  // 0..8
	const static rgb
		clrKC[KC_Layer][3],  // [3] = rft  [0 rect, 1 frame, 2 text]
		clrLay[Lmax][3], clrOver;

	const rgb* getC(const KClr& kc, const int& lay, const int& rft);


	//  main  -----
	Settings();
	void Default();

	bool Load(), Save();

	void GetWndDim(sf::Window* wnd);

	bool FindData();
	std::string data;  // data dir path


	//  dimensions  -----
	int   iFontH = 18;     // font height in list
	int   iFontGui = 17;   // font height for Gui
	bool  bBold = true;    // keys font bold

	int   iCombo = 0;      // layout combo, picked id
	bool  bList = true;    // show pressed list
	bool  bListSimple = true;  // show only names, or full vk,sc,ext info
	bool  bLayout = true;  // show keyboard layout
	float fScale = 1.f;    // scale layout


	//  window  -----
	int   xwPos = 0,     ywPos = 0;
	int   xwSize = 1310, ywSize = 450;

	bool  bFps = false;    // show Fps
	bool  bInfo = true;    // keys, layers
	bool  escQuit = false;
	bool  logOut = false;

	bool  vsync = true;    // screen advanced
	int   limitFps = 0;
	int   iAliasing = 8;
	int   iSleep = 5;      // in ms

	bool  bVK = false;     // test maps
	bool  bKLL = false;
	bool  bScan = false;

	bool  bL[Lmax] = {false,};

	char  pathSet[260];


	//  GUI dimensions  const  -----
	const int xGuiSize = 600, yGuiSize = 114,
		xRWndSize = 120,
		xGui1 = 160, xGui2 = 110, xGui3 = 130;
};
