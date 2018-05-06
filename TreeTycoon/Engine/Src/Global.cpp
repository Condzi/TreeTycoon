/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Global.hpp"
#include "Updater.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Assets.hpp"
#include "SceneStack.hpp"

namespace con::priv
{
// Don't care about memory cleanup. They live whole Game lifetime so it doesn't matter.
GlobalClass::GlobalClass() :
	Updater( *( new UpdaterClass{} ) ),
	Game( *( new GameClass{} ) ),
	GameWindow( *( new Window{} ) ),
	Renderer( *( new RendererClass{} ) ),
	Assets( *( new AssetsClass{} ) ),
	SceneStack( *( new SceneStackClass{} ) )
{}
}

namespace con
{
inline priv::GlobalClass Global{};
}