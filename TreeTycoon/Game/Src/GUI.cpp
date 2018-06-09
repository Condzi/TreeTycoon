/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "GUI.hpp"

GUI::GUI()
{
	setTarget( Global.GameWindow );
	auto boilerplate = [this]( sf::Event event ) {
		this->handleEvent( event );
	};

	Global.Input.setAdditionalEventDispatcher( boilerplate );
}

GUI::~GUI()
{
	Global.Input.resetAdditionalEventDispatcher();
}

void GUI::render( sf::RenderWindow& window )
{
	draw();
}
