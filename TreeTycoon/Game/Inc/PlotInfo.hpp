/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

struct PlotInfo final
{
	std::string name;
	size_t nameHash = 0;
	int16_t emptyPrice = 0;
	int16_t sizeX = 0;
	int16_t sizeY = 0;
};