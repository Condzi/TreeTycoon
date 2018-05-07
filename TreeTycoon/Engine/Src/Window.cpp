/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "Game.hpp"

namespace con::priv
{
void Window::_create( const Vec2u& size, uint32_t fps )
{
	window.create( { size.x, size.y }, "", sf::Style::Close );
	window.setFramerateLimit( fps );
}

sf::RenderWindow& Window::_getSFMLWindow()
{
	return window;
}

void Window::_pollEvents()
{
	if ( !hasFocus() )
		return;

	Global.Input._clearStates();
	sf::Event ev;
	while ( window.pollEvent( ev ) ) {
		if ( ev.type == sf::Event::Closed )
			Global.ExitGame = true;
		else
			Global.Input._dispatchEvent( ev );
	}
}

void Window::setTitle( const std::string& title )
{
	window.setTitle( title );
}

bool Window::hasFocus() const
{
	return window.hasFocus();
}

Vec2f Window::convertAbsoluteToPixels( const Vec2f& absolute )
{
	if ( absolute.x > 1.0f || absolute.x < 0 ||
		 absolute.y > 1.0f || absolute.y < 0 ) {
		log( LogPriority::Error, "wrong args - invalid absolute position: {", absolute.x, ", ", absolute.y, "}." );
		return {};
	}

	auto winSize = ConvertTo<Vec2f>( window.getSize() );

	return { winSize.x * absolute.x, winSize.y * absolute.y };
}

Vec2f Window::convertPixelToAbsolute( const Vec2f& pixel ) 
{
	auto winSize = ConvertTo<Vec2f>( window.getSize() );

	if ( pixel.x > winSize.x || pixel.x < 0 ||
		 pixel.y > winSize.y || pixel.y < 0 ) {
		log( LogPriority::Error, "wrong args - invalid pixel position: {", pixel.x, "/", winSize.x, ", ", pixel.y, "/", winSize.y, "}." );
		return {};
	}

	return { pixel.x / winSize.x, pixel.y / winSize.y };
}
}