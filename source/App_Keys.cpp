#include "App.h"

#define ret		 return true;


//  Key pressed
///-----------------------------------------------------------------------------
bool App::KeyDown(const sf::Event::KeyEvent& key)
{
	using namespace sf;

	switch (key.code)
	{
		//  arrows, move
		case Keyboard::Left:  ret
		case Keyboard::Right: ret
		case Keyboard::Up:	  ret
		case Keyboard::Down:  ret

		//  Esc - Close
		case Keyboard::Escape:
			pWindow->close();
			ret
	}
	ret
}
