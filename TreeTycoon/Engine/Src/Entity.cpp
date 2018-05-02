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
	switch ( status ) {
	case Status::Enabled:
	{
		status = Status::Disabled;
		onDisable();
		break;
	}
	case Status::Disabled:
	{
		debugLog( LogPriority::Warning, "already disabled." );
		break;
	}
	case Status::Dead:
	{
		debugLog( LogPriority::Warning, "can't be disabled: it's dead." );
		break;
	}
	}
}

void Entity::enable()
{
	switch ( status ) {
	case Status::Enabled:
	{
		debugLog( LogPriority::Warning, "already enabled." );
		break;
	}
	case Status::Disabled:
	{
		status = Status::Enabled;
		onEnable();
		break;
	}
	case Status::Dead:
	{
		debugLog( LogPriority::Warning, "can't be enabled: it's dead." );
		break;
	}
	}
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