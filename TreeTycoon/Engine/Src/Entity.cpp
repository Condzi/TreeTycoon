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
	if ( status != Status::Dead ) {
		status = Status::Dead;
		onKill();
		return;
	}

	debugLog( LogPriority::Warning, "already dead." );
}

void Entity::disable()
{
	if ( status == Status::Dead )
		debugLog( LogPriority::Warning, "can't be disabled: it's dead." );
	else if ( status != Status::Disabled ) {
		status = Status::Disabled;
		onDisable();
	} else
		debugLog( LogPriority::Warning, "already disabled." );
}

void Entity::enable()
{
	if ( status == Status::Dead )
		debugLog( LogPriority::Warning, "can't be enabled: it's dead." );
	else if ( status != Status::Enabled ) {
		status = Status::Enabled;
		onEnable();
	} else
		debugLog( LogPriority::Warning, "already enabled." );
}

Entity::Status Entity::getStatus() const
{
	return status;
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
	if ( status == Status::Enabled )
		onUpdate();
}

std::string Entity::loggerName() const
{
	static auto getStatusAsString = []( Status s ) {
		switch ( s ) {
		case Status::Enabled: return "Enabled";
		case Status::Disabled: return "Disabled";
		case Status::Dead: return "Dead";
		}
	};

	return ConvertTo<std::string>( tag, ":", getStatusAsString( status ) );
}
}