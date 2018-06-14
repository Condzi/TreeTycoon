/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "TreeStats.hpp"
#include "TreeInfo.hpp"

class Tree final :
	public con::Entity
{
public:
	TreeStats stats;
	const TreeInfo* info = nullptr;
	std::string parentPlotName;

	Tree() = default;
	Tree( const TreeInfo* const info_, const std::string& parentPlotName_ );

	RectI getTextureRect() const;
};