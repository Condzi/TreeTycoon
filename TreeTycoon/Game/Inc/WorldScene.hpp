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
	TreeInfosStorage treeInfos;
	PlotsStorage plots{*this};
	Plot* selectedPlot = nullptr;

	void onPush() override
	{
		tag = "World";
		treeInfos.load();
		plots.load();
		loadGui();
	}

	void onEnable() override
	{
		loadGui();
	}

private:
	void loadGui()
	{
		auto& gui = con::Global.GUI;
		gui.loadWidgetsFromFile( constants::WORLD_GUI_PATH );

		gui.get( "button_exit" )->connect( "pressed", []() {
			con::Global.ExitGame = true;
		} );

		auto& plotsList = *gui.get( "list_plots" )->cast<tgui::ListBox>();
		plotsList.removeAllItems(); // removing "placeholder"

		for ( auto* plot : plots.getAllPlots() ) {
			auto plotName = plot->getInfo().name;
			plotsList.addItem( plotName, plotName );
		}

		plotsList.connect( "itemSelected", [&]( const sf::String& itemId ) {
			con::Global.SceneStack.disableCurrentScene();
			con::Global.SceneStack.push(1);
			selectedPlot = plots.findPlot( itemId ).value_or( nullptr );
		} );
	}

};
