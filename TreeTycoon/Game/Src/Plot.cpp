/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "Plot.hpp"

Plot::Plot( World& world_, const PlotInfo& info_ ) :
	world( world_ ),
	info( info_ ),
	assignedTrees( { info.sizeX, info.sizeY } )
{}

std::optional<Tree*> Plot::spawnTree( size_t nameHash, const Vec2u& position )
{
	// TODO: Implement me.

	// auto* tree = world.spawn<Tree>(nameHash, info.nameHash);
	// assignedTrees.emplace_back(tree);
}

std::optional<Tree*> Plot::getTree( const Vec2u& position )
{
	if ( auto tree = assignedTrees.at( position ); tree )
		return tree;

	return {};
}
