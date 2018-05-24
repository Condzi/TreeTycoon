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
void GameWindowClass::_create( const Vec2u& size, uint32_t fps )
{
	window.create( { size.x, size.y }, "", sf::Style::Close );
	window.setFramerateLimit( fps );
}

sf::RenderWindow& GameWindowClass::_getSFMLWindow()
{
	return window;
}

void GameWindowClass::_pollEvents()
{
	Global.Input._clearStates();
	sf::Event ev;
	while ( window.pollEvent( ev ) ) {
		if ( ev.type == sf::Event::Closed )
			Global.ExitGame = true;
		else if ( hasFocus() )
			Global.Input._dispatchEvent( ev );
	}
}

void GameWindowClass::setTitle( const std::string& title )
{
	window.setTitle( title );
}

bool GameWindowClass::hasFocus() const
{
	return window.hasFocus();
}

Vec2f GameWindowClass::convertAbsoluteToPixel( const Vec2f& absolute )
{
	const auto winSize = ConvertTo<Vec2f>( window.getSize() );

	return { winSize.x * absolute.x, winSize.y * absolute.y };
}

Vec2f GameWindowClass::convertPixelToAbsolute( const Vec2f& pixel )
{
	auto winSize = ConvertTo<Vec2f>( window.getSize() );

	return { pixel.x / winSize.x, pixel.y / winSize.y };
}
}