/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "Tree.hpp"

Tree::Tree( const TreeInfo* const info_, const std::string& parentPlotName ) :
	info( info_ ),
	parentPlotHash( std::hash<std::string>{}( parentPlotName ) )
{}

Tree::Tree( const TreeInfo* const info_, size_t parentPlotHash_ ) :
	info( info_ ),
	parentPlotHash( parentPlotHash_ )
{
	texture = &con::Global.Assets.Texture.get( info->textureName );
}

RectI Tree::getTextureRect() const
{
	return
	{
		stats.growingState * constants::TREE_TEXTURE_WIDTH,
		0,
		constants::TREE_TEXTURE_WIDTH,
		constants::TREE_TEXTURE_HEIGHT
	};
}

