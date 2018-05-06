/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

namespace con::priv
{
class Window final
{
public:
	void _create( const Vec2u& size, uint32_t fps );
	sf::RenderWindow& _getSFMLWindow();
	void _pollEvents();
	void setTitle( const std::string& title );
	bool hasFocus() const;

private:
	sf::RenderWindow window;
};
}