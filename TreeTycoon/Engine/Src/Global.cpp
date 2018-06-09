/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Global.hpp"
#include "Updater.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "Assets.hpp"
#include "SceneStack.hpp"
#include "Input.hpp"
#include "GUI.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace con::priv
{
GlobalClass::GlobalClass() :
	_Updater( *( new UpdaterClass{} ) ),
	Game( *( new GameClass{} ) ),
	GameWindow( *( new sf::RenderWindow{} ) ),
	_Renderer( *( new RendererClass{} ) ),
	Assets( *( new AssetsClass{} ) ),
	SceneStack( *( new SceneStackClass{} ) ),
	Input( *( new InputClass{} ) ),
	GUI( *( new GUIClass{} ) )
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