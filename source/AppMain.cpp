#include <SFML/Graphics.hpp>
#include "AppMain.h"
#include "App.h"


AppMain::AppMain()
{
}

bool AppMain::Run()
{

	//  Create window
	//------------------------------------------------
	//sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	sf::VideoMode vm = sf::VideoMode(600, 400);

	sf::RenderWindow* window;
	window = new sf::RenderWindow(vm,
		"SFML demo",  //  title
		sf::Style::Default,  //sf::Style::None,
		sf::ContextSettings());

	window->setVerticalSyncEnabled(true);
	//window->setPosition(sf::Vector2i(0,0));


	//  Init app
	App* app = new App();
	app->Init();


	//  Load data
	//------------------------------------------------
	sf::Font font;
	if (!font.loadFromFile("data/DejaVuLGCSans.ttf"))
		{}  //Warning("Can't load .ttf","App Run");

	sf::Texture tex;
	if (!tex.loadFromFile("data/white.png"))
		{}  //Warning("Can't load white.png","App Run");

	sf::Sprite back(tex);

	//  pass sfml vars
	app->pWindow = window;
	app->pBackgr = &back;
	app->pFont = &font;
	app->text.setFont(font);
	app->text.setCharacterSize(app->iFontH);


	//  Loop
	//------------------------------------------------
	while (window->isOpen())
	{
		//  Process events
		//------------------
		sf::Event e;
		while (window->pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::KeyPressed:
				app->KeyDown(e.key);
				break;

			case sf::Event::Closed:
				window->close();
				break;
			}
		}

		//  Draw
		//------------------
		window->clear();

		app->Graph();

		window->display();

		//sf::Sleep(0.20f);
	}

	delete window;
	delete app;
	return true;
}
