/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "PlotViewScene.hpp"
#include "WorldScene.hpp"

void PlotViewScene::setPlot()
{
	plot = dynamic_cast<WorldScene*>( con::Global.SceneStack.getSceneOfTag( "World" ).value() )->selectedPlot;
}
