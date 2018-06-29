/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "PlotRenderingSystem.hpp"

class PlotViewScene final :
	public con::Scene
{
public:
	Plot* plot = nullptr;

	void onPush() override
	{
		loadGui();
		plot = GlobalGameData.CurrentPlot;
		tag = con::ConvertTo<std::string>( "PlotView(", plot->getInfo().name, ")" );
		addSystem<PlotRenderingSystem>( 0 );

		if ( static bool spawned = false; !spawned ) {
			spawned = true;
			for ( size_t y = 0; y < 12; y++ )
				for ( size_t x = 0; x < 12; x++ ) {
					plot->spawnTree( std::hash<std::string>{}( "Apple" ), { x,y } ).value()->stats.growingState = con::Random( 0, 2 );
				}
		}
	}

private:
	void loadGui()
	{
		auto& gui = con::Global.GUI;
		gui.removeAllWidgets();
		gui.loadWidgetsFromFile( constants::PLOT_VIEW_GUI_PATH );

		gui.get( "button_exit" )->connect( "pressed", []() {
			con::Global.ExitGame = true;
		} );

		gui.get( "button_world" )->connect( "pressed", []() {
			GlobalGameData.CurrentPlot = nullptr;
			con::Global.SceneStack.pop();
		} );
	}
};