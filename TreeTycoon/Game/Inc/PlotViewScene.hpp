/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Plot.hpp"

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
	}

private:
	void loadGui()
	{
		auto& gui = con::Global.GUI;
		gui.loadWidgetsFromFile( constants::PLOT_GUI_PATH );

		gui.get( "button_exit" )->connect( "pressed", []() {
			con::Global.ExitGame = true;
		} );

		gui.get( "button_world" )->connect( "pressed", []() {
			auto& sceneStack = con::Global.SceneStack;
			sceneStack.pop();
			sceneStack.enableCurrentScene();
		} );
	}
};