/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

struct GlobalGameDataClass final
{
	class TreeInfosStorage& TreeInfos;
	class PlotsStorage& Plots;
	class Plot* CurrentPlot = nullptr;

	GlobalGameDataClass();
};

extern GlobalGameDataClass GlobalGameData;
