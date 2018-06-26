/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "Plot.hpp"
#include "WorldScene.hpp"

Plot::Plot( WorldScene& world_, const PlotInfo& info_ ) :
	world( &world_ ),
	info( info_ ),
	assignedTrees( { con::ConvertTo<uint32_t>( info.sizeX ), con::ConvertTo<uint32_t>( info.sizeY ) } )
{}

std::optional<Tree*> Plot::spawnTree( size_t nameHash, const Vec2u& position )
{
	if ( !world )
		return {};

	const TreeInfo* treeInfo = GlobalGameData.TreeInfos.findTreeInfo( nameHash ).value_or( nullptr );
	if ( treeInfo == nullptr )
		return {};

	Tree* tree = &world->spawn<Tree>( treeInfo, info.nameHash );
	assignedTrees.at( position ) = tree;

	return tree;
}

std::optional<Tree*> Plot::getTree( const Vec2u& position )
{
	if ( auto tree = assignedTrees.at( position ); tree )
		return tree;

	return {};
}

const PlotInfo& Plot::getInfo()
{
	return info;
}
