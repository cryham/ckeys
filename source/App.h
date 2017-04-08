#pragma once
#include "AppDraw.h"
#include "Settings.h"


class App : public AppDraw
{
public:
	//  main
	//--------------------------
	App();
	bool Init();

	bool KeyDown(const sf::Event::KeyEvent& key);
	void Graph();  // draw graphics
	void Gui();   // draw Gui


	//  vars
	//--------------------------
	int iFontH = 18;  // font height
	//  gui util  -----
	void SetupGuiClr();
	void Sep(int y);  // dummy separator
	void Line(bool dark = false);  //--


};
