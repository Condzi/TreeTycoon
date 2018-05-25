/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "TreeStats.hpp"
#include "TreeInfo.hpp"
#include "GUI.hpp"

class Tree final
{
public:
	TreeStats statistics;
	const TreeInfo& INFO;
	con::Sprite visualRepresentation;
	tgui::Button::Ptr clickableButton;

	Tree( const TreeInfo const* info, GUI& gui );

	void setPosition( const Vec2f& position );
	void updateVisualRepresentation();
};