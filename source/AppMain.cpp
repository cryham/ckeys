#include <SFML/Graphics.hpp>
#include "AppMain.h"
#include "App.h"
using namespace sf;



AppMain::AppMain()
{
}

bool AppMain::Run()
{

	//  Create window
	//------------------------------------------------
	//VideoMode vm = VideoMode::getDesktopMode();
	VideoMode vm = VideoMode(600, 400);

	RenderWindow* window = new RenderWindow(
		vm, "SFML demo",  //  title
		Style::Default,  //Style::None,
		ContextSettings());

	window->setVerticalSyncEnabled(true);
	//window->setPosition(Vector2i(0,0));


	//  Init app
	App* app = new App();
	app->Init();


	//  Load data
	//------------------------------------------------
	Font font;
	if (!font.loadFromFile("data/DejaVuLGCSans.ttf"))
		{}  //Warning("Can't load .ttf","App Run");

	Texture tex;
	if (!tex.loadFromFile("data/white.png"))
		{}  //Warning("Can't load white.png","App Run");

	Sprite back(tex);

	//  pass sfml vars
	app->pWindow = window;
	app->pBackgr = &back;
	app->pFont = &font;
	app->text.setFont(font);
	app->text.setCharacterSize(app->iFontH);


	//  Loop
	//------------------------------------------------
	Clock timer;
	while (window->isOpen())
	{
		//  Process events
		//------------------
		Event e;
		while (window->pollEvent(e))
		{
			switch (e.type)
			{
			case Event::KeyPressed:
				app->KeyDown(e.key);
				break;

			case Event::Closed:
				window->close();
				break;
			}
		}
		sf::Time time = timer.restart();
		app->dt = time.asSeconds();

		//  Draw
		//------------------
		window->clear();

		app->Graph();

		window->display();

		//Sleep(0.20f);
	}

	delete window;
	delete app;
	return true;
}
