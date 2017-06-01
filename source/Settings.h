#pragma once

namespace sf {  class Window;  }


//  App Settings
//------------------------------------------------
class Settings
{
public:
	const static int ver = 100;  // version

	//  main  -----
	Settings();
	void Default();

	bool Load(), Save();

	void GetWndDim(sf::Window* wnd);


	//  dimensions  -----
	int   iFontH = 18;     // font height in list
	int   iFontGui = 17;   // font height for Gui
	bool  bBold = false;   // keys font bold

	int   iCombo = 0;      // layout combo, picked id

	bool  bList = true;    // show pressed list
	bool  bListSimple = true;  // show only names, or full vk,sc,ext info

	bool  bLayout = true;  // show keyboard layout
	float fScale = 1.f;    // scale layout


	//  window  -----
	int   xwPos = 0,     ywPos = 0;
	int   xwSize = 1310, ywSize = 420;

	bool  bFps = false;    // show Fps
	bool  escQuit = false;

	bool  vsync = true;    // screen advanced
	int   limitFps = 0;
	int   iAliasing = 8;
	int   iSleep = 5;      // in ms

	bool  bVK = false;     // test vk map
	bool  bKLL = false;    // test kll map

	bool  bL1 = true;      // layers
	bool  bL2 = false;
	bool  bL3 = false;

	char  pathSet[260];


	//  GUI dimensions  const  -----
	const int xGuiSize = 600, yGuiSize = 114,
		xRWndSize = 120,
		xGui1 = 185, xGui2 = 110, xGui3 = 130;
};
