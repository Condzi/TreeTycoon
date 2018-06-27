/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "PlotInfo.hpp"
#include "Tree.hpp"

class WorldScene;

class Plot final
{
public:
	Plot() = default;
	Plot( WorldScene& world_, const PlotInfo& info_ );

	std::optional<Tree*> spawnTree( size_t nameHash, const Vec2u& position );
	std::optional<Tree*> getTree( const Vec2u& position );
	const con::FixedArray2D<Tree*>& getTreesArray();
	const PlotInfo& getInfo();

private:
	con::FixedArray2D<Tree*> assignedTrees;
	WorldScene* world = nullptr;
	PlotInfo info;
};