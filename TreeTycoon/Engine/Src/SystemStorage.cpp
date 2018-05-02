/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "SystemStorage.hpp"

namespace con::priv
{
SystemStorage::SystemStorage( Scene* parentScene_ ) :
	parentScene( *parentScene_ )
{}
void SystemStorage::updateSystems()
{
	// DEBUG!
	if ( needsSort ) {
		if ( static bool logged = false; !logged ) {
			logged = true;
			std::cout<< "\nFIXME - SystemStorage needs sort! Update me before something!\n";
			update();
		}
	}

	for ( auto& system : systems )
		system->onUpdate();
}

void SystemStorage::update()
{
	if ( needsSort ) {
		needsSort = false;

		std::sort( systems.begin(), systems.end(), []( auto& a, auto& b ) {
			return a->_getUpdatePriority() < b->_getUpdatePriority();
		} );
	}
}
}
