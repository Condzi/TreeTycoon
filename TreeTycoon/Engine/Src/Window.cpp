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

Vec2f Window::convertAbsoluteToPixel( const Vec2f& absolute )
{
	const auto winSize = ConvertTo<Vec2f>( window.getSize() );
	Vec2f pixel{};

	if ( absolute.x > 1.0f || absolute.x < 0 )
		log( LogPriority::Error, "wrong args - invalid absolute position X: ", absolute.x, "." );
	else
		pixel.x = winSize.x * absolute.x;

	if ( absolute.y > 1.0f || absolute.y < 0 )
		log( LogPriority::Error, "wrong args - invalid absolute position Y: ", absolute.y, "." );
	else
		pixel.y = winSize.y * absolute.y;


	return pixel;
}

Vec2f Window::convertPixelToAbsolute( const Vec2f& pixel )
{
	auto winSize = ConvertTo<Vec2f>( window.getSize() );
	Vec2f abs{};

	if ( pixel.x > winSize.x || pixel.x < 0 )
		log( LogPriority::Error, "wrong args - invalid pixel X position: ", pixel.x, "/", winSize.x, "." );
	else
		abs.x = pixel.x / winSize.x;

	if ( pixel.y > winSize.x || pixel.y < 0 )
		log( LogPriority::Error, "wrong args - invalid pixel Y position: ", pixel.x, "/", winSize.x, "." );
	else
		abs.y = pixel.y / winSize.y;

	return abs;
}
}