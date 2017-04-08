#pragma once
#include <SFML/Config.hpp>

namespace sf {  class Window;  }


//  App Settings
//------------------------------------------------
class Settings
{
public:
	const static int ver = 50;  // version

	//  main  -----
	Settings();
	void Default();

	bool Load(), Save();


	//  dimensions  -----
	int   iFontH = 18;      // font height in list
	int   iFontGui = 17;    // font height for Gui

	int   iCombo = 0;       // combo pick id


	//  window  -----
	int xwPos = 0, ywPos = 0;
	int xwSize = 1024, ywSize = 768;
	void GetWndDim(sf::Window* wnd);

	bool escQuit = false;

	char pathSet[260];
};
