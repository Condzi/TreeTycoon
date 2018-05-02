/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "System.hpp"

namespace con
{
void System::setUpdatePriority( int16_t val )
{
	updatePriority = val;
}

int16_t System::getUpdatePriority() const
{
	return updatePriority;
}

void System::_setScene( Scene& scene )
{
	parentScene = &scene;
}
}