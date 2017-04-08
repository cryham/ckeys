#include "App.h"


//  ctor
App::App()
{

}

//  Init
//------------------------------------------------------------------
bool App::Init()
{
	SetupGuiClr();

	return true;
}


//  utils
//------------------------------------------------------------------

//  write out text
int App::Txt(int x, int y)
{
	text.setString(s);
	text.setColor(clr);
	text.setPosition(x, y);
	pWindow->draw(text);
	return text.getLocalBounds().width;  // advance x pos
}

//  fill rect
void App::Rect(int x, int y,
		  int sx, int sy,
		  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
	pBackgr->setScale(sx-x, sy-y);
	pBackgr->setPosition(x, y);
	pBackgr->setColor(sf::Color(b, g, r));
	pWindow->draw(*pBackgr);
}
