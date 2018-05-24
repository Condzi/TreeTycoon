/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "GUI.hpp"

GUI::~GUI()
{
	if ( isInitialised )
		Global.Input.resetAdditionalEventDispatcher();
}

void GUI::update()
{
	if ( !isInitialised ) {
		setTarget( Global.GameWindow._getSFMLWindow() );
		auto boilerplate = [this]( sf::Event event ) {
			this->handleEvent( event );
		};

		Global.Input.setAdditionalEventDispatcher( boilerplate );
	}
}

void GUI::render( sf::RenderWindow& window )
{
	draw();
}
