/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Updater.hpp"
#include "IUpdatable.hpp"

namespace con::priv
{
inline UpdaterClass Updater{};

void UpdaterClass::add( IUpdatable* updatable )
{
	updatables.emplace_back( updatable );
}

void UpdaterClass::remove( IUpdatable* updatable )
{
	updatables.erase( std::remove( updatables.begin(), updatables.end(), updatable ) );
}

void UpdaterClass::update()
{
	sortByPriority();
	for ( auto* updatable : updatables )
		updatable->update();
}

void UpdaterClass::sortByPriority()
{
	std::sort( updatables.begin(), updatables.end(), []( IUpdatable* a, IUpdatable* b ) {
		return a->getPriority() < b->getPriority();
	} );
}
}