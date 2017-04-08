#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class App
{
public:
	//  main
	//--------------------------
	App();

	bool Init();
	bool KeyDown(const sf::Event::KeyEvent& key);
	void Graph();  // draw graphics


	//  vars
	//--------------------------
	int iFontH = 18;  // font height


	//  sfml vars
	//--------------------------
	sf::RenderWindow* pWindow = nullptr;
	sf::Sprite* pBackgr = nullptr;

	sf::Font* pFont = nullptr;
	sf::Text text;

	sf::String s;
	sf::Color clr;


	//  sfml drawing utils

	//  set text color
	//--------------------------
	void Clr(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
	{
		clr = sf::Color(r,g,b);
	}

	//  write out text, from s
	int Text(int x, int y);

	//  fill rectangle
	void Rect(int x, int y,
			  int sx, int sy,
			  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
};
