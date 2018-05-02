/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Scene.hpp"

namespace con
{
void Scene::_enable()
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
		enableEntities();
		onEnable();
		break;
	}
	case Status::Unloaded:
	{
		debugLog( LogPriority::Warning, "can't be enabled: it's unloaded." );
		break;
	}
	}
}

void Scene::_disable()
{
	switch ( status ) {
	case Status::Enabled:
	{
		status = Status::Disabled;
		disableEntities();
		onDisable();
		break;
	}
	case Status::Disabled:
	{
		debugLog( LogPriority::Warning, "already disabled." );
		break;
	}
	case Status::Unloaded:
	{
		debugLog( LogPriority::Warning, "can't be disabled: it's unloaded." );
		break;
	}
	}
}

std::string Scene::loggerName() const
{
	static auto getStatusAsString = []( Status s ) {
		switch ( s ) {
		case Status::Enabled: return "Enabled";
		case Status::Disabled: return "Disabled";
		}
	};

	return ConvertTo<std::string>( tag, ":", getStatusAsString( status ) );
}

void Scene::disableEntities()
{
	forEachEntity( []( Entity& entity ) {
		entity.disable();
	} );
}

void Scene::enableEntities()
{
	forEachEntity( []( Entity& entity ) {
		entity.enable();
	} );
}
}