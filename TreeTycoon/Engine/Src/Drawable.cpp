/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Drawable.hpp"
#include "Renderer.hpp"
#include "Window.hpp"

namespace con
{
IDrawable::IDrawable()
{
	Global._Renderer.add( this );
}
IDrawable::~IDrawable()
{
	Global._Renderer.remove( this );
}

void IDrawable::setDrawLayer( int16_t layer_ )
{
	layer = layer_;
}

int16_t IDrawable::getDrawLayer() const
{
	return layer;
}

void IDrawable::boundWithEntity( Entity* boundedEntity_ )
{
	boundedEntity = boundedEntity_;
}

Entity* IDrawable::getBoundedEntity() const
{
	return boundedEntity;
}

bool IDrawable::isBoundedWithEntity() const
{
	return boundedEntity != nullptr;
}

void IDrawable::updatePositionToEntity( sf::Transformable& object ) const
{
	auto& win = Global.GameWindow;

	if ( useEntityPosition && boundedEntity ) {
		if ( boundedEntity->useAbsolutePositioning ) {
			auto entityPos = boundedEntity->position;

			object.setPosition( win.convertAbsoluteToPixels( entityPos ) );
		} else
			object.setPosition( boundedEntity->position );
	}
}

void RectangleShape::render( sf::RenderWindow& window )
{
	window.draw( *this );
}

void RectangleShape::update()
{
	updatePositionToEntity( *this );
	updateFrameTime();
	if ( auto opt = getFrameRect(); opt.has_value() ) {
		setTexture( animationInfo.sheet );
		setTextureRect( opt.value() );
	}
}

void CircleShape::render( sf::RenderWindow& window )
{
	window.draw( *this );
}

void CircleShape::update()
{
	updatePositionToEntity( *this );
	updateFrameTime();
	if ( auto opt = getFrameRect(); opt.has_value() ) {
		setTexture( animationInfo.sheet );
		setTextureRect( opt.value() );
	}
}

void Sprite::render( sf::RenderWindow& window )
{
	window.draw( *this );
}

void Sprite::update()
{
	updatePositionToEntity( *this );
	updateFrameTime();
	if ( auto opt = getFrameRect(); opt.has_value() ) {
		// Incosistency - rest of drawables needs pointer, Sprite needs reference. 
		setTexture( *animationInfo.sheet );
		setTextureRect( opt.value() );
	}
}

void Text::render( sf::RenderWindow& window )
{
	window.draw( *this );
}

void IAnimation::updateFrameTime()
{
	const auto& ai = animationInfo;

	if ( !isAnimation )
		return;

	if ( errorWithInfo() ) {
		isAnimation = false;
		return;
	}

	currentFrameTime += Global.FrameTime;
	if ( currentFrameTime > ai.fps ) {
		currentFrameTime -= ai.fps;

		if ( ++currentFrameNumber > ai.framesCount )
			currentFrameNumber = 0;
	}
}
std::optional<sf::IntRect> IAnimation::getFrameRect()
{
	const auto& ai = animationInfo;

	if ( !isAnimation )
		return {};

	auto newFrameXpos = currentFrameNumber * ai.frameSize;
	return sf::IntRect( newFrameXpos, 0, ai.frameSize, ai.frameSize );
}

bool IAnimation::errorWithInfo()
{
	const auto& ai = animationInfo;

	if ( !ai.sheet ) {
		log( LogPriority::Error, "null sheet." );
	} else if ( ai.sheet->getSize().x < ai.framesCount * ai.frameSize ) {
		auto has = ai.sheet->getSize().x;
		auto need = ai.framesCount * ai.frameSize;

		log( LogPriority::Error, "sheet is smaller in X than declared (", has, " - declared ", need, ")." );
	} else if ( ai.sheet->getSize().y < ai.frameSize ) {
		auto has = ai.sheet->getSize().y;
		auto need = ai.frameSize;

		log( LogPriority::Error, "sheet is smaller in Y than declared (", has, " - declared ", need, ")." );
	} else
		return false;

	return true;
}
}