/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include <TGUI/Gui.hpp>
#include "Drawable.hpp"

namespace con::priv
{
class GUIClass final :
	public tgui::Gui,
	public IDrawable
{
public:
	using tgui::Gui::Gui;

	GUIClass();

private:
	void render( sf::RenderWindow& window ) override;
};
}
