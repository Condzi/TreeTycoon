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
#include "Input.hpp"

namespace con::priv
{
GlobalClass::GlobalClass() :
	_Updater( *( new UpdaterClass{} ) ),
	Game( *( new GameClass{} ) ),
	GameWindow( *( new GameWindowClass{} ) ),
	_Renderer( *( new RendererClass{} ) ),
	Assets( *( new AssetsClass{} ) ),
	SceneStack( *( new SceneStackClass{} ) ),
	Input( *( new InputClass{} ) )
{}

// Delete some pts to call their destructors.
GlobalClass::~GlobalClass()
{
	delete &Assets;
}
}

namespace con
{
inline priv::GlobalClass Global{};
}