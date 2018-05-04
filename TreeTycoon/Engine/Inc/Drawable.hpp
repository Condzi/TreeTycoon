/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Utility.hpp"

namespace con
{
class IDrawable
{
public:
	IDrawable();
	RULE_OF_FIVE_NO_CTOR( IDrawable );
	virtual ~IDrawable();

	void setDrawLayer( int16_t layer_ );
	int16_t getDrawLayer() const;

	virtual void render( sf::RenderWindow& window ) {}

private:
	int16_t layer = 0;
};

class RectangleShape :
	public sf::RectangleShape,
	public IDrawable
{
public:
	using sf::RectangleShape::RectangleShape;

	void render( sf::RenderWindow& window ) override;
};

class CircleShape :
	public sf::CircleShape,
	public IDrawable
{
public:
	using sf::CircleShape::CircleShape;

	void render( sf::RenderWindow& window ) override;
};

class Sprite :
	public sf::Sprite,
	public IDrawable
{
public:
	using sf::Sprite::Sprite;

	void render( sf::RenderWindow& window ) override;
};

class Text :
	public sf::Text,
	public IDrawable
{
public:
	using sf::Text::Text;

	void render( sf::RenderWindow& window ) override;
};
}