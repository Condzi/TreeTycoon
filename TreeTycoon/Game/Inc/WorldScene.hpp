/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "TreeInfosStorage.hpp"
#include "PlotsStorage.hpp"

class WorldScene final :
	public con::Scene
{
public:
	void onPush() override
	{
		tag = "World";
		GlobalGameData.TreeInfos.load();
		GlobalGameData.Plots.load( *this );
	}

	void onUpdate() override
	{
		static Scene* lastScene = nullptr;
		if ( con::Global.SceneStack.getSceneOnTop().value_or( nullptr ) == this && lastScene != this ) {
			lastScene = this;
			loadGui();
		} else
			lastScene = con::Global.SceneStack.getSceneOnTop().value_or( nullptr );
	}

private:
	void loadGui()
	{
		auto& gui = con::Global.GUI;
		gui.removeAllWidgets();
		gui.loadWidgetsFromFile( constants::WORLD_VIEW_GUI_PATH );

		gui.get( "button_exit" )->connect( "pressed", []() {
			con::Global.ExitGame = true;
		} );

		auto& plotsList = *gui.get( "list_plots" )->cast<tgui::ListBox>();
		plotsList.removeAllItems(); // removing "placeholder"

		for ( auto* plot : GlobalGameData.Plots.getAllPlots() ) {
			auto plotName = plot->getInfo().name;
			plotsList.addItem( plotName, plotName );
		}

		plotsList.connect( "itemSelected", [&]( const sf::String& itemId ) {
			con::Global.SceneStack.push( 1 );
			GlobalGameData.CurrentPlot = GlobalGameData.Plots.findPlot( itemId ).value_or( nullptr );
		} );
	}

};
