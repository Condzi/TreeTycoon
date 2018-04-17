/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"
#include "Assets.hpp"

namespace con::priv
{
AssetsClass::AssetsClass()
{
	Settings._load( "settings.ini" );
}
}

namespace con
{
inline con::priv::AssetsClass Assets{};
}