/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "TreeStats.hpp"
#include "TreeInfo.hpp"

// FIXME: Buttons are disappearing after scene reload (they are deleted from GUI because loading, prevent that. use onEnable()?)
class Tree final :
	public con::Entity
{
public:
	tgui::Button::Ptr button;
	TreeStats stats;
	const TreeInfo* info = nullptr;
	size_t parentPlotHash = 0;
	const sf::Texture* texture = nullptr;

	Tree() = default;
	Tree( const TreeInfo* const info_, const std::string& parentPlotName );
	Tree( const TreeInfo* const info_, size_t parentPlotHash_ );

	RectI getTextureRect() const;

	void onUpdate() override;

private:
	void initButton();
};