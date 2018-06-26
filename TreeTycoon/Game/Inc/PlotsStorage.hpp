/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Plot.hpp"

class WorldScene;

class PlotsStorage final :
	public con::ILogger
{
public:
	void load( WorldScene& world );

	std::optional<Plot* const> findPlot( const std::string& name );
	std::optional<Plot* const> findPlot( size_t hash );
	std::vector<Plot*> getAllPlots();

private:
	std::vector<Plot> plots;

	std::string loggerName() const override
	{
		return "Plots Storage";
	}

	bool loadConfig( std::vector<PlotInfo>& infos );
	void initializePlots( const std::vector<PlotInfo>& infos, WorldScene& world );
};