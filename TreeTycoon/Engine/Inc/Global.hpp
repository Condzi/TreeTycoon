/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

namespace sf
{
class RenderWindow;
}

namespace con::priv
{
struct GlobalClass final
{
	class UpdaterClass& _Updater;
	class GameClass& Game;
	sf::RenderWindow& GameWindow;
	class RendererClass& _Renderer;
	class AssetsClass& Assets;
	class SceneStackClass& SceneStack;
	class InputClass& Input;
	class GUIClass& GUI;
	std::unordered_map<std::string, std::string> PlayerStats;
	sf::Time FrameTime;
	bool ExitGame = false;

	GlobalClass();
	~GlobalClass();
};
}

namespace con
{
extern priv::GlobalClass Global;
}