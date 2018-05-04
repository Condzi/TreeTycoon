/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Drawable.hpp"
#include "Renderer.hpp"

namespace con
{
IDrawable::IDrawable()
{
	priv::Renderer.add( this );
}
IDrawable::~IDrawable()
{
	priv::Renderer.remove( this );
}

void IDrawable::setDrawLayer( int16_t layer_ )
{
	layer = layer_;
}

int16_t IDrawable::getDrawLayer() const
{
	return layer;
}

void RectangleShape::render( sf::RenderWindow& window )
{
	window.draw( *this );
}

void CircleShape::render( sf::RenderWindow& window )
{
	window.draw( *this );
}

void Sprite::render( sf::RenderWindow& window )
{
	window.draw( *this );
}

void Text::render( sf::RenderWindow& window )
{
	window.draw( *this );
}
}