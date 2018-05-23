/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "GUI.hpp"

using namespace con;

class GameScene final :
	public Scene
{
public:
	void onPush() override
	{
		auto exitButton = tgui::Button::create( "Exit" );
		exitButton->setSize( "20%", "10%" );
		exitButton->setPosition( "40%", "45%" );
		exitButton->setTextSize( 0 );
		gui.add( exitButton );
		exitButton->connect( "pressed", []() {
			Global.ExitGame = true;
		} );
	}

private:
	GUI gui;
};