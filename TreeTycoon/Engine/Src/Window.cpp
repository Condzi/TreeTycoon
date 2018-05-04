/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Window.hpp"
#include "Input.hpp"

namespace con
{
inline priv::Window GameWindow{};
}

namespace con::priv
{
void Window::_create( const Vec2u& size )
{
	window.create( { size.x, size.y }, "", sf::Style::Close );
}

sf::RenderWindow& Window::_getSFMLWindow()
{
	return window;
}

void Window::_pollEvents()
{
	if ( !window.hasFocus() )
		return;

	Input._clearStates();
	sf::Event ev;
	while ( window.pollEvent( ev ) ) {
		if ( ev.type == sf::Event::Closed )
			return window.close();

		Input._dispatchEvent( ev );
	}
}

void Window::setTitle( const std::string& title )
{
	window.setTitle( title );
}
}