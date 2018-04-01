/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window( { 800,600 }, "" );
	Event ev;

	while ( window.isOpen() ) {
		while ( window.pollEvent( ev ) )
			if ( ev.type == Event::Closed )
				window.close();

		window.clear();
		window.display();
	}
}