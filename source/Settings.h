#pragma once

namespace sf {  class Window;  }


//  App Settings
//------------------------------------------------
class Settings
{
public:
	const static int ver = 70;  // version

	//  main  -----
	Settings();
	void Default();

	bool Load(), Save();

	void GetWndDim(sf::Window* wnd);


	//  dimensions  -----
	int   iFontH = 18;     // font height in list
	int   iFontGui = 17;   // font height for Gui

	int   iCombo = 0;      // layout combo, picked id

	bool  bList = true;    // show pressed list
	bool  bListSimple = true;  // show only names, or full vk,sc,ext info

	bool  bLayout = true;  // show keyboard layout
	float fScale = 1.f;    // scale layout


	//  window  -----
	int   xwPos = 0,     ywPos = 0;
	int   xwSize = 1024, ywSize = 768;

	bool  bFps = false;    // show Fps
	bool  escQuit = false;

	bool  vsync = true;    // screen advanced
	int   limitFps = 0;
	int   iAliasing = 8;

	char  pathSet[260];
};
