/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Entity.hpp"	

namespace con
{
void Entity::kill()
{
	if ( state != State::Dead ) {
		state = State::Dead;
		onKill();
		return;
	}

	debugLog( LogPriority::Warning, "already dead." );
}

void Entity::disable()
{
	if ( state == State::Dead )
		debugLog( LogPriority::Warning, "can't be disabled: it's dead." );
	else if ( state != State::Disabled ) {
		state = State::Disabled;
		onDisable();
	} else
		debugLog( LogPriority::Warning, "already disabled." );
}

void Entity::enable()
{
	if ( state == State::Dead )
		debugLog( LogPriority::Warning, "can't be enabled: it's dead." );
	else if ( state != State::Enabled ) {
		state = State::Enabled;
		onEnable();
	} else
		debugLog( LogPriority::Warning, "already enabled." );
}

Entity::State Entity::getState() const
{
	return state;
}

Scene& Entity::getParentScene()
{
	return *parentScene;
}

int32_t Entity::getUniqueID()
{
	return uniqueID;
}

void Entity::_setParentScene( Scene& scene )
{
	parentScene = &scene;
}

void Entity::update()
{
	if ( state == State::Enabled )
		onUpdate();
}

std::string Entity::loggerName() const
{
	static auto getStateAsString = []( State s ) {
		switch ( s ) {
		case State::Enabled: return "Enabled";
		case State::Disabled: return "Disabled";
		case State::Dead: return "Dead";
		}
	};

	return ConvertTo<std::string>( tag, ":", getStateAsString( state ) );
}
}