/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "GUI.hpp"
#include "TreeInfoStorage.hpp"

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
		sprite.setTexture( Global.Assets.Texture.get( treeInfoStorage.findTree( "Apple" ).value().textureName ) );
		sprite.setScale( 3, 3 );
	}

private:
	GUI gui;
	TreeInfoStorage treeInfoStorage;
	Sprite sprite;
};