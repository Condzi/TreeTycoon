/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "GUI.hpp"
#include "Input.hpp"

namespace con::priv
{
GUIClass::GUIClass()
{
	setTarget( Global.GameWindow );
}

void GUIClass::render( sf::RenderWindow& window )
{
	draw();
}
}
