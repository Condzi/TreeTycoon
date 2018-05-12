/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Renderer.hpp"
#include "Window.hpp"

namespace con::priv
{
void RendererClass::add( IDrawable* drawable )
{
	drawables.emplace_back( drawable );
}

void RendererClass::remove( IDrawable* drawable )
{
	drawables.erase( std::remove( drawables.begin(), drawables.end(), drawable ) );
}

void RendererClass::sortByLayer()
{
	std::sort( drawables.begin(), drawables.end(), []( IDrawable* a, IDrawable* b ) {
		return a->getDrawLayer() < b->getDrawLayer();
	} );
}

void RendererClass::render()
{
	auto& win = Global.GameWindow._getSFMLWindow();

	win.clear();

	for ( auto drawable : drawables ) {
		if ( auto e = drawable->getBoundedEntity(); e )
			if ( e->getStatus() != Entity::Status::Enabled )
				continue;

		drawable->render( win );
	}

	win.display();
}

void RendererClass::update()
{
	sortByLayer();
	render();
}
}