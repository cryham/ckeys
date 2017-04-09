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

	int   iCombo = 0;      // combo pick id

	bool  bList = true;    // show pressed list
	bool  bLayout = true;  // show keyboard layout
	bool  bFps = false;    // show Fps

	float fScale = 1.f;    // scale layout


	//  window  -----
	int xwPos = 0, ywPos = 0;
	int xwSize = 1024, ywSize = 768;


	bool escQuit = false;

	char pathSet[260];
};
