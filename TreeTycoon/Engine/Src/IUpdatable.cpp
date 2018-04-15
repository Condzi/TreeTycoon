/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "IUpdatable.hpp"
#include "Updater.hpp"

namespace con
{
IUpdatable::IUpdatable()
{
	priv::Updater.add( this );
}

IUpdatable::~IUpdatable()
{
	priv::Updater.remove( this );
}
}
