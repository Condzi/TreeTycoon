/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

namespace con::priv
{
struct GlobalClass final
{
	class UpdaterClass& Updater;
	class GameClass& Game;
	class Window& GameWindow;
	class RendererClass& Renderer;
	class AssetsClass& Assets;
	class SceneStackClass& SceneStack;
	sf::Time FrameTime;
	bool ExitGame = false;

	GlobalClass();
};
}

namespace con
{
extern priv::GlobalClass Global;
}