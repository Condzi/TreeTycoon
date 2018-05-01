/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "EntityStorage.hpp"

#include <SFML/System/Clock.hpp>

namespace con::priv
{
void EntityStorage::update()
{
	if ( cleanupClock.getElapsedTime() >= CLEANUP_INTERVAL ) {
		cleanupClock.restart();

		cleanup();
	}
}

void EntityStorage::cleanup()
{
	// To have IDE autocomplete (if auto& then doesn't work)
	using EntityPtr = std::unique_ptr<Entity>;

	auto begin = entities.begin();
	auto end = entities.end();

	entities.erase( std::remove_if( begin, end,
					[]( EntityPtr& e ) {
		return e->getStatus() == Entity::Status::Dead;
	} ), end );
}
}