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
	Global._Updater.add( this );
}

IUpdatable::~IUpdatable()
{
	Global._Updater.remove( this );
}
}
