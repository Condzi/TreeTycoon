/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "System.hpp"

namespace con
{
void System::_setUpdatePriority( int16_t val )
{
	updatePriority = val;
}

int16_t System::_getUpdatePriority() const
{
	return updatePriority;
}

void System::_setScene( Scene& scene )
{
	parentScene = &scene;
}
}