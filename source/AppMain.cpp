#include <SFML/Graphics.hpp>
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "AppMain.h"
#include "App.h"
using namespace sf;  using namespace ImGui::SFML;



AppMain::AppMain()
{
}

bool AppMain::Run()
{

	//  Create window
	//------------------------------------------------
	//VideoMode vm = VideoMode::getDesktopMode();
	VideoMode vm = VideoMode(800, 600);

	RenderWindow* window = new RenderWindow(
		vm, "SFML ImGui demo",  //  title
		Style::Default,  //Style::None,
		ContextSettings());

	window->setVerticalSyncEnabled(true);
	//window->setPosition(Vector2i(0,0));


	//  ImGui
	//------------------
	Init(*window);
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = 0;  io.LogFilename = 0;  // nope
	io.Fonts->ClearFonts();
	//  font
	ImFont* fnt = io.Fonts->AddFontFromFileTTF(
					  "data/DejaVuLGCSans.ttf", 18);
	Texture* fntTex = new Texture;
	createFontTexture(*fntTex);
	setFontTexture(*fntTex);


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
			ProcessEvent(e);

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
		Update(*window, time);
		app->dt = time.asSeconds();

		//  Draw
		//------------------
		app->Gui();

		window->resetGLStates();

		app->Graph();

		ImGui::Render();

		window->display();

		//Sleep(0.20f);
	}

	//  dtor
	//------------------
	ImGui::Shutdown();
	delete window;
	delete app;
	return true;
}
