#pragma once
#include "AppDraw.h"
#include "Settings.h"
#include "Keyboard.h"


class App : public AppDraw
{
public:
	//  main
	//--------------------------
	App();
	bool Init();
	void Resize(int x, int y);

	bool KeyDown(const sf::Event::KeyEvent& key);
	void Graph();  // draw graphics
	void Gui();   // draw Gui


	//  gui util  -----
	void SetupGuiClr();
	void Sep(int y);  // dummy separator
	void Line(bool dark = false);  //--

	Settings set;

	Keys keys;
};
