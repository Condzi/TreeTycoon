/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "Tree.hpp"

Tree::Tree( const TreeInfo* const info_, const std::string& parentPlotName_ ) :
	info( info_ ),	
	parentPlotName( parentPlotName_ )
{}

RectI Tree::getTextureRect() const
{
	return
	{
		stats.growingState * constants::TREE_TEXTURE_WIDTH,
		0,
		constants::TREE_TEXTURE_WIDTH,
		constants::TREE_TEXTURE_REAL_HEIGHT
	};
}

