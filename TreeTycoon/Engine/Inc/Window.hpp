/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Debug.hpp"

namespace con::priv
{
class Window final :
	public ILogger
{
public:
	void _create( const Vec2u& size, uint32_t fps );
	sf::RenderWindow& _getSFMLWindow();
	void _pollEvents();
	void setTitle( const std::string& title );
	bool hasFocus() const;
	Vec2f convertAbsoluteToPixel( const Vec2f& absolute );
	Vec2f convertPixelToAbsolute( const Vec2f& pixels );

private:
	sf::RenderWindow window;

	std::string loggerName() const override
	{
		return "Window";
	}
};
}