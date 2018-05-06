/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Game.hpp"
#include "Drawable.hpp"

int main()
{
	con::RectangleShape rect;
	rect.setFillColor( sf::Color{ 155,155,155 } );
	rect.setSize( { 400,300 } );
	rect.setOrigin( 200, 150 );
	rect.setPosition( 400, 300 );

	con::Global.Game.run();
}