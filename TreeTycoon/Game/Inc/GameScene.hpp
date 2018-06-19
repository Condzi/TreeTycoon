/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "GUI.hpp"
#include "TreeInfosStorage.hpp"
#include "Tree.hpp"

using namespace con;

class GameScene final :
	public Scene
{
public:
	void onPush() override
	{
		tag = "Game Scene";
		auto exitButton = tgui::Button::create( "Exit" );
		exitButton->setSize( "20%", "10%" );
		exitButton->setPosition( "40%", "45%" );
		exitButton->setTextSize( 0 );
		Global.GUI.add( exitButton );
		exitButton->connect( "pressed", []() {
			Global.ExitGame = true;
		} );
	}

private:
	TreeInfosStorage treeInfoStorage;
	std::unique_ptr<Tree> t;
};