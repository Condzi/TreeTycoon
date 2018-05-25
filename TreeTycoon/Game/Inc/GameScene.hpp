/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "GUI.hpp"
#include "TreeInfoStorage.hpp"
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
		gui.add( exitButton );
		exitButton->connect( "pressed", []() {
			Global.ExitGame = true;
		} );

		treeInfoStorage.load();
		t = std::make_unique<Tree>( treeInfoStorage.findTree( "Apple" ).value(), gui );
		t->setPosition( { 100,100 } );
		t->clickableButton->connect( "pressed", [this]() {
			t->statistics.growingState++;
			if ( t->statistics.growingState == 3 )
				t->statistics.growingState = 0;

			t->updateVisualRepresentation();
		} );
	}

private:
	GUI gui;
	TreeInfoStorage treeInfoStorage;
	std::unique_ptr<Tree> t;
};