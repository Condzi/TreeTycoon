/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Utility.hpp"
#include "IUpdatable.hpp"
#include "Entity.hpp"

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
	void boundWithEntity( Entity* boundedEntity_ );
	Entity* getBoundedEntity() const;
	bool isBoundedWithEntity() const;

	virtual void render( sf::RenderWindow& window ) {}

protected:
	Entity* boundedEntity = nullptr;
	int16_t layer = 0;
};

struct AnimationInfo final
{
	sf::Texture* sheet = nullptr;
	uint16_t frameSize = 0;
	uint16_t framesCount = 0;
	sf::Time fps;
};

class IAnimation :
	public IDrawable,
	public IUpdatable,
	public ILogger
{
public:
	bool isAnimation = false;
	AnimationInfo animationInfo;

	int8_t getUpdatePriority() const
	{
		return ConvertTo<int8_t>( UpdatePriority::Drawable );
	}

protected:
	void updateFrameTime();
	std::optional<sf::IntRect> getFrameRect();

private:
	sf::Time currentFrameTime;
	uint16_t currentFrameNumber = 0;

	bool errorWithInfo();

	std::string loggerName() const override
	{
		return "IAnimation";
	}
};

class RectangleShape :
	public sf::RectangleShape,
	public IAnimation
{
public:
	using sf::RectangleShape::RectangleShape;

	void render( sf::RenderWindow& window ) override;

private:
	void update() override;
};

class CircleShape :
	public sf::CircleShape,
	public IAnimation
{
public:
	using sf::CircleShape::CircleShape;

	void render( sf::RenderWindow& window ) override;

private:
	void update() override;
};

class Sprite :
	public sf::Sprite,
	public IAnimation
{
public:
	using sf::Sprite::Sprite;

	void render( sf::RenderWindow& window ) override;

private:
	void update() override;
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