#include "App.h"
#include "Settings.h"

#define ret		 return true;


//  Key pressed
///-----------------------------------------------------------------------------
bool App::KeyDown(const sf::Event::KeyEvent& key)
{
	using namespace sf;

	switch (key.code)
	{
		//  Esc - Close
		case Keyboard::Escape:
			if (set.escQuit)  pWindow->close();
			ret
	}
	ret
}
