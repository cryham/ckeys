#include <SFML/Graphics.hpp>
#include <SFML/System/Sleep.hpp>
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
	//  laod Settings first
	//------------------
	App* app = new App();
	app->set.Load();
	Settings& set = app->set;


	//  Create window
	//-----------------------------------------------
	sf::ContextSettings cs;
	cs.antialiasingLevel = 8;

	RenderWindow* window = new RenderWindow(
		VideoMode(set.xwSize, set.ywSize),
		"Crystal Keys",  //  title
		Style::Default,  //Style::None,
		cs);

	window->setVerticalSyncEnabled(true);
	window->setPosition(Vector2i(set.xwPos, set.ywPos));


	//  ImGui
	//------------------
	Init(*window);
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = 0;  io.LogFilename = 0;  // nope
	io.Fonts->ClearFonts();
	//  font
	ImFont* fnt = io.Fonts->AddFontFromFileTTF(
					  "data/DejaVuLGCSans.ttf", app->set.iFontGui);
	Texture* fntTex = new Texture;
	createFontTexture(*fntTex);
	setFontTexture(*fntTex);


	//  Init app
	//------------------
	Vector2u ws = window->getSize();
	app->Resize(ws.x, ws.y);
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

	//  pass to app
	app->pWindow = window;
	app->pBackgr = &back;
	app->pFont = &font;
	app->text.setFont(font);
	app->text.setCharacterSize(app->set.iFontH);


	//  Loop
	//------------------------------------------------
	Clock timer;
	const float iv = 0.2f;  // interval for fps update
	float dt_sum = 0.f;  int cnt = 0;

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
			case Event::KeyPressed:		app->KeyDown(e.key);  break;
			//case Event::KeyReleased:	app->KeyUp(e.key);  break;

			case Event::Resized:	app->Resize(e.size.width, e.size.height);  break;
			case Event::Closed:		set.GetWndDim(window);  window->close();  break;
			}
		}
		sf::Time time = timer.restart();
		Update(*window, time);

		//  dt, update fps  ----
		app->dt = time.asSeconds();
		dt_sum += app->dt;  ++cnt;
		if (dt_sum > iv)
		{
			app->fps = float(cnt) / dt_sum;
			dt_sum = 0.f;  cnt = 0;
		}

		//  Draw
		//------------------
		app->Gui();

		window->resetGLStates();

		app->Graph();

		ImGui::Render();

		window->display();

		//sleep(sf::seconds(0.05f));  // test 20 fps
	}

	//  dtor
	//------------------
	set.Save();

	ImGui::Shutdown();
	delete window;
	delete app;
	return true;
}
