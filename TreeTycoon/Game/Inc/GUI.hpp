/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

using namespace con;

class GUI final :
	public tgui::Gui,
	public IDrawable
{
public:
	using tgui::Gui::Gui;

	GUI();
	~GUI();

private:
	void render( sf::RenderWindow& window ) override;
};