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

	void onPush() override
	{
		auto& gui = con::Global.GUI;
		gui.loadWidgetsFromFile( constants::WORLD_GUI_PATH );

		gui.get( "button_exit" )->connect( "pressed", []() {
			con::Global.ExitGame = true;
		} );

		treeInfos.load();
		plots.load();

		auto& plotsList = *gui.get( "list_plots" )->cast<tgui::ListBox>();
		plotsList.removeAllItems(); // removing "placeholder"

		for ( auto* plot : plots.getAllPlots() )
			plotsList.addItem( plot->getInfo().name );
	}
};
