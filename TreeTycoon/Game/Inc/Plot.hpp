/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "PlotInfo.hpp"
#include "Tree.hpp"

class World;

class Plot final
{
public:
	Plot() = default;
	Plot( World& world_, const PlotInfo& info_ );

	std::optional<Tree*> spawnTree( size_t nameHash, const Vec2u& position );
	std::optional<Tree*> getTree( const Vec2u& position );

private:
	con::FixedArray2D<Tree*> assignedTrees;
	World* world = nullptr;
	PlotInfo info;
};